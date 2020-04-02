/*************************************************************************************************** 
 * File             : ext_int.c
 * Date             : 02/04/2020.   
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
    //***User Area Begin->code: External Interrupt 1***
	
	//EX_INT1_CallBack();
    
    pwm_5_h = pwm_off;
     
    led_red     = off;
    led_green   = on;
    led_blue    = off;
    
	//***User Area End->code: External Interrupt 1***
    EX_INT1_InterruptFlagClear();
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
