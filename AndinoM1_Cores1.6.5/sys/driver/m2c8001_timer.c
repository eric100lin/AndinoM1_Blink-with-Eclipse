/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_timer.c
 *  \brief M2C8001 timer driver
 *  $Date: 2014-05-05
 *
 *
 * ------------------------------------------------------------------------------------------------
 */


/***********************************************************************************************
*   INCLUDES
************************************************************************************************/
#include "m2c8001_timer.h"
#include "m2c8001_int.h"


/***********************************************************************************************
*   MARCOS
************************************************************************************************/


/***********************************************************************************************
*   GLOBAL VARIABLES
************************************************************************************************/
static DRVTIMER_Callback *gTIMER1Callback;
static DRVTIMER_Callback *gTIMER2Callback;
static DRVTIMER_Callback *gTIMER3Callback;




/***********************************************************************************************
*   LOCAL FUNCTIONS
************************************************************************************************/
void TIMER1_Isr(int unused)
{
    u32 status=0;

   /*Read interrupt status*/
    status =TIMER->INTRSTATE & 0x7;

    if(gTIMER1Callback)
        gTIMER1Callback(status);

    /*Clean Timer interrupt status*/
    TIMER->INTRSTATE = status;

    /* Clear interrupt status */
    INTC->HW1INTRCLEAR = IC_TIMER1;

}

void TIMER2_Isr(int unused)
{
    u32 status=0;
   /*Read interrupt status*/
    status =TIMER->INTRSTATE & 0x38;

    if(gTIMER2Callback)
        gTIMER2Callback(status);

    /*Clean Timer interrupt status*/
    TIMER->INTRSTATE = status;

    /* Clear interrupt status */
    INTC->HW1INTRCLEAR = IC_TIMER2;

}

void TIMER3_Isr(int unused)
{
    u32 status=0;
   /*Read interrupt status*/
    status =TIMER->INTRSTATE & 0x1C0;

    if(gTIMER3Callback)
        gTIMER3Callback(status);

    /*Clean Timer interrupt status*/
    TIMER->INTRSTATE = status;

    /* Clear interrupt status */
    INTC->HW1INTRCLEAR = IC_TIMER3;

}




/***********************************************************************************************
*   GLOBAL FUNCTIONS
************************************************************************************************/

void TIMER_IsrInit(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1)
        ISR_InsertCb(INT_TYPE_IRQ,IRQ_TM1_INTR,TIMER1_Isr);
    else if(u8TimerIdx == TIMER2)
        ISR_InsertCb(INT_TYPE_IRQ,IRQ_TM2_INTR,TIMER2_Isr);
    else if(u8TimerIdx == TIMER3)
        ISR_InsertCb(INT_TYPE_IRQ,IRQ_TM3_INTR,TIMER3_Isr);
}




