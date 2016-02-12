
/***********************************************************************************************
*   INCLUDES
************************************************************************************************/
#include <stdio.h>
#include <nds32_intrinsic.h>
#include "config.h"
#include "m2c8001.h"
#include "m2c8001_int.h"


/***********************************************************************************************
*   GLOBAL VARIABLES
************************************************************************************************/
static IRQ_Func_t gIrqCbTbl[IRQ_INTR_SIZE];
static IRQ_Func_t gFiqCbTbl[FIQ_INTR_SIZE];
static IRQ_Func_t gExtIntCbTbl;

static int gintIrqIdx=0;
static int gintFiqIdx=0;


inline void GIE_ENABLE()
{
	__nds32__setgie_en();
	__nds32__dsb();
}

inline void GIE_DISABLE()
{
	__nds32__setgie_dis();
	__nds32__dsb();
}

 /* this function generates a s/w interrupt */
void gen_swi()
{
	unsigned int int_pend;

	int_pend = __nds32__mfsr(NDS32_SR_INT_PEND);
	int_pend |= 0x10000;
	__nds32__mtsr(int_pend, NDS32_SR_INT_PEND);
	__nds32__dsb();
}


void enableIntr(unsigned int mask, int edge, int neg)
{
	if (edge)
		outw(INTC_BASE + IRQTMR_OFFSET, inw(INTC_BASE + IRQTMR_OFFSET) | mask);     //Trigger Mode , edge
	else
		outw(INTC_BASE + IRQTMR_OFFSET, inw(INTC_BASE + IRQTMR_OFFSET) & ~mask);    //Trigger Mode, level

	if (neg)
		outw(INTC_BASE + IRQTLR_OFFSET, inw(INTC_BASE + IRQTLR_OFFSET) | mask);     //Trigger Level, active low
	else
		outw(INTC_BASE + IRQTLR_OFFSET, inw(INTC_BASE + IRQTLR_OFFSET) & ~mask);    //Trigger Level, active high /* Joe updated */

	outw(INTC_BASE + IRQER_OFFSET, inw(INTC_BASE + IRQER_OFFSET) | mask);           //Enable Register

}

void disableIntr(unsigned int mask)
{
    outw(INTC_BASE + IRQER_OFFSET, inw(INTC_BASE + IRQER_OFFSET) & ~mask);
}

void clearIrqState(unsigned int mask)
{
    outw(INTC_BASE + IRQICR_OFFSET, 1 << mask);
}


void enableFiqIntr(unsigned int mask, int edge, int neg)
{
	if (edge)
		outw(INTC_BASE + FIQTMR_OFFSET, inw(INTC_BASE + FIQTMR_OFFSET) | mask);     //Trigger Mode , edge
	else
		outw(INTC_BASE + FIQTMR_OFFSET, inw(INTC_BASE + FIQTMR_OFFSET) & ~mask);    //Trigger Mode, level

	if (neg)
		outw(INTC_BASE + FIQTLR_OFFSET, inw(INTC_BASE + FIQTLR_OFFSET) | mask);     //Trigger Level, active high
	else
		outw(INTC_BASE + FIQTLR_OFFSET, inw(INTC_BASE + FIQTLR_OFFSET) & ~mask);    //Trigger Level, active low

	outw(INTC_BASE + FIQER_OFFSET, inw(INTC_BASE + FIQER_OFFSET) | mask);           //Enable Register

}

void disableFiqIntr(unsigned int mask)
{
    outw(INTC_BASE + FIQER_OFFSET, inw(INTC_BASE + FIQER_OFFSET) & ~mask);
}

void clearFiqState(unsigned int mask)
{
    outw(INTC_BASE + FIQICR_OFFSET, 1 << mask);
}



