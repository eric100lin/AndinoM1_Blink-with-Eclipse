#include "m2c8001_pwm.h"

void PWM_CLK_EN(void)
{
    CGU->PIPCLKSW |= (PIP_EN_PWM1_CLK|PIP_EN_PWM1_APBCLK);
}

void MTF_PWM_ENA(u8 pin)
{
    if(pin == 4)
        TOP->PADMUX1 = (TOP->PADMUX1 & ~PAD_I2C_SDA_MUX_MASK) | PAD_I2C_SDA_MUX_PWM3;
        //MFP_PWM3_ENABLE();
    else if(pin == 5)
        TOP->PADMUX1 = (TOP->PADMUX1 & ~PAD_I2C_CLK_MUX_MASK) | PAD_I2C_CLK_MUX_PWM2;
        //MFP_PWM2_ENABLE();
}

void PWM_Set_Clk_Src(void)
{
    //CGU->DIPCLKSEL = (CGU->DIPCLKSEL &~DIP_CLK_SEL_PWM1_MASK) | DIP_CLK_SEL_PWM1_XO;
    CGU->DIPCLKSEL = (CGU->DIPCLKSEL &~DIP_CLK_SEL_PWM1_MASK) | DIP_CLK_SEL_PWM1_32K | DIP_CLK_SEL_RTC_XO;
}

void PWM_Config_Setting(u8 pin, u16 Duty,u16 Period,u8 Div)
{
    u8 ch = 0;
    
    if(pin == 4)
        ch = 1;
    else
        ch = 0;
        
    if(ch == 0){
        /*Set clock*/
        PWM1->PWM0CR = Div & PWM_CTRL_PRESCALE ;
        /*Duty*/
        PWM1->PWM0DUTY = Duty & PWM_DUTY_DCYCLE;
        /*Period*/
        PWM1->PWM0PER =  Period & PWM_PER_PERVAL ;
    }
    else{
        /*Set clock*/
        PWM1->PWM1CR = Div & PWM_CTRL_PRESCALE ;
        /*Duty*/
        PWM1->PWM1DUTY = Duty & PWM_DUTY_DCYCLE;
        /*Period*/
        PWM1->PWM1PER =  Period & PWM_PER_PERVAL ;
    }
}

void PWM_ENA(u8 pin)
{
    u8 ch = 0;
    
    if(pin == 4)
        ch = 1;
    else
        ch = 0;
        
    if(ch == 0)
        PWM1->PWM0CR2 |=PWM_CTRL2_EN;
    else
        PWM1->PWM1CR2 |=PWM_CTRL2_EN;
}

void PWM_Disable(u8 pin)
{
    u8 ch = 0;
    
    if(pin == 4)
        ch = 1;
    else
        ch = 0;
        
    if(ch == 0)
        PWM1->PWM0CR2 &= ~PWM_CTRL2_EN;
    else
        PWM1->PWM1CR2 &= ~PWM_CTRL2_EN;
}

void PWM_CLK_DIS(void)
{
    CGU->PIPCLKSW &= ~(PIP_EN_PWM1_CLK|PIP_EN_PWM1_APBCLK);
}
