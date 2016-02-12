#include "m2c8001_spi.h"

void SPI_EnableManualCS(SPI_TypeDef *spiPort)
{
    spiPort->CR0 |=SSP_CTRL0_MANUAL_EN; 
}

void SPI_DisableManualCS(SPI_TypeDef *spiPort)
{
    spiPort->CR0 &= ~SSP_CTRL0_MANUAL_EN; 
}

void SPI_SetCS(SPI_TypeDef *spiPort)
{
    spiPort->CR0 &= ~SSP_CTRL0_MANUAL_VAL; 
}

void SPI_ClrCS(SPI_TypeDef *spiPort)
{
    spiPort->CR0 |= SSP_CTRL0_MANUAL_VAL; 
}

void SPI_SetBitLength(SPI_TypeDef *spiPort,u8 u8Len)
{
    u8 len = (u8Len - 1) & 0x1F;
    spiPort->CR1 = (spiPort->CR1 & ~SSP_CTRL1_SDL) | (len << 16);
}

void SPI_StartTransfer(SPI_TypeDef *spiPort,u32 u32Data)
{
    spiPort->DR = u32Data;
    spiPort->CR2 |= (SSP_CTRL2_SSPEN | SSP_CTRL2_TXDOE);
}

u8 SPI_IsBusy(SPI_TypeDef *spiPort)
{
    return((spiPort->SR & SSP_STAS_BUSY) ? 1:0);
}

u32 SPI_ReadRxFIFO(SPI_TypeDef *spiPort)
{
    return spiPort->DR;
}

void SPI_WriteTxFIFO(SPI_TypeDef *spiPort,u32 u32Data)
{
     spiPort->DR = u32Data;
}

void SPI_ClrRxFIFO(SPI_TypeDef *spiPort)
{
    spiPort->CR2 |= SSP_CTRL2_RXFCLR;
}

void SPI_SetClockFreq(SPI_TypeDef *spiPort,u8 u8Div)
{
/* SPI clock PCLK/(2*(divider+1)) */
     spiPort->CR1 = (spiPort->CR1 &~SSP_CTRL1_DIV) | u8Div;
}

void SPI_Init(SPI_TypeDef *spiPort,SPI_DATA_t *tParam)
{
    if((u32)spiPort == SPI0_BASE){
        RCU->CSRSWRSTN &= ~RCU_SW_RST_SPI0;
        CGU->PIPCLKSW |= (PIP_EN_SSP0_CLK|PIP_EN_SSP0_APBCLK); //Enable SPI0 clock
    }
    else if((u32)spiPort == SPI1_BASE){
        RCU->CSRSWRSTN &= ~RCU_SW_RST_SPI1;
        CGU->PIPCLKSW |= (PIP_EN_SSP1_CLK|PIP_EN_SSP1_APBCLK); //Enable SPI1 clock
    }
    //SPI_IsrInit(spiPort);//Init SPI ISR callback

    if(tParam->u8Mode == SPI_DRV_MODE_MASTER){/*Master*/
        spiPort->CR0 = SSP_CTRL0_FFMT_SPI | SSP_CTRL0_OPM_MASTER;
        SPI_SetClockFreq(spiPort,tParam->u8Div);
    }
    else{/*Slave*/
        spiPort->CR0 = SSP_CTRL0_FFMT_SPI | SSP_CTRL0_OPM_SLAVE;
        spiPort->CR2 = SSP_CTRL2_SSPEN | SSP_CTRL2_TXDOE;
    }
    if(tParam->u8ClkPhase == SPI_DRV_CLKPH_HALF)
        spiPort->CR0 |= SSP_CTRL0_SCLKPH;
    if(tParam->u8ClkPolarity == SPI_DRV_CLKPO_HIGH)
        spiPort->CR0 |= SSP_CTRL0_SCLKPO;
}

void SPI_DeInit(SPI_TypeDef *spiPort)
{
    if((u32)spiPort == SPI0_BASE)
        CGU->PIPCLKSW &= ~(PIP_EN_SSP0_CLK|PIP_EN_SSP0_APBCLK);
    else if((u32)spiPort == SPI1_BASE)
        CGU->PIPCLKSW &= ~(PIP_EN_SSP1_CLK|PIP_EN_SSP1_APBCLK);

    //SPI_IsrDeInit(spiPort);
}

void SPI_SetDataMode(SPI_TypeDef *spiPort,SPI_DATA_t *tParam)
{
    if(tParam->u8ClkPhase == SPI_DRV_CLKPH_HALF)
        spiPort->CR0 |= SSP_CTRL0_SCLKPH;
    if(tParam->u8ClkPolarity == SPI_DRV_CLKPO_HIGH)
        spiPort->CR0 |= SSP_CTRL0_SCLKPO;
}

void SPI_SetSPIDataMode(SPI_TypeDef *spiPort, u8 dataMode)
{
    SPI_DATA_t tSpiData;

    if(dataMode == 0)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_ONE;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_LOW;
    }
    else if(dataMode == 1)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_HALF;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_LOW;
    }
    else if(dataMode == 2)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_ONE;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_HIGH;
    }
    else if(dataMode == 3)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_HALF;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_HIGH;
    }
    
    SPI_SetDataMode(spiPort,&tSpiData);
}

void SPI_Settings(SPI_TypeDef *spiPort, u8 div, u8 dataMode)
{
    SPI_DATA_t tSpiData;   
         
    tSpiData.u8Mode = SPI_DRV_MODE_MASTER;
    tSpiData.u8Div = div;
    
    if(dataMode == 0)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_ONE;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_LOW;
    }
    else if(dataMode == 1)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_HALF;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_LOW;
    }
    else if(dataMode == 2)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_ONE;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_HIGH;
    }
    else if(dataMode == 3)
    {
        tSpiData.u8ClkPhase = SPI_DRV_CLKPH_HALF;
        tSpiData.u8ClkPolarity = SPI_DRV_CLKPO_HIGH;
    }
   
    /*SPI0 PAD MUX*/
    MFP_SPI0_ENABLE();
    
    SPI_Init(spiPort,&tSpiData);
    SPI_EnableManualCS(spiPort);
    SPI_ClrCS(spiPort);
}

u32 SPI_Transfer(SPI_TypeDef *spiPort, u8 bitlen, u32 data)
{
    SPI_SetBitLength(spiPort, bitlen);
    SPI_StartTransfer(spiPort, data);
    while(SPI_IsBusy(spiPort));
    
    //for read operaion
    SPI_ClrRxFIFO(spiPort);
    if(bitlen == 8)
        return (SPI_ReadRxFIFO(spiPort) & 0xFF);
    else if(bitlen == 16)
        return (SPI_ReadRxFIFO(spiPort) & 0xFFFF);
    else if(bitlen == 32)
        return (SPI_ReadRxFIFO(spiPort));

    return 0;
}
