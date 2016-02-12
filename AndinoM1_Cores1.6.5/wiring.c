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

#ifdef __cplusplus
extern "C" {
#endif

volatile uint32_t us_time = 0;
volatile uint32_t ms_time = 0;

void TIMER1_Callback(u32 u32Sts)
{
    uint32_t us_time_unit;
    uint32_t ms_time_unit;
    /* Timer overflow, add time period to global timer counter */
    us_time_unit = SYS_GetAPBClockFreq() / 1000000;
    us_time += 0xffffffff / us_time_unit;
    ms_time_unit = SYS_GetAPBClockFreq() / 1000;
    ms_time += 0xffffffff / ms_time_unit;
}

void TIMER1_init(void) {
    /* Register callback fuction */
    TIMER_RegisterCallback(TIMER1, TIMER1_Callback);
    /* Initial timer */
    CGU->IIPCLKSW |= IIP_EN_TIMER1_CLK;
    TIMER->TM1COUNTER = 0;
    TIMER->TM1LOAD = 0;
    /* Count up */
    TIMER->TMCR |= TIMER_CTRL_TM1UP;
    /* Internal clock */
    TIMER->TMCR &= ~TIMER_CTRL_TM1CLK;
    /* Enable Interrupts */
    TIMER_EnableInt(TIMER1);
    /* Start timer */
    TIMER_Start(TIMER1);
}

uint32_t us_ticker_read(void) {
    uint32_t tm1_cntr;
    uint32_t us_time_unit;
    us_time_unit = SYS_GetAPBClockFreq() / 1000000;
    tm1_cntr = TIMER->TM1COUNTER / us_time_unit;
    return tm1_cntr;
}

void delay(uint32_t ms) {
    volatile uint32_t start;
    start = millis();
    while ((millis() - start) < ms);
}

uint32_t millis( void ) {
    uint32_t ms_time_tmp;
    ms_time_tmp = (uint32_t) us_ticker_read() / 1000;
    return ms_time + ms_time_tmp;
}

uint32_t micros( void ) {
    uint32_t us_time_tmp;
    us_time_tmp = (uint32_t) us_ticker_read();
    return us_time + us_time_tmp;
}

void delayMicroseconds(uint32_t usec) {
    volatile uint32_t start;
    start = micros();
    while ((micros() - start) < usec);
}
#ifdef __cplusplus
}
#endif
