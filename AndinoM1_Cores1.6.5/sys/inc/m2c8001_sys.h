/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_sys.h
 *  \brief M2C8001 System functions prototypes
 *  $Date: 2014-01-08
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

#ifndef M2C8001_SYS_H_
#define M2C8001_SYS_H_
#include "m2c8001.h"
#include "nds32_intrinsic.h"
/***********************************************************************************************
*   MARCOS
************************************************************************************************/




/*APB clock source*/
#define APB_CLK_SRC_XO  0
#define APB_CLK_SRC_CPUPLL  1


/*CPUPLL Frequency under normal mode*/
typedef enum{
    CPUPLL_FREQ_8M = 8,
    CPUPLL_FREQ_16M = 16,
    CPUPLL_FREQ_24M = 24,
    CPUPLL_FREQ_32M = 32,
    CPUPLL_FREQ_48M = 48,
    CPUPLL_FREQ_60M = 60
}CpuPLLFreq_t;

#define CPU_STANDBY __nds32__standby_no_wake_grant



/**************************************************************************************************
 *   GLOBAL PROTOTYPES
 *************************************************************************************************/

CpuPLLFreq_t SYS_GetCpupllFreq(void);
void SYS_SetCpupllFreq(CpuPLLFreq_t freq);

u8 SYS_GetAPBClockSrc(void);
u32 SYS_GetAPBClockFreq(void);

/*For library*/
void SYS_Init(void);
u16 SYS_GetRtcOscCurFreq(void);

#endif /* M2C8001_SYS_H_ */
