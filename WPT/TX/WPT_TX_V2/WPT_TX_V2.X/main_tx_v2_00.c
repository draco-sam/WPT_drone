/*************************************************************************************************** 
 * File             : main_tx_v2_00.c
 * Date             : 02/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

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
    
    //PG5CONLbits.ON = 1;//PWM generator enabled.
    
    //pwm_5_h = pwm_on;
    
    pwm_duty_cycle(50);//[%].
    
    while (1)
    {
        //RB1 I/O for ON/OFF PWM.
        //RB1 = 1 -> PWM 5 H ON
        //RB1 = 0 -> PWM 5 H OFF with an external interrupt.
        if(PORTBbits.RB1 == 1){//RB1 I/O for ON/OFF PWM.
            pwm_5_h = pwm_on;
        }
    }
    
    return 0;
}
