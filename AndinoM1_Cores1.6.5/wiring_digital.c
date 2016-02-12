/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

uint32_t pin_dmux[14]={20,19,23,24,3,18,7,10,1,2,28,25,26,27};

void pinMode( int pin_m, uint8_t mode )
{
    uint32_t pin = pin_dmux[pin_m];
    if (mode == INPUT)
    {
        GPIO_SetPinMux(pin);
        GPIO_SetDir(pin, GPIO_INPUT);
    }
    else if (mode == INPUT_PULLUP)
    {
        GPIO_SetPinMux(pin);
        GPIO_SetDir(pin, GPIO_INPUT);
        GPIO_SetInputType(pin, INPUT_PULLUP);
    }
    else if (mode == OUTPUT)
    {
        GPIO_SetPinMux(pin);
        GPIO_SetDir(pin, GPIO_OUTPUT);
    }
}

void digitalWrite( int pin_m, uint8_t value )
{
    uint32_t pin = pin_dmux[pin_m];
    GPIO_SetOutput(pin, value);
}

int digitalRead( int pin_m )
{
    uint32_t pin = pin_dmux[pin_m];
    return GPIO_GetBit(pin);
}


