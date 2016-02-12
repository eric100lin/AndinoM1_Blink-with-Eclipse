#include "Arduino.h"

void noTone(uint8_t pin)
{
    if((pin != 4)&&(pin != 5))  //A4 & A5 can be set PWM( use PWM1)
        return;
        
    PWM_Disable(pin);
    PWM_CLK_DIS();
}

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
    // frequency (in hertz) and duration (in milliseconds).
    uint8_t PwmDiv = 0;
    uint32_t Duty = 0;
    uint32_t period = 0;
    uint32_t start_tick = 0;
    
    if((pin != 4)&&(pin != 5))  //only A4 & A5 can be set PWM( use PWM1)
        return;

    PwmDiv = 0x0;
    period = 32768/frequency; //how many T
    Duty = period/2;
    
    PWM_CLK_EN();
    MTF_PWM_ENA(pin);
    PWM_Set_Clk_Src();
    PWM_Config_Setting(pin,Duty,period-1,PwmDiv); //make 50%,50% period 
    PWM_ENA(pin);

    if(duration == 0)
        return;

    start_tick = millis();
    while(1)
    {
        if((millis() - start_tick) > duration)
        {
            noTone(pin);
            break;
        }
    }
}