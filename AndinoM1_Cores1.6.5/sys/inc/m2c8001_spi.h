#ifndef M2C8001_SPI_H_
#define M2C8001_SPI_H_
#include "m2c8001.h"

typedef struct
{
    u8 u8Mode;/*SPI Mode: Maste/Slave*/
    u8 u8Div;   /*SPI clock divider*/
    u8 u8ClkPhase;  /*SPI clock phase*/
    u8 u8ClkPolarity; /*SPI clock polarity*/
}SPI_DATA_t;

#define SPI_DRV_MODE_MASTER (1)
#define SPI_DRV_MODE_SLAVE  (0)
/*SPI clock polarity*/
#define SPI_DRV_CLKPO_HIGH (1) /*Clock remain high when SPI is idle*/
#define SPI_DRV_CLKPO_LOW  (0) /*Clock remain low when SPI is idle*/

/*SPI clock phase*/
#define SPI_DRV_CLKPH_HALF (1)
#define SPI_DRV_CLKPH_ONE  (0)

/********************* Bit definition of SSP control register0(0x0) **********************/
#define SSP_CTRL0_SCLKPH		(0x1 << 0)  /*Clock phase*/
#define SSP_CTRL0_SCLKPO		(0x1 << 1)  /*Clock polarity*/

#define SSP_CTRL0_OPM_SLAVE	(0x1 << 2)
#define SSP_CTRL0_OPM_MASTER	(0x3 << 2)
#define SSP_CTRL0_OPM_MASK	(0x3 << 2)

#define SSP_CTRL0_TXDMY_NUM     (0xF0000)  /*Set dummy cycle numbers*/
#define SSP_CTRL0_MANUAL_EN     (0x1 << 20)  /*Manual CS PIN enable*/
#define SSP_CTRL0_MANUAL_VAL    (0x1 << 21)  /*Manual CS VAL*/

#define SSP_CTRL0_FFMT_SPI			(0x1 << 12)  /*Frame format:SPI*/
#define SSP_CTRL0_FFMT_MIC			(0x2 << 12)  /*Frame format:MICROWIRE*/
#define SSP_CTRL0_FFMT_I2S			(0x3 << 12)  /*Frame format:I2S*/

/********************* Bit definition of SSP control register1(0x4) **********************/
#define SSP_CTRL1_DIV		(0xFFFF)
#define SSP_CTRL1_SDL		(0x1F0000)
#define SSP_CTRL1_PDL		(0x1F000000)
/********************* Bit definition of SSP control register2(0x8) **********************/
#define SSP_CTRL2_SSPEN		(0x1 << 0)  /*SSP enable*/
#define SSP_CTRL2_TXDOE		(0x1 << 1)  /*Transmit data output enable*/
#define SSP_CTRL2_RXFCLR		(0x1 << 2)  /*Receive FIFO clear*/
#define SSP_CTRL2_TXFCLR		(0x1 << 3)  /*Transmit FIFO clear*/
#define SSP_CTRL2_ACWRST		(0x1 << 4)  /*AC-link warm reset enable*/
#define SSP_CTRL2_ACCRST		(0x1 << 5)  /*AC-link cold reset enable*/
#define SSP_CTRL2_SSPRST		(0x1 << 6)  /*SSP reset*/
/********************* Bit definition of SSP status register(0x0C) **********************/
#define SSP_STAS_REF		(0x1 << 0)  /*Receive FIFO full*/
#define SSP_STAS_TFNF		(0x1 << 1)  /*Transmit FIFO not full*/
#define SSP_STAS_BUSY		(0x1 << 2)  /*Busy indicator*/
#define SSP_STAS_RFVF		(0xF0)  /*Receive FIFO valid entries*/
#define SSP_STAS_TFVF		(0xF000)  /*Transmit FIFO valid entries*/

void SPI_EnableManualCS(SPI_TypeDef *spiPort);
void SPI_DisableManualCS(SPI_TypeDef *spiPort);
void SPI_SetCS(SPI_TypeDef *spiPort);
void SPI_ClrCS(SPI_TypeDef *spiPort);
void SPI_SetBitLength(SPI_TypeDef *spiPort,u8 u8Len);
void SPI_StartTransfer(SPI_TypeDef *spiPort,u32 u32Data);
u8 SPI_IsBusy(SPI_TypeDef *spiPort);
u32 SPI_ReadRxFIFO(SPI_TypeDef *spiPort);
void SPI_WriteTxFIFO(SPI_TypeDef *spiPort,u32 u32Data);
void SPI_ClrRxFIFO(SPI_TypeDef *spiPort);
void SPI_SetClockFreq(SPI_TypeDef *spiPort,u8 u8Div);
void SPI_Init(SPI_TypeDef *spiPort,SPI_DATA_t *tParam);
void SPI_DeInit(SPI_TypeDef *spiPort);
void SPI_SetSPIDataMode(SPI_TypeDef *spiPort, u8 dataMode);
void SPI_Settings(SPI_TypeDef *spiPort, u8 div, u8 dataMode);
u32 SPI_Transfer(SPI_TypeDef *spiPort, u8 bitlen, u32 data);

#endif