/* 
 * File             : main_wpt_tx_00.c
 * Date             : 21/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\dsPIC33C\h.
#include "Lib_Sam/lib_wpt_tx_00.h"

int main(void) {
    
    Nop();
    
    SYSTEM_Initialize();
    
    led_red     = on;
    led_green   = off;
    led_blue    = off;
    
//    pin_init();
//    oscillator_init();
//    interrupt_init();
//    TMR1_init();
//    pwm_init();
    
    //TMR1_start();//For blink LEDs at 0.5s.
    
    while (1)
    {
        // Add your application code
    }
    
    return 0;
}