/***********************************************************************************************
@brief:Init specified Timer,set counter,clk source
@para:
        -u8TimerIdx:specified Timer Index
        -u8ClkSrc: clock source TIMER_CLK_SRC_32K/TIMER_CLK_SRC_APB
        -u32LoadCnt:Load value to counter and Load register
************************************************************************************************/
void TIMER_Init(u8 u8TimerIdx,u8 u8ClkSrc,u32 u32LoadCnt)
{
    if(u8TimerIdx == TIMER1){
        CGU->IIPCLKSW |= IIP_EN_TIMER1_CLK;
        TIMER->TM1COUNTER = u32LoadCnt;
        TIMER->TM1LOAD = u32LoadCnt;
        TIMER->TMCR &= ~TIMER_CTRL_TM1UP; //count down
        if(u8ClkSrc == TIMER_CLK_SRC_32K){
            TIMER->TMCR |= TIMER_CTRL_TM1CLK; //external clock
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL &~DIP_CLK_SEL_TIMER1_MASK) |DIP_CLK_SEL_TIMER1_32K;
        }
        else if(u8ClkSrc == TIMER_CLK_SRC_APB){
            TIMER->TMCR &= ~TIMER_CTRL_TM1CLK; //Internal clock
        }
    }
    else if((u8TimerIdx == TIMER2)){
        CGU->IIPCLKSW |= IIP_EN_TIMER2_CLK;
        TIMER->TM2COUNTER = u32LoadCnt;
        TIMER->TM2LOAD = u32LoadCnt;
        TIMER->TMCR &= ~TIMER_CTRL_TM2UP; //count down
        if(u8ClkSrc == TIMER_CLK_SRC_32K){
            TIMER->TMCR |= TIMER_CTRL_TM2CLK; //external clock
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL &~DIP_CLK_SEL_TIMER2_MASK) | DIP_CLK_SEL_TIMER2_32K;
        }
        else if(u8ClkSrc == TIMER_CLK_SRC_APB){
            TIMER->TMCR &= ~TIMER_CTRL_TM2CLK; //Internal clock
        }
    }
    else if((u8TimerIdx == TIMER3)){
        CGU->IIPCLKSW |= IIP_EN_TIMER3_CLK;
        TIMER->TM3COUNTER = u32LoadCnt;
        TIMER->TM3LOAD = u32LoadCnt;
        TIMER->TMCR &= ~TIMER_CTRL_TM3UP; //count down
        if(u8ClkSrc == TIMER_CLK_SRC_32K){
            TIMER->TMCR |= TIMER_CTRL_TM3CLK; //external clock
            CGU->DIPCLKSEL = (CGU->DIPCLKSEL &~DIP_CLK_SEL_TIMER3_MASK) | DIP_CLK_SEL_TIMER3_32K;
        }
        else if(u8ClkSrc == TIMER_CLK_SRC_APB){
            TIMER->TMCR &= ~TIMER_CTRL_TM3CLK; //Internal clock
        }
    }
}

/***********************************************************************************************
@brief:Disable Timer clock
@para:
        -u8TimerIdx:specified Timer
************************************************************************************************/
void TIMER_DeInit(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1)
        CGU->IIPCLKSW &= ~IIP_EN_TIMER1_CLK;
    else if((u8TimerIdx == TIMER2))
        CGU->IIPCLKSW &= ~IIP_EN_TIMER2_CLK;
    else if((u8TimerIdx == TIMER3))
        CGU->IIPCLKSW &= ~IIP_EN_TIMER3_CLK;
}

/***********************************************************************************************
@brief:Start specified Timer
@para:
        -u8TimerIdx:specified Timer Index
************************************************************************************************/
void TIMER_Start(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1)
        TIMER->TMCR |= TIMER_CTRL_TM1EN;
    else if((u8TimerIdx == TIMER2))
        TIMER->TMCR |= TIMER_CTRL_TM2EN;
    else if((u8TimerIdx == TIMER3))
        TIMER->TMCR |= TIMER_CTRL_TM3EN;;
}

/***********************************************************************************************
@brief:Stop specified Timer
@para:
        -u8TimerIdx:specified Timer Index
************************************************************************************************/
void TIMER_Stop(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1)
        TIMER->TMCR &= ~TIMER_CTRL_TM1EN;
    else if((u8TimerIdx == TIMER2))
        TIMER->TMCR &= ~TIMER_CTRL_TM2EN;
    else if((u8TimerIdx == TIMER3))
        TIMER->TMCR &= ~TIMER_CTRL_TM3EN;
}

/***********************************************************************************************
@brief:Set Match1 and Match2 of specified Timer
@para:
        -u8TimerIdx:specified Timer Index
        -u32Match1: Match1 value
        -u32Match2: Match2 value
************************************************************************************************/
void TIMER_SetMatchValue(u8 u8TimerIdx,u32 u32Match1,u32 u32Match2)
{
    if(u8TimerIdx == TIMER1){
        TIMER->TM1MATCH1 = u32Match1;
        TIMER->TM1MATCH2 = u32Match2;
    }
    else if(u8TimerIdx == TIMER2){
        TIMER->TM2MATCH1 = u32Match1;
        TIMER->TM2MATCH2 = u32Match2;
    }
    else if(u8TimerIdx == TIMER3){
        TIMER->TM3MATCH1 = u32Match1;
        TIMER->TM3MATCH2 = u32Match2;
    }
}

