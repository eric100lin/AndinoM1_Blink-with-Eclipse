/*!
 **************************************************************************************************
 *  \copyright
 *    Copyright (c) 2012-2013 M-Square Comm.
 *    This software is the proprietary information of M2C Comm.
 *    All Right Reserved.
 **************************************************************************************************
 *  \file m2c8001_gpio.c
 *  \brief M2C8001 GPIO driver
 *  $Date: 2014-04-14
 *
 *
 * ------------------------------------------------------------------------------------------------
 */

/***********************************************************************************************
 *   INCLUDES
 ************************************************************************************************/
#include "m2c8001_gpio.h"
#include "m2c8001_int.h"

/***********************************************************************************************
 *   MARCOS
 ************************************************************************************************/


/***********************************************************************************************
 *   GLOBAL VARIABLES
 ************************************************************************************************/
DRVGPIO_Callback *gGpioCallback;

/***********************************************************************************************
 *   LOCAL FUNCTIONS
 ************************************************************************************************/
void GPIO_Isr(int unused)
{
    /*Read the GPIO masked interrupt status  to check the gpio pin. */
    int status = GPIO->IMS;

    GPIO->IC = status; /*Clear GPIO interrupt status*/
    if (gGpioCallback)
        gGpioCallback(status);
}

/***********************************************************************************************
 *   GLOBAL FUNCTIONS
 ************************************************************************************************/
void GPIO_IsrInit(void)
{
    INT_FiqEn(1 << FIQ_GPIO_INTR, 0, 0);
    ISR_InsertCb(INT_TYPE_FIQ, FIQ_GPIO_INTR, GPIO_Isr);
}

/***********************************************************************************************
 @brief:Set GPIO specified port direction
 @para:
 -u8Idx: Specified GPIO port
 -u8Val: GPIO_INPUT/GPIO_OUTPUT
 ***********************************************************************************************/
void GPIO_SetDir(u8 u8Idx, u8 u8Dir)
{
    if (u8Dir == GPIO_OUTPUT)
        GPIO->DIR |=(1 << u8Idx);
    else
        GPIO->DIR &=~(1 << u8Idx);
}

/***********************************************************************************************
 @brief:Get the pin value from the specified input GPIO pin.
 @para:
 -u8Bit: Specified GPIO port
 -u8Dir: GPIO_INPUT/GPIO_OUTPUT
 ***********************************************************************************************/
u8 GPIO_GetBit(u8 u8Idx)
{
    return ((GPIO->DIN >> u8Idx) & 0x1);
}

/***********************************************************************************************
 @brief:Set GPIO specified port output value
 @para:
 -u8Bit: Specified GPIO port
 -u8Dir: GPIO_OUT_HIGH/GPIO_OUT_LOW
 ***********************************************************************************************/
void GPIO_SetOutput(u8 u8Idx, u8 u8Val)
{
    if (u8Val == GPIO_OUT_HIGH)
        GPIO->DOUT |=(1 <<u8Idx);
    else
        GPIO->DOUT &= ~(1 <<u8Idx);
}

void GPIO_SetInputType(u8 u8Idx, u8 u8Val)
{
    /* Input as pullup mode. */
    if (u8Val == 2)	{
        GPIO->PUE |=(1 <<u8Idx);
        GPIO->PUT |=(1 <<u8Idx);
    }
}

void GPIO_SetPinMux(u8 idx)
{
    if(idx < 16)/*GPIO 0~15*/
        TOP->PADMUX0 = TOP->PADMUX0 & ~(0x3 << (idx*2));
    else if(idx < 19) /*GPIO 16,17,18*/
        TOP->PADMUX1 = TOP->PADMUX1 & ~(0x3 << ((idx & 0xF)*2));
    else if (idx < 29) /*GPIO 19~28*/
        TOP->PADMUX1 = (TOP->PADMUX1 & ~(0x3 << ((idx & 0xF) * 2)))
            | (0x1 << ((idx & 0xF) * 2));
}


/***********************************************************************************************
 @brief:Enable GPIO specified PIN interrupt
 @para:
 -u8Idx: Specified GPIO port
 -u8Type:Trigger type(GPIO_TRIG_LEVEL/GPIO_TRIG_EDGE)
 -u8Mode:GPIO_FALLING_LOW/GPIO_RISING_HIGH
 ***********************************************************************************************/
void GPIO_EnableInt(u8 u8Idx, u8 u8TrigType, u8 u8Mode, u8 u8Both)
{
    /*Edge or Level trigger */
    if (u8TrigType == GPIO_TRIG_LEVEL)
        GPIO->IT |= (1 <<u8Idx);
    else
        GPIO->IT &= ~(1 <<u8Idx);

    /*Falling/Rising edge */
    if(u8Mode == GPIO_FALLING_LOW)
        GPIO->IR |= (1 <<u8Idx);
    else
        GPIO->IR &= ~(1 <<u8Idx);

    /*Single/Both edge */
    if(u8Both == 1)
        GPIO->IB |= (1 <<u8Idx);
    else
        GPIO->IB &= ~(1 <<u8Idx);
    /*Enable GPIO interrupt*/
    GPIO->IE |= (1 <<u8Idx);
}

/***********************************************************************************************
 @brief:Disable interrupt function of GPIO specified PIN
 @para:
 -u8Idx: Specified GPIO port
 ***********************************************************************************************/
void GPIO_DisableInt(u8 u8Idx)
{
    GPIO->IE &= ~(1 << u8Idx);
}

/***********************************************************************************************
 @brief:Register GPIPO interrupt callback function
 @para:
 -cb: GPIO callback function
 ***********************************************************************************************/
void GPIO_RegisterCallback(DRVGPIO_Callback *cb)
{
    gGpioCallback = cb;
}

void AGPIO_ENA(u8 pin)
{
    //TOP->AGPIOCTRL0 &= ~(AGPIO_AEN_ADGPIO1_2|AGPIO_AEN_ADGPIO3_4);
    switch(pin)
    {
        case 0:
        case 1:
            TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO1_2;
            break;
        case 2:
        case 3:
        	 TOP->AGPIOCTRL0 |= AGPIO_AEN_ADGPIO3_4;
        	 break;
    }
}

void AGPIO_DIS(u8 pin)
{ 
    switch(pin)
    {
        case 0:
        case 1:
            TOP->AGPIOCTRL0 &= ~AGPIO_AEN_ADGPIO1_2;
            break;
        case 2:
        case 3:
        	 TOP->AGPIOCTRL0 &= ~AGPIO_AEN_ADGPIO3_4;
        	 break;
    }
}

void AGPIO_ENA_SAR_Func(u8 pin)
{ 
    //TOP->AGPIOCTRL0 &= ~0xFF;
    TOP->AGPIOCTRL0 |= (0x03 << (pin*2));
}

void AGPIO_DIS_SAR_Func(u8 pin)
{
    TOP->AGPIOCTRL0 &= ~(0x03 << (pin*2));
}
