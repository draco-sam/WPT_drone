/*************************************************************************************************** 
 * File             : interrupt_wpt_tx.c
 * Date             : 02/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

/**
    Section: Includes
*/
//#include <xc.h>

#include "../Lib_Sam/dsPIC33CK256MP206.h"
#include "interrupt_wpt_tx.h"

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //INT1I: External Interrupt 1, Priority: 1.
    //In pin "PIN_MANAGER_Initialize()" -> RPINR0bits.INT1R = 0x0021.
    //RB1->EXT_INT:INT1, external interrupt 1 for On/OFF PWM.
    IPC3bits.INT1IP = 1;
}

void __attribute__ ((weak)) EX_INT0_CallBack(void)
{
    // Add your custom callback code here
}
//__________________________________________________________________________________________________
 

void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
/*
 * Interrupt Handler for EX_INT0 - INT0
*/
{
    //***User Area Begin->code: External Interrupt 0***
	
	EX_INT0_CallBack();
    
	//***User Area End->code: External Interrupt 0***
    EX_INT0_InterruptFlagClear();
}
//__________________________________________________________________________________________________

 void __attribute__ ((weak)) EX_INT1_CallBack(void)
{
    // Add your custom callback code here
}
//__________________________________________________________________________________________________
 
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
/*
 * User Area Begin->code: External Interrupt 1 :
 * --------------------------------------------
 */
{
	//EX_INT1_CallBack();
    
    led_blue    = on;
    led_green   = off;
    led_red     = off;
    
    pwm_5_h     = pwm_off;//PWM OFF if falling edge on pin 37 (external INT1).
    
	//***User Area End->code: External Interrupt 1***
    EX_INT1_InterruptFlagClear();
}

//__________________________________________________________________________________________________
void EXT_INT_Initialize(void)
{
/*
 * External Interrupt Initializers :
 * --------------------------------
 * Initializer for the following external interrupts
 * INT1
 */
    /* INT1 :
     * -----
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     *****************************************************/
    EX_INT1_InterruptFlagClear();   
    //EX_INT1_PositiveEdgeSet();
    EX_INT1_NegativeEdgeSet();///RB1->EXT_INT:INT1, external interrupt 1 for On/OFF PWM.
    EX_INT1_InterruptEnable();
}
//__________________________________________________________________________________________________

