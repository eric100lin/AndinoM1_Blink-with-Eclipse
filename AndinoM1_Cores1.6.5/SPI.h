#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <inttypes.h>
#include "m2c8001.h"

#define CLOCK_SRC  (24000000UL)

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#ifdef __cplusplus
class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    if (__builtin_constant_p(clock)) {
      init_AlwaysInline(clock, bitOrder, dataMode);
    } else {
      init_MightInline(clock, bitOrder, dataMode);
    }
  }
  SPISettings() {
    init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
  }
private:
  void init_MightInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }
  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    __attribute__((__always_inline__)) {

    //uint8_t clockDiv;

    //serial clock generate formula: freq=24MHz/(2*(div+1))
    if (__builtin_constant_p(clock)) {
      if (clock >= CLOCK_SRC / 2) {
        clockDiv = 0;
      } else if (clock >= CLOCK_SRC / 4) {
        clockDiv = 1;
      } else if (clock >= CLOCK_SRC / 6) {
        clockDiv = 2;
      } else if (clock >= CLOCK_SRC / 8) {
        clockDiv = 3;
      } else if (clock >= CLOCK_SRC / 10) {
        clockDiv = 4;
      } else if (clock >= CLOCK_SRC / 12) {
        clockDiv = 5;
      } else {
        clockDiv = 6;
      }
    } else {
      uint32_t clockSetting = CLOCK_SRC / 2;
      clockDiv = 0;
      while (clockDiv < 6 && clock < clockSetting) {
        clockSetting /= (2*(clockDiv+1));
        clockDiv++;
      }
    }
    spiBitOrder = bitOrder;
    spiDataMode = dataMode;
  }
  uint8_t clockDiv;
  uint8_t spiBitOrder;
  uint8_t spiDataMode;
  friend class SPIClass;
};


class SPIClass {
    public:
    	  // Initialize the SPI library
        SPIClass(SPI_TypeDef *pSPIPort);
        void begin();
        void end();
        void beginTransaction(SPISettings settings);
        void endTransaction();
        uint8_t transfer(uint8_t val); // val can be:addr, data, 0(for read)
        uint16_t transfer16(uint16_t val);
        uint32_t transfer32(uint32_t val);
        void setBitOrder(uint8_t order);
        void setClockDivider(uint8_t div);
        void setDataMode(uint8_t mode);
        
    private:
        SPI_TypeDef *SPIPort0;
};

extern SPIClass SPI;
#endif
#endif
