/*************************************************************************************************** 
 * File             : ext_int.c
 * Date             : 16/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "ext_int.h"

#define led_red         LATCbits.LATC14
#define led_green       LATCbits.LATC13
#define led_blue        LATCbits.LATC12
#define on              0
#define off             1
#define port_b1_ext_int PORTBbits.RB1

//***User Area Begin->code: Add External Interrupt handler specific headers 

//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
*/
 
 void __attribute__ ((weak)) EX_INT1_CallBack(void)
{
    // Add your custom callback code here
}

/**
  Interrupt Handler for EX_INT1 - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
{
    unsigned long time_counter = 0;
	
	//EX_INT1_CallBack();
    
    INTCON2bits.GIE = 0;//Global interrupt are disabled.
    
    //Wait switch bounce. time_counter=75000 <-> +-500 ms (150 for 1ms).
    for(time_counter=0 ; time_counter < 75000 ; time_counter++){}//Wait switch bounce.
    
    if(port_b1_ext_int == 1){//PWM ON.
        pwm_5_h     = pwm_on;
        
        INTCON2bits.INT1EP = 1;//External interrupt 1 on NEGATIVE edge.
            
        led_red     = on;
        led_green   = off;
        led_blue    = off;
    }
    else{//PWM OFF in the other cases.
        pwm_5_h = pwm_off;
        
        INTCON2bits.INT1EP = 0;//External interrupt 1 on POSITIVE edge.
     
        led_red     = off;
        led_green   = on;
        led_blue    = off;
    }
	
    EX_INT1_InterruptFlagClear();
    INTCON2bits.GIE = 1;//Global interrupt are enable.
}
/**
    Section: External Interrupt Initializers
 */
/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT1
*/
void EXT_INT_Initialize(void)
{
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT1_InterruptFlagClear();   
    EX_INT1_NegativeEdgeSet();
    EX_INT1_InterruptEnable();
}
