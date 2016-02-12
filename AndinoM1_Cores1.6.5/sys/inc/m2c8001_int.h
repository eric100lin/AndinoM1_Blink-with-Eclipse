/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_int.h
 *  \brief M2C8001 INT functions prototypes
 *  $Date: 2014-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

#ifndef M2C8001_INT_H_
#define M2C8001_INT_H_

/***********************************************************************************************
*   MARCOS
************************************************************************************************/

#define SHIFT_INT(x)    (1<<x)
#define	ISR_NUM(irq)    ((unsigned int) (1<<irq))


/**************************************************************************************************
 *   CONSTANTS AND DEFINES
 *************************************************************************************************/

#define INT_TYPE_FIQ    (0x00)
#define INT_TYPE_IRQ    (0x01)
#define INT_TYPE_EXT    (0x02)

#define LEVEL_TRIGGER   (0)
#define EDGE_TRIGGER    (1)

#define HIGH_ACTIVE     (0)
#define LOW_ACTIVE      (1)


#define KHz 1000
#define MHz 1000000
#define TICK_HZ 1
#define SIMU_FACTOR (0)

/***********************************************************************************************
*   TYPEDEFS
************************************************************************************************/
typedef enum IRQ_NUM
{
    IRQ_TM1_INTR = 0,
    IRQ_TM2_INTR,
    IRQ_TM3_INTR,
    IRQ_I2C_INTR,
    IRQ_MAC_INTR,
    IRQ_SSP0_INTR,
    IRQ_SSP1_INTR,
    IRQ_DMAC_INTR,
    IRQ_UART0_INTR,
    IRQ_UART1_INTR,
    IRQ_SNIFFER_INTR,
    IRQ_SARADC_INTR,
    IRQ_SW0_INTR,
    IRQ_SW1_INTR,
    IRQ_FLASH_INTR,
    IRQ_INTR_SIZE,
    IRQ_INTR_NULL = 0xFF,
}IRQ_NUM_e;

typedef enum FIQ_NUM
{
    FIQ_LPTM1_INTR,
    FIQ_LPTM2_INTR,
    FIQ_LPTM3_INTR,
    FIQ_WDT_INTR,
    FIQ_RTC_INTR,
    FIQ_GPIO_INTR,
    FIQ_ACMP0_INTR,
    FIQ_ACMP1_INTR,
    FIQ_RTCOSC_INTR,
    FIQ_SW0_INTR,
    FIQ_SW1_INTR,
    FIQ_EXT0_INTR,
    FIQ_INTR_SIZE,
    FIQ_INTR_NULL = 0xFF,
}FIQ_NUM_e;



typedef enum EXT_IRQ_NUM
{
    EXT_INT1,
    EXT_INT_SIZE,
}EXT_IRQ_NUM_e;


typedef void (*IRQ_Callback)(int irqNum);

typedef struct IRQ_Func_s
{
	int   irq;
	IRQ_Callback pIrqCb;
} IRQ_Func_t;


/***********************************************************************************************
*   GLOBAL PROTOTYPES
************************************************************************************************/
inline void GIE_ENABLE();
inline void GIE_DISABLE();

void enableIntr(unsigned int mask, int edge, int neg);
void disableIntr(unsigned int mask);
void clearIrqState(unsigned int mask);
void enableFiqIntr(unsigned int mask, int edge, int neg);
void disableFiqIntr(unsigned int mask);
void clearFiqState(unsigned int mask);
int ISR_InsertCb(int intType,int intNum,IRQ_Callback cb);


///////////////////////////////////////////////////////////////////////////////////////

void INT_IrqEn(unsigned int mask, int edge, int neg);
void INT_IrqDis(unsigned int mask);
void INT_IrqStsClr(unsigned int mask);
void INT_FiqEn(unsigned int mask, int edge, int neg);
void INT_FiqDis(unsigned int mask);
void INT_FiqStsClr(unsigned int mask);

void INT_GblIsrEn(void);
void INT_GblIsrDis(void);


#endif /* M2C8001_INT_H_ */