/***********************************************************************************************
@brief:Register specified Timer interrupt callback function
@para:
        -u8TimerIdx:specified Timer Index
        -cb: Timer callback function
***********************************************************************************************/
void TIMER_RegisterCallback(u8 u8TimerIdx,DRVTIMER_Callback cb)
{
    if(u8TimerIdx == TIMER1)
        gTIMER1Callback = cb;
    else if(u8TimerIdx == TIMER2)
        gTIMER2Callback = cb;
    else if(u8TimerIdx == TIMER3)
        gTIMER3Callback = cb;
}

/***********************************************************************************************
@brief:Enable specified Timer interrupt  function
@para:
        -u8TimerIdx:specified Timer Index
***********************************************************************************************/
void TIMER_EnableInt(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1){
        TIMER->TMCR |= TIMER_CTRL_TM1OFE;
        INT_IrqEn(1 << IRQ_TM1_INTR, 1, 0);
    }
    else if(u8TimerIdx == TIMER2){
        TIMER->TMCR |= TIMER_CTRL_TM2OFE;
        INT_IrqEn(1 << IRQ_TM2_INTR, 1, 0);
    }
    else if(u8TimerIdx == TIMER3){
        TIMER->TMCR |= TIMER_CTRL_TM3OFE;
        INT_IrqEn(1 << IRQ_TM3_INTR, 1, 0);
    }
}

/***********************************************************************************************
@brief:Disable specified Timer interrupt  function
@para:
        -u8TimerIdx:specified Timer Index
***********************************************************************************************/
void TIMER_DisableInt(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1){
        TIMER->TMCR &= ~TIMER_CTRL_TM1OFE;
        INT_IrqDis(1 << IRQ_TM1_INTR);
    }
    else if(u8TimerIdx == TIMER2){
        TIMER->TMCR &= ~TIMER_CTRL_TM2OFE;
        INT_IrqDis(1 << IRQ_TM2_INTR);
    }
    else if(u8TimerIdx == TIMER3){
        TIMER->TMCR &= ~TIMER_CTRL_TM3OFE;
        INT_IrqDis(1 << IRQ_TM3_INTR);
    }
}


/***********************************************************************************************
@brief:Get TIMER current counter
@para:
        -u8TimerIdx:specified Timer Index
***********************************************************************************************/
u32 TIMER_GetCounter(u8 u8TimerIdx)
{
    if(u8TimerIdx == TIMER1)
        return  TIMER->TM1COUNTER;
    else if(u8TimerIdx == TIMER2)
        return  TIMER->TM2COUNTER;
    else if(u8TimerIdx == TIMER3)
        return  TIMER->TM3COUNTER;
    else
        return 0;
}

/***********************************************************************************************
@brief:Set CPUPLL to Timer divider of specified Timer
@para:
        -u8TimerIdx:specified Timer Index
        -u8Divider:divider value 1~15
************************************************************************************************/
void TIMER_SetCpupllDivider(u8 u8TimerIdx,u8 u8Divider)
{
    if(u8TimerIdx == TIMER1)
        CGU->TMRCLKDIV = (CGU->TMRCLKDIV &~TCLK_TIMER1_CPUPLL_DIV) |(u8Divider<<0);
    else if(u8TimerIdx == TIMER2)
        CGU->TMRCLKDIV = (CGU->TMRCLKDIV &~TCLK_TIMER2_CPUPLL_DIV) |(u8Divider<<4);
    else if(u8TimerIdx == TIMER3)
        CGU->TMRCLKDIV = (CGU->TMRCLKDIV &~TCLK_TIMER3_CPUPLL_DIV) |(u8Divider<<8);
}

