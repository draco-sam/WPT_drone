/* 
 * File             : lib_wpt_tx_00.h
 * Date             : 21/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "dsPIC33CK256MP206.h"
#include "../mcc_generated_files/system.h"
#include "../mcc_generated_files/pwm.h"

void pin_init (void);
void oscillator_init(void);
void pwm_init (void);
//void pwm_on_off(unsigned short choix_pwm);
void TMR1_init (void);
void TMR1_start( void );
void TMR1_stop( void );
void interrupt_init (void);

#define led_red         LATCbits.LATC14
#define led_green       LATCbits.LATC13
#define led_blue        LATCbits.LATC12
#define on              0
#define off             1



