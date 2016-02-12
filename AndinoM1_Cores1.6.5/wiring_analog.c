#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define SARADC_DELAY_US    (250)
#define SARADC_SAMPLE_CNT   5

uint32_t ResolutionRead = 0;
uint32_t PWMBit = 0;

int analogRead(uint8_t pin)
{
    int value = 0;
    int i = 0;

    if (pin >= 4)
        return 0;

    AGPIO_ENA(pin);
    AGPIO_ENA_SAR_Func(pin);
    sarADC_Init();

    for(i=0;i<SARADC_SAMPLE_CNT;i++) //sample adc 5 times and average
    {
        sarADC_Start();
        delayMicroseconds(SARADC_DELAY_US);
        value += sarADC_Read(pin);
    }
    value/=SARADC_SAMPLE_CNT;

    //sarADC_DeInit();
    //AGPIO_DIS_SAR_Func(pin);
    //AGPIO_DIS(pin);

    if(ResolutionRead)
    {
        value &= ResolutionRead;
        //ResolutionRead = 0;
    }

    return value;
}

void analogReadResolution(uint8_t bit)
{
    int maskbit = 0;
    int i = 0;

    if(bit == 0)
        return;

    if (bit >= 12) //max resolution is 12 bits
        bit = 12;

    for(i=0;i<bit;i++)
        maskbit |= (0x1 << i);

    ResolutionRead = maskbit;
}

void analogWrite(uint8_t pin, int val)
{
    uint8_t PwmDiv = 0;
    uint32_t Duty = 0;
    uint32_t period = 0;
    uint32_t frequency = 1000; //make 1KHz frequency

    if((pin != 4)&&(pin != 5))  //only A4 & A5 can be set PWM( use PWM1)
        return;

    PwmDiv = 0x3F;// 24MHz/64 = 375KHz ,1T = 375KHz

    period = 375000/frequency; //how many T, minimux freq = 375000/1024 = 366Hz

    if(val == 0)
        Duty = 0;
    else if(val == 255)
        Duty = period;
    else
        Duty = (period*val)/255;;

    if(PWMBit)
    {
        Duty &= PWMBit;
        period &= PWMBit;
        PWMBit = 0;
    }

    PWM_CLK_EN();
    MTF_PWM_ENA(pin);
    PWM_Set_Clk_Src();
    PWM_Config_Setting(pin,Duty,period-1,PwmDiv);
    PWM_ENA(pin);
}

void analogReference(uint8_t mode)
{
	//The feature is not supported.
}

void analogWriteResolution(uint8_t bit)
{
    int duty_maskbit = 0;
    int i = 0;

    if(bit == 0)
        return;

    if (bit >= 10) //max resolution is 10 bits
        bit = 10;

    for(i=0;i<bit;i++)
        duty_maskbit |= (0x1 << i);

    PWMBit = duty_maskbit;
}

#ifdef __cplusplus
}
#endif
