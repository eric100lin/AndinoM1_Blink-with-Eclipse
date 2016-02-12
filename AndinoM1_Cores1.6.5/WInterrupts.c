/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

static int first_attach_func =0;
uint32_t pin_imux[14]={20,19,23,24,3,18,7,10,1,2,28,25,26,27};

struct gpio_struct
{
    void (*interrupt_func)(void);
};

struct gpio_struct gpio_table[32];

void GPIO_Callback(u32 int_status_bit)
{
    uint32_t int_pin;
    int i;
    void (*int_func)(void);
    int_pin = 0xFF;
    /* Find interrupt pin */
    for ( i = 0; i < 32 ; i++) {
        if (((int_status_bit >> i) & 0x1) == 1) {
            int_pin = i;
            break;
        }
    }
    if (int_pin < 32) {
        /* Execute interrupt function */
        int_func = gpio_table[int_pin].interrupt_func;
        int_func();
    }
}

void attachInterrupt(uint32_t pin_m, void (*callback)(void), uint32_t mode)
{
    uint32_t pin = pin_imux[pin_m];
    /* Setup callback function at first time */
    if (first_attach_func == 0){
        GPIO_RegisterCallback(GPIO_Callback);
        first_attach_func += 1;
    }
    /* Setup GPIO mode */
    GPIO_SetPinMux(pin);
    GPIO_SetDir(pin, GPIO_INPUT);
    /* Register Interrupt callback function */
    gpio_table[pin].interrupt_func = callback;
    /* Enable GPIO interrupt */
    if (mode == LOW)
        GPIO_EnableInt(pin, GPIO_TRIG_LEVEL, GPIO_FALLING_LOW, 0);
    else if (mode == CHANGE)
        GPIO_EnableInt(pin, GPIO_TRIG_EDGE, GPIO_FALLING_LOW, 1);
    else if (mode == RISING)
        GPIO_EnableInt(pin, GPIO_TRIG_EDGE, GPIO_RISING_HIGH, 0);
    else if (mode == FALLING)
        GPIO_EnableInt(pin, GPIO_TRIG_EDGE, GPIO_FALLING_LOW, 0);
    else if (mode == HIGH)
        GPIO_EnableInt(pin, GPIO_TRIG_LEVEL, GPIO_RISING_HIGH, 0);
}
void detachInterrupt(uint32_t pin_m)
{
    uint32_t pin = pin_imux[pin_m];
    /* Disable Interrupt */
    GPIO_DisableInt(pin);
}
