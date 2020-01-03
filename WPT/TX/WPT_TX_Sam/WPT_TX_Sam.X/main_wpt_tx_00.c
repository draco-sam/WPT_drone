/* 
 * File             : main_wpt_tx_00.c
 * Date             : 28/12/2019.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\dsPIC33C\h.
#include "Lib_Sam\dsPIC33CK256MP206.h"
#include "Lib_Sam/lib_wpt_tx_00.h"

int main(void) {
    
    Nop();
    
    pin_init();
    oscillator_init();
    interrupt_init();
    TMR1_init();
    pwm_init();
    
    TMR1_start();//For blink LEDs at 0.5s.
    
    while (1)
    {
        // Add your application code
    }
    
    return 0;
}
