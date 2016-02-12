/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_sys.c
 *  \brief M2C8001 system driver
 *  $Date: 2013-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */


/***********************************************************************************************
*   INCLUDES
************************************************************************************************/
#include "platform.h"
#include "m2c8001_sys.h"

/***********************************************************************************************
*   MARCOS
************************************************************************************************/


/***********************************************************************************************
*   GLOBAL VARIABLES
************************************************************************************************/


/***********************************************************************************************
*   LOCAL FUNCTIONS
************************************************************************************************/


/***********************************************************************************************
*   GLOBAL FUNCTIONS
************************************************************************************************/


/***********************************************************************************************
@brief:Get CPUPLL Current Frequency
@para:
        -freq: CPUPLL Frequency
@ret: CPUPLL  Frequency
***********************************************************************************************/
CpuPLLFreq_t SYS_GetCpupllFreq(void)
{
    u32 cpupllRegVal = CGU->CPUPLLCFG ;
    CpuPLLFreq_t freq;
    u8 oDiv = 0;
    u8 fbDiv;
    u8 RefFreq = 4;/*4MHZ*/

    fbDiv = (cpupllRegVal & CPUPLL_CFG_FBDIV) >> 2;
    oDiv = (cpupllRegVal & CPUPLL_CFG_ODIV) >> 13;

    freq=(fbDiv*RefFreq) >>oDiv;
    return freq;
}


/***********************************************************************************************
@brief:Set CPUPLL Frequency
@para:
        -freq: CPUPLL Frequency
***********************************************************************************************/
void SYS_SetCpupllFreq(CpuPLLFreq_t freq)
{
    u8 oDiv = 0;
    u8 fbDiv;
    u8 RefFreq = 4;
    u32 cpupllRegVal = CGU->CPUPLLCFG ;
    switch(freq){
        case CPUPLL_FREQ_8M:
             oDiv = 4;
             break;
        case CPUPLL_FREQ_16M:
        case CPUPLL_FREQ_24M:
             oDiv = 3;
             break;
        case CPUPLL_FREQ_32M:
        case CPUPLL_FREQ_48M:
        case CPUPLL_FREQ_60M:
             oDiv = 2;
             break;
        default:
            return;
    }
    fbDiv = freq*(0x1<<oDiv)/RefFreq;

     /*Set Register*///
    cpupllRegVal = (cpupllRegVal &~ CPUPLL_CFG_FBDIV) |(fbDiv << 2);

    cpupllRegVal = (cpupllRegVal &~ CPUPLL_CFG_ODIV) |(oDiv << 13);

    cpupllRegVal &= ~CPUPLL_CFG_CALPLL;
    cpupllRegVal &= ~CPUPLL_CFG_PREDIV;
    CGU->CPUPLLCFG = cpupllRegVal;
}


/***********************************************************************************************
@brief:Get APB clock Source
@para:
@ret: APB clock source (APB_CLK_SRC_XO/APB_CLK_SRC_CPUPLL)
***********************************************************************************************/
u8 SYS_GetAPBClockSrc(void)
{
    u8 clkSrc = APB_CLK_SRC_XO;
    if((CGU->DIPCLKSEL & DIP_CLK_SEL_APB_MASK) == DIP_CLK_SEL_APB_CPUPLL)
        clkSrc = APB_CLK_SRC_CPUPLL;
    return clkSrc;
}


/***********************************************************************************************
@brief:Get APB clock Frequency
@para:
@ret: APB clock Frequency(Hz)
***********************************************************************************************/
u32 SYS_GetAPBClockFreq(void)
{
    u32 clk = __XTAL;
    switch(CGU->DIPCLKSEL & DIP_CLK_SEL_APB_MASK){
        case DIP_CLK_SEL_APB_XO:
            clk = __XTAL;
            break;
        case DIP_CLK_SEL_APB_32K:
            clk = __RTC_32K;
            break;
        case DIP_CLK_SEL_APB_CPUPLL:
            clk = SYS_GetCpupllFreq()*MHz;
            break;
    }
    return clk;
}

