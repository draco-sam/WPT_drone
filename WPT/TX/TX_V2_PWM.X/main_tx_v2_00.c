/*************************************************************************************************** 
 * File             : main_tx_v2_00.c
 * Date             : 16/04/2020.   
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
    unsigned long time_counter = 0;
    
    // initialize the device
    SYSTEM_Initialize();
    
    //Check the position of the PWM on/off switch at startup :------------
    //
    //External interrupt 1 on IO B1 is configured
    //for a negative edge at the beginning of the code.
    //
    //PWM 5 high is configured OFF at the beginning of the code.
    //
    //The position of the switch determines the next edge interrupt. 
    if(port_b1_ext_int == 1){//Switch for PWM is ON.
        INTCON2bits.INT1EP = 1;//External interrupt 1 on NEGATIVE edge.
        led_red     = on;
        led_green   = off;
        led_blue    = off; 
    }
    else{//Switch for PWM is OFF.
        INTCON2bits.INT1EP = 0;//External interrupt 1 on POSITIVE edge.
        led_red     = off;
        led_green   = on;
        led_blue    = off;
    }
    //--------------------------------------------------------------------
    
    
    while (1)
    {
//        time_counter = 0;
//        
//        //Wait x ms. time_counter = 150 <-> +- 1ms.
//        for(time_counter=0 ; time_counter < 75000 ; time_counter++){}
//        led_red     = !led_red;
        
        
       
        Nop();
    }
    return 1; 
}
/**
 End of File
*/