#if (defined(NDS32_BASELINE_V3) || defined(NDS32_BASELINE_V3M))
unsigned int intr_save_mask(unsigned int num)
{
	/* get current intr enable mask */
	unsigned int old_mask = __nds32__mfsr(NDS32_SR_INT_MASK2);
	unsigned int mask = old_mask & (~(1 << num));
	__nds32__mtsr(mask, NDS32_SR_INT_MASK2);
	__nds32__dsb();
	return old_mask;
}

void intr_restore_mask(unsigned int mask)
{
	GIE_DISABLE();
	/* restore intr enable mask */
	__nds32__mtsr(mask, NDS32_SR_INT_MASK2);
	__nds32__dsb();
}
#endif

int ISR_InsertCb(int intType,int intNum,IRQ_Callback cb)
{
    int i;

    if(intType == INT_TYPE_FIQ){
        if(intNum>FIQ_INTR_SIZE)
            return 1;
        for(i=0;i<gintFiqIdx;i++){
            if(gFiqCbTbl[i].irq==intNum){
                return 0;
            }
        }
        gFiqCbTbl[gintFiqIdx].irq=intNum;
        gFiqCbTbl[gintFiqIdx].pIrqCb=cb;
        gintFiqIdx++;
    }else if(intType == INT_TYPE_IRQ){
        if(intNum>IRQ_INTR_SIZE)
            return 1;
        for(i=0;i<gintIrqIdx;i++){
            if(gIrqCbTbl[i].irq==intNum){
                return 0;
            }
        }
        gIrqCbTbl[gintIrqIdx].irq=intNum;
        gIrqCbTbl[gintIrqIdx].pIrqCb=cb;
        gintIrqIdx++;
        //DBG_PRINT("\n\rintNum:%d",intNum);
    }
    else if(intType == INT_TYPE_EXT){
        gExtIntCbTbl.pIrqCb=cb;
    }
    return 0;
}


void intc_reset()
{
	/* HW1(+0x4)Enable Regiter, interrupt disabled */
	outw(INTC_BASE + IRQER_OFFSET, INT_ER_INIT);
	/* HW1(+0x8)Interrupt Clear Register, write 1 to clear */
	outw(INTC_BASE + IRQICR_OFFSET, INT_CLEAR_VALUE);

	/* HW0(+0x24)Enable Regiter, interrupt disabled */
	outw(INTC_BASE + FIQER_OFFSET, INT_ER_INIT);
	/* HW0(+0x28)Interrupt Clear Register, write 1 to clear */
	outw(INTC_BASE + FIQICR_OFFSET, INT_CLEAR_VALUE);
}

void initIntr()
{

	/* Check IVIC version (IVB.IVIC_VER) */
	if (__nds32__mfsr(NDS32_SR_IVB) & (1 << 11)) {
     	    //__nds32__mtsr(0x10007, NDS32_SR_INT_MASK);
#if (defined(NDS32_BASELINE_V3) || defined(NDS32_BASELINE_V3M))
        	/* enable HW# (timer1, GPIO & SWI) */
        	//__nds32__mtsr(IC_TIMER1 | IC_GPIO | IC_SWI, NDS32_SR_INT_MASK2);
		/* Interrupt pending register, write 1 to clear */
		__nds32__mtsr(0xFFFFFFFF, NDS32_SR_INT_PEND2);
#endif
	} else {
		/* enable SW0, HW0 and HW1 and HW2*/
	    //__nds32__mtsr(0x10007, NDS32_SR_INT_MASK);
	    //__nds32__mtsr(0x00007, NDS32_SR_INT_MASK);
        //intc_reset();

        //M2C IVIC Version is 1 in newton, so this section is not executed, moved out.
	}

    /* Interrupt controller */
    intc_reset();

    /* enable HW0 */
	__nds32__mtsr(0x00007, NDS32_SR_INT_MASK);  //Only enable HW0/HW1/HW2

}

