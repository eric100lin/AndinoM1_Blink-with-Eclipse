#ifndef M2C8001_ADC_H_
#define M2C8001_ADC_H_

#include "m2c8001.h"

void sarADC_Init(void);
void sarADC_DeInit(void);
void sarADC_Start(void);
u32 sarADC_Read(u8 ch);

#endif