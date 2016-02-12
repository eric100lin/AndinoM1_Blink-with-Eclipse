#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
#include "SPI.h"

#define SPI_DATA_LEN_8BITS     8
#define SPI_DATA_LEN_16BITS    16
#define SPI_DATA_LEN_32BITS    32

SPIClass SPI(SPI0);

SPIClass::SPIClass(SPI_TypeDef *pSPIPort)
{
    SPIPort0 = pSPIPort;
}

void SPIClass::begin()
{
    SPI_SetCS(SPIPort0);  //Set CS to Low
}

void SPIClass::end()
{
    SPI_ClrCS(SPIPort0);  //Set CS to High
}

void SPIClass::beginTransaction(SPISettings settings)
{
    uint8_t div = settings.clockDiv;  //maxmux freq:12MHz
    //uint8_t bitorder = settings.spiBitOrder; //only MSB First
    /*|------------------|
      |SPI_MODE|CPOL|CPHA|
      |------------------|
      |    0   |  0 |  0 |
      |------------------|
      |    1   |  0 |  1 |
      |------------------|
      |    2   |  1 |  0 |
      |------------------|
      |    3   |  1 |  1 |
      |------------------|*/
    uint8_t datmode = settings.spiDataMode;
    
    SPI_Settings(SPIPort0, div, datmode);
}

void SPIClass::endTransaction()
{  
    SPI_DeInit(SPIPort0);
}

uint8_t SPIClass::transfer(uint8_t val)
{
    return SPI_Transfer(SPIPort0,SPI_DATA_LEN_8BITS,val);
}

uint16_t SPIClass::transfer16(uint16_t val)
{
    return SPI_Transfer(SPIPort0,SPI_DATA_LEN_16BITS,val);
}

uint32_t SPIClass::transfer32(uint32_t val)
{
    return SPI_Transfer(SPIPort0,SPI_DATA_LEN_32BITS,val);
}

void SPIClass::setBitOrder(uint8_t order)
{
    //do nothing, only MSB First
    return;
}

void SPIClass::setClockDivider(uint8_t div)
{
    SPI_SetClockFreq(SPIPort0, div);
}

void SPIClass::setDataMode(uint8_t mode)
{
    SPI_SetSPIDataMode(SPIPort0, mode);
}
