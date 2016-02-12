#include "Arduino.h"

void sarADC_Init(void)
{
    outw( 0x00f18000, inw(0x00f18000)|0x1 << 7);
    outw( 0x00D0002C, inw(0x00D0002C) | (0x1 << 29)); // en_sar 24m_clk,[29] csr_en_sar_G = 1
    outw( 0x00d0004c, 0x00004000); // pd_sar power down control
    outw( 0x00d0009c, 0xffff5321); // saradc channel select (first time need)[7:4]csr_saradc_idx_1 = 5
}

void sarADC_DeInit(void)
{
    outw( 0x00D0002C, inw(0x00D0002C) &~ (0x1 << 29) ); // en_sar 24m_clk,[29] csr_en_sar_G = 0

    outw( 0x00d0004c, 0x00004200 ); // [9] csr_pd_sar_G = 1
}

void sarADC_Start(void)
{
    outw(0xD00098,0x450);// start saradc
}

u32 sarADC_Read(u8 ch)
{
    u32 value  = 0;
    
    switch(ch)
    {
        case 0:
        case 1:
            value = inw(0xd00100);
            if(ch == 0)
                value &= 0xFFF;
            else
                value = (value >> 12) & 0xFFF;
            break;
        case 2:
        case 3:
            value = inw(0xd00104);
            if(ch == 2)
                value &= 0xFFF;
            else
                value = (value >> 12) & 0xFFF;
            break;
    }
    
    return value;    
}