#ifndef M2C8001_PWM_H_
#define M2C8001_PWM_H_

#include "m2c8001.h"

/***********************************************************************************************
*   SOC PWM definition
************************************************************************************************/

/* PWM CTRL Register */
#define PWM_CTRL_PRESCALE    (0x3F)

/* PWM DUTY Register */
#define PWM_DUTY_DCYCLE    (0x3FF)

/* PWM PER Register */
#define PWM_PER_PERVAL    (0x3FF)

/* PWM CTRL2 Register */
#define PWM_CTRL2_EN    (0x1)

void PWM_CLK_EN(void);
void MTF_PWM_ENA(u8 pin);
void PWM_Set_Clk_Src(void);
void PWM_Config_Setting(u8 pin, u16 Duty,u16 Period,u8 Div);
void PWM_ENA(u8 pin);
void PWM_Disable(u8 pin);
void PWM_CLK_DIS(void);

#endif