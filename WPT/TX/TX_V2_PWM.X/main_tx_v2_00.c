/*************************************************************************************************** 
 * File             : main_tx_v2_00.c
 * Date             : 02/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/
#include "mcc_generated_files/system.h"
#include "p33CK256MP206.h"

/*
                         Main application
 */

#define port_b1_ext_int PORTBbits.RB1

#define led_red         LATCbits.LATC14
#define led_green       LATCbits.LATC13
#define led_blue        LATCbits.LATC12
#define on              0
#define off             1

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    led_red     = on;
    led_green   = off;
    led_blue    = off;
    
    
    
    while (1)
    {
        if(port_b1_ext_int == 1){
            pwm_5_h = pwm_on;
            
            led_red     = on;
            led_green   = off;
            led_blue    = off;
        }
        
       
        
        Nop();
    }
    return 1; 
}
/**
 End of File
*/

