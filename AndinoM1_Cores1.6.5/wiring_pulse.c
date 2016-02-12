#include "Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    uint8_t status = 0;
    uint8_t value = 0;
    uint32_t timeout_tick = 0;
    uint32_t start_tick = 0;
    
    if(state)
        status = 1;
    else
        status = 0;
        
    timeout_tick = micros();
    while(1)
    {
        value = digitalRead(pin);
        if(value == status)
        {
            start_tick = micros();
            break;
        }
        
        if((micros() - timeout_tick) > timeout)
            return 0;
    }
    
    while(1)
    {
        value = digitalRead(pin);
        if(value != status)
            return (micros() - start_tick);
            
        if((micros() - timeout_tick) > timeout)
            return 0;
    }
}

#ifdef __cplusplus
}
#endif