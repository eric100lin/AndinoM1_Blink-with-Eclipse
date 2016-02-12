/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_timer.h
 *  \brief M2C8001 Timer functions prototypes
 *  $Date: 2014-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */


#ifndef M2C8001_TIMER_H_
#define M2C8001_TIMER_H_

#include "m2c8001.h"

/***********************************************************************************************
*   MARCOS
************************************************************************************************/
#define TIMER1  (1)
#define TIMER2  (2)
#define TIMER3  (3)

#define TIMER_CLK_SRC_32K   (1)
#define TIMER_CLK_SRC_APB   (2)
#define TIMER_CLK_SRC_XO    (3)
#define TIMER_CLK_SRC_CPULL (4)


#define TIMER_MODE_ONESHOT (1)
#define TIMER_MODE_CONTINUE (0)


/***********************************************************************************************
*   TYPEDEFS
************************************************************************************************/
typedef void (DRVTIMER_Callback)(u32 u32IntSts);



/***********************************************************************************************
*   SOC Timer definition
************************************************************************************************/

/********************* Bit definition of Timer control register **********************/
#define TIMER_CTRL_TM1EN		(0x1 << 0)	/*Timer1 enable  */
#define TIMER_CTRL_TM1CLK		(0x1 << 1)	/*Timer1 clock :1/EXT1CLK, 0/PCLK*/
#define TIMER_CTRL_TM1OFE		(0x1 << 2)	/*Timer1 enable overflow interrupt*/
#define TIMER_CTRL_TM2EN		(0x1 << 3)	/*Timer2 enable */
#define TIMER_CTRL_TM2CLK		(0x1 << 4)	/*Timer2 clock :1/EXT1CLK, 0/PCLK*/
#define TIMER_CTRL_TM2OFE		(0x1 << 5)	/*Timer2 enable overflow interrupt*/
#define TIMER_CTRL_TM3EN		(0x1 << 6)	/*Timer3 enable */
#define TIMER_CTRL_TM3CLK		(0x1 << 7)	/*Timer3 clock :1/EXT1CLK, 0/PCLK*/
#define TIMER_CTRL_TM3OFE		(0x1 << 8)	/*Timer3 enable overflow interrupt*/
#define TIMER_CTRL_TM1UP		(0x1 << 9)	/*Timer1 up or down countt*/
#define TIMER_CTRL_TM2UP		(0x1 << 10)	/*Timer2 up or down countt*/
#define TIMER_CTRL_TM3UP		(0x1 << 11)	/*Timer3 up or down countt*/


/********************* Bit definition of Timer mask register **********************/
#define TIMER_MASK_TM1MH1		(0x1 << 0)	/*Mask Time1 Match1 interrupt */
#define TIMER_MASK_TM1MH2		(0x1 << 1)	/*Mask Time1 Match2 interrupt */
#define TIMER_MASK_TM1OFE		(0x1 << 2)	/*Mask Time1 Overflow interrupt */
#define TIMER_MASK_TM2MH1		(0x1 << 3)	/*Mask Time2 Match1 interrupt */
#define TIMER_MASK_TM2MH2		(0x1 << 4)	/*Mask Time2 Match2 interrupt */
#define TIMER_MASK_TM2OFE		(0x1 << 5)	/*Mask Time2 Overflow interrupt */
#define TIMER_MASK_TM3MH1		(0x1 << 6)	/*Mask Time3 Match1 interrupt */
#define TIMER_MASK_TM3MH2		(0x1 << 7)	/*Mask Time3 Match2 interrupt */
#define TIMER_MASK_TM3OFE		(0x1 << 8)	/*Mask Time3 Overflow interrupt */



/**************************************************************************************************
 *   GLOBAL PROTOTYPES
 *************************************************************************************************/
void TIMER_IsrInit(u8 u8TimerIdx);
void TIMER_Init(u8 u8TimerIdx,u8 u8ClkSrc,u32 u32LoadCnt);
void TIMER_DeInit(u8 u8TimerIdx);
void TIMER_Start(u8 u8TimerIdx);
void TIMER_Stop(u8 u8TimerIdx);
void TIMER_SetMatchValue(u8 u8TimerIdx,u32 u32Match1,u32 u32Match2);
void TIMER_RegisterCallback(u8 u8TimerIdx,DRVTIMER_Callback cb);
void TIMER_EnableInt(u8 u8TimerIdx);
void TIMER_DisableInt(u8 u8TimerIdx);
void TIMER_SetCpupllDivider(u8 u8TimerIdx,u8 u8Divider);
u32 TIMER_GetCounter(u8 u8TimerIdx);






#endif /* M2C8001_TIMER_H_ */
