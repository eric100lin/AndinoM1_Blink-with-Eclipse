/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_gpio.h
 *  \brief M2C8001 GPIO functions prototypes
 *  $Date: 2014-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

#ifndef M2C8001_GPIO_H_
#define M2C8001_GPIO_H_
#include "m2c8001.h"

/***********************************************************************************************
*   TYPEDEFS
************************************************************************************************/
typedef void (DRVGPIO_Callback)(u32);


/***********************************************************************************************
*   MARCO
************************************************************************************************/
#define GPIO_INPUT 		(0)
#define GPIO_OUTPUT 	(1)

#define GPIO_OUT_LOW 	(0)
#define GPIO_OUT_HIGH 	(1)

#define GPIO_PULL_LOW 	(0)
#define GPIO_PULL_HIGH 	(1)

#define GPIO_TRIG_EDGE 	(1)	/*Edge Trigger*/
#define GPIO_TRIG_LEVEL (0)	/*Level Trigger*/

#define GPIO_FALLING_LOW	(1)
#define GPIO_RISING_HIGH	(0)


/**************************************************************************************************
 *   GLOBAL PROTOTYPES
 *************************************************************************************************/
void GPIO_IsrInit(void);
void GPIO_SetDir(u8 u8Idx, u8 u8Dir);
u8 GPIO_GetBit(u8 u8Idx);
void GPIO_SetOutput(u8 u8Idx, u8 u8Val);
void GPIO_SetInputType(u8 u8Idx, u8 u8Val);
void GPIO_SetPinMux(u8 idx);
void GPIO_RegisterCallback(DRVGPIO_Callback *cb);
void GPIO_EnablePullup(u8 u8Idx,u8 u8Type);
void GPIO_DisablePullup(u8 u8Idx);
void GPIO_EnableInt(u8 u8Idx,u8 u8TrigType,u8 u8Mode,u8 u8Both);
void GPIO_DisableInt(u8 u8Idx);

void AGPIO_ENA(u8 pin);
void AGPIO_DIS(u8 pin);
void AGPIO_ENA_SAR_Func(u8 pin);
void AGPIO_DIS_SAR_Func(u8 pin);

#endif /* M2C8001_GPIO_H_ */
