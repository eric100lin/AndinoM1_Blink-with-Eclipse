/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h
#include <inttypes.h>
#include "Stream.h"
#ifdef __cplusplus
extern "C"{
#include "m2c8001.h"
} // extern "C"
#endif // __cplusplus
// Define config for Serial.begin(baud, config);
// SERIAL_8N1 0x300 = UART_DRV_DATABITS_8 << 8 | UART_DRV_PARITY_NONE << 4 | UART_DRV_STOPBITS_1
#define SERIAL_5N1 0x000
#define SERIAL_6N1 0x100
#define SERIAL_7N1 0x200
#define SERIAL_8N1 0x300
#define SERIAL_5N2 0x001
#define SERIAL_6N2 0x101
#define SERIAL_7N2 0x201
#define SERIAL_8N2 0x301
#define SERIAL_5E1 0x030
#define SERIAL_6E1 0x130
#define SERIAL_7E1 0x230
#define SERIAL_8E1 0x330
#define SERIAL_5E2 0x031
#define SERIAL_6E2 0x131
#define SERIAL_7E2 0x231
#define SERIAL_8E2 0x331
#define SERIAL_5O1 0x010
#define SERIAL_6O1 0x110
#define SERIAL_7O1 0x210
#define SERIAL_8O1 0x310
#define SERIAL_5O2 0x011
#define SERIAL_6O2 0x111
#define SERIAL_7O2 0x211
#define SERIAL_8O2 0x311

class HardwareSerial : public Stream
{
  public:
    HardwareSerial(UART_TypeDef *pUartConsole);
    void begin(uint32_t);
    void begin(uint32_t, uint32_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() { return true; }
  private:
    UART_TypeDef *UartConsole;
};
extern HardwareSerial Serial;
#endif
