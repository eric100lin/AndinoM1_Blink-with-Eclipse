#ifndef M2C8001_I2C_H_
#define M2C8001_I2C_H_
#include "m2c8001.h"

/*I2C driver retren value*/
#define I2C_RET_TIMEOUT (0)
#define I2C_RET_SUCCESS (1)

/*I2C Mode*/
#define I2C_MODE_MASTER (1)
#define I2C_MODE_SLAVE (2)

/***********************************************************************************************
*   SOC I2C definition
************************************************************************************************/

/********************* Bit definition of I2C control register **********************/
#define I2C_CTRL_RST        (0x1 << 0)  /*Reset I2C controller*/
#define I2C_CTRL_ENABLE     (0x1 << 1)  /*Enable I2C bus interface controller*/
#define I2C_CTRL_SCL_EN     (0x1 << 2)  /*Enable I2C controller clock ouput for master mode*/
#define I2C_CTRL_GC_EN      (0x1 << 3)  /*Enable I2C controller to respondto a general call message as a slave*/
#define I2C_CTRL_START      (0x1 << 4)  /*Generate a start condition*/
#define I2C_CTRL_STOP       (0x1 << 5)  /*Generate a stop condition*/
#define I2C_CTRL_NACK       (0x1 << 6)  /**/
#define I2C_CTRL_TB_EN      (0x1 << 7)  /*I2C controller is ready to receive or transmit one byte*/
#define I2C_CTRL_DTI_EN     (0x1 << 8)  /*It will gernerate  interrupt when DT register has transmitted data to bus*/
#define I2C_CTRL_DRI_EN     (0x1 << 9)  /*It will gernerate interrupt when DR register has received data form bus*/
#define I2C_CTRL_BERRI_EN   (0x1 << 10)
#define I2C_CTRL_STOPI_EN   (0x1 << 11)  /*It will generate interrupt when I2C controller detect STOP condition*/
#define I2C_CTRL_SAMI_EN    (0x1 << 12)
#define I2C_CTRL_ALL_EN     (0x1 << 13)
#define I2C_CTRL_STARI_EN   (0x1 << 14)  /*It will generate interrupt when I2C controller detect STAR condition*/

#define I2C_CTRL_INT_MASK   (0x3F00)

/********************* Bit definition of I2C status register **********************/
#define I2C_STAS_RW      (0x1 << 0)  /*I2C servers in a master-receive or slave-transmit mode*/
#define I2C_STAS_ACK     (0x1 << 1)  /*I2C controller receives or sends non-ack*/
#define I2C_STAS_I2CB    (0x1 << 2)  /*I2C controller is busy*/
#define I2C_STAS_BB      (0x1 << 3)  /*I2C controller is busy,but it's not involved in the transaction*/
#define I2C_STAS_DT      (0x1 << 4)  /*Data Register(DR) transmitted one data byte to I2C bus*/
#define I2C_STAS_DR      (0x1 << 5)  /*Data Register(DR) received  one new data byte from I2C bus*/
#define I2C_STAS_BERR    (0x1 << 6)  /*I2C controller detects non-ACK responses from slave device */
#define I2C_STAS_STOP    (0x1 << 7)  /*I2C controller detects a stop condition*/
#define I2C_STAS_SAM     (0x1 << 8)  /*I2C controller receives a slave address that matches the general call address*/
#define I2C_STAS_GC      (0x1 << 9)  /*I2C controller receives a slave address that matches the address in the slave register(SAR*/
#define I2C_STAS_AL      (0x1 << 10)  /*I2C controller loses arbitration when operating in master mode*/
#define I2C_STAS_START   (0x1 << 11)  /*I2C controller detects a start condition*/


void I2C_Init(u8 u8Mode,u8 u8Div);
void I2C_DeInit(void);
void I2C_SetPCLK(u32 div);
void I2C_Writebyte(u8 u8Data);
u8 I2C_Readbyte(void);
u8 I2C_Write(u8 u8Addr, u8 * pu8Data, u8 u8Len);
u8 I2C_Read(u8 u8Addr, u8 * pu8Data, u8 u8Len);

#endif