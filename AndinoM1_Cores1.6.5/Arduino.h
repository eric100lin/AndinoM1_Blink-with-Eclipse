/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Arduino_h
#define Arduino_h

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus
#include "m2c8001.h"
#include "m2c8001_sys.h"
#include "m2c8001_int.h"
#include "m2c8001_uart.h"
#include "m2c8001_timer.h"
#include "m2c8001_gpio.h"
#include "m2c8001_adc.h"
#include "m2c8001_pwm.h"
#include "m2c8001_spi.h"
#include "m2c8001_i2c.h"
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <nds32_intrinsic.h>
#include <stdbool.h>
#include <avr/pgmspace.h>


/* sketch */
extern void setup( void ) ;
extern void loop( void ) ;


#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define NOT_AN_INTERRUPT -1

#define LOW 0
#define HIGH 1
#define CHANGE 2
#define FALLING 3
#define RISING 4

#define DEFAULT 1
#define EXTERNAL 0

#define BIN 2
#define OCT 8
#define DEC 10
#define HEX 16

// undefine stdlib's abs if encountered
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif // min

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif // max

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define interrupts() __nds32__gie_en()
#define noInterrupts() __nds32__gie_dis()

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

#define LSBFIRST 0
#define MSBFIRST 1
typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;

#ifdef __cplusplus
#include "WString.h"
#include "WCharacter.h"
#include "HardwareSerial.h"
#include "WMath.h"
extern "C"{
#endif // __cplusplus

/* Digital I/O */
void pinMode(int, uint8_t);
void digitalWrite(int, uint8_t);
int digitalRead(int);

/* Analog I/O */
void analogReference(uint8_t mode);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int val);
void analogReadResolution(uint8_t bit);
void analogWriteResolution(uint8_t bit);

/* Advanced I/O */
void noTone(uint8_t pin);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);


/* External interrupt */
void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode);
void detachInterrupt(uint32_t pin);

/* Time function */
void TIMER1_init(void);
void delay(uint32_t);
uint32_t millis(void);
uint32_t micros(void);
void delayMicroseconds(uint32_t);
/* GPIO pin numbers. */
typedef enum {
	D0 = 0,
	D1 = 1,
	D2 = 2,
	D3 = 3,
	D4 = 4,
	D5 = 5,
	D6 = 6,
	D7 = 7,
	D8 = 8,
	D9 = 9,
	D10 = 10,
	D11 = 11,
	D12 = 12,
	D13 = 13,
	A0 = 0,
	A1 = 1,
	A2 = 2,
	A3 = 3,
	A4 = 4,
	A5 = 5,
} PinName;


/* M2C8001 specific APIs. */
extern void System_init( void );

#ifdef __cplusplus
void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
} // extern "C"
#endif // __cplusplus

#endif // Arduino_h