void initIntr_standby()
{

	/* Check IVIC version (IVB.IVIC_VER) */
	if (__nds32__mfsr(NDS32_SR_IVB) & (1 << 11)) {
#if (defined(NDS32_BASELINE_V3) || defined(NDS32_BASELINE_V3M))
		/* enable HW (GPIO) */
		__nds32__mtsr(IC_GPIO, NDS32_SR_INT_MASK2);
		/* Interrupt pending register, write 1 to clear */
		__nds32__mtsr(0xFFFFFFFF, NDS32_SR_INT_PEND2);
#endif
	} else {
        ;//M2C IVIC Version is 1 in newton, so this section is not executed, moved out.
	}

    /* Interrupt controller */
    intc_reset();

    /* enable HW0 */
	__nds32__mtsr(0x0001, NDS32_SR_INT_MASK);


}

void clear_swi()
{
	unsigned int int_pend;

	int_pend = 0x10;
	__nds32__mtsr(int_pend, NDS32_SR_INT_PEND);
	__nds32__dsb();
}

/* User can use our handler or Default_Handler */
void exception_handler(int exception_nr)
{
	while (1) ;
}

void tlb_exception_handler(int exception_nr)
{
	while (1) ;
}

/* HW0, HW1 and SW0 interrupts will only occur on IVIC version (IVB.IVIC_VER) = 0. */
void HW0_ISR()  /* FIQ Entry Point */
{
    int i,intStatus=0;

    /* read status */
    intStatus = inw(INTC_BASE+FIQSR_OFFSET);

    for(i=0;i<FIQ_INTR_SIZE;i++){
        if(ISR_NUM(gFiqCbTbl[i].irq) & intStatus){
            if(gFiqCbTbl[i].pIrqCb){
                gFiqCbTbl[i].pIrqCb(gFiqCbTbl[i].irq);
                break;
            }else{
                puts("\r\nNO_ISR");
            }
        }
    }
}

void HW1_ISR()  /* IRQ Entry Point */
{

    int i,intStatus=0;

    /* read status */
    intStatus = inw(INTC_BASE+IRQSR_OFFSET);

    //DBG_PRINT("\r\nIRQ Type:%d\r\n",intStatus);

    for(i=0;i<IRQ_INTR_SIZE;i++){
        if(ISR_NUM(gIrqCbTbl[i].irq) & intStatus){

#if 1
            if(intStatus >= ISR_NUM(gIrqCbTbl[i].irq))
            intStatus -= ISR_NUM(gIrqCbTbl[i].irq);
#endif

            if(gIrqCbTbl[i].pIrqCb){
                gIrqCbTbl[i].pIrqCb(gIrqCbTbl[i].irq);
                break;
            }else{
                puts("\r\nNO_ISR");
            }
#if 1
            if(!intStatus){
                i = IRQ_INTR_SIZE;
            }
#endif
        }
    }


}

void HW2_ISR()
{
    if(gExtIntCbTbl.pIrqCb){
        gExtIntCbTbl.pIrqCb(gExtIntCbTbl.irq);
    }else{
        puts("\r\nNO_ISR");
    }
}

void SW0_ISR()
{
	puts("A software interrupt occurs ...\n");
	clear_swi();
	return;
}


#if 0
void SYSirq_Disable_Interrupts_Save_Flags(unsigned int *flags)
{
	unsigned int tmp_flags;

	*flags = __nds32__mfsr(NDS32_SR_PSW) & 0x1;
	__nds32__setgie_dis();
	__nds32__dsb();
}

void SYSirq_Enable_Interrupts_Save_Flags(unsigned int *flags)
{
	unsigned int tmp_flags;

	*flags = __nds32__mfsr(NDS32_SR_PSW) & 0x1;
	__nds32__setgie_en();
	__nds32__dsb();
}

void SYSirq_Interrupts_Restore_Flags(unsigned int flags)
{
	unsigned int tmp;

	tmp = __nds32__mfsr(NDS32_SR_PSW);
	tmp = __nds32__bclr(tmp, 0) | flags;
	__nds32__mtsr(tmp, NDS32_SR_PSW);
	__nds32__dsb();
}
#endif









