/* 
 * File             : lib_wpt_tx_00.h
 * Date             : 28/12/2019.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "dsPIC33CK256MP206.h"

void pin_init (void);
void oscillator_init(void);
void pwm_init (void);
void pwm_on_off(unsigned short choix_pwm);
void TMR1_init (void);
void TMR1_start( void );
void TMR1_stop( void );
void interrupt_init (void);

