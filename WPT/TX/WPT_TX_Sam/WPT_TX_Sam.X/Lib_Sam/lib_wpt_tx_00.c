/* 
 * File             : lib_wpt_tx_00.c
 * Date             : 29/12/2019.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "lib_wpt_tx_00.h"
#include "p24FJ128GC006.h"

//Primary Oscillator HS,HS Oscillator,Clock switching and Fail disabled.
_CONFIG2(FNOSC_PRI & POSCMD_HS & FCKSM_CSDCMD)
//Oscillator divided by 8 (32 MHz input).
_CONFIG4(PLLDIV_DIV8)



void oscillator_init(void)
/*
 * 
 */
{
    //Déclarations structures.
    OSCCONBITS reg_osccon;
    CLKDIVBITS reg_clkdiv;
    
    //Primary Oscillator (XT, HS, EC).
    //Idem à "_COSC = 0b010;".
    reg_osccon.COSC = 0b010;
    
    //System Clock Select bits : 32 MHz (divide-by-1). 
    reg_clkdiv.CPDIV = 0b00;
}
//*************************************************************************************************

void pwm1_init (void)
/*
 * 
 */
{
    /* 
     * Remappable Peripheral Pin (PPS) RP23 :
     * -------------------------------------
     * Configurer OC1 (PW1) sur pin RP23.
     * Output Compare 1 sur Output Function Number 18 (0x12).
     * RPOR11 : Peripheral Pin Select Output Register 11.
     * 
     * Remarques :
     * ----------
     * OSCCON bit 6 pour verrouiller ou déverrouiller I/O et donc RP pin.
     * Code assembleur pour lock/unlock PPS.
     */
    TRISDBITS.TRISD2 = 0;//RD2 en output. !!! A vérifier si nécessaire !!!
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR11bits.RP23R = 0x0012;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
       
    
    /*
     * Configurer période PWM :
     * -----------------------
     * Timer5 prescaler à 1:1.
     */
    T5CONBITS.TCKPS = 0b00;
    
    
    OC1RS   = 0x00;//Reset.
    OC1R    = 0x00;//Reset.
    
    /*
     * OUTPUT COMPARE 1 CONTROL REGISTER 1 :
     * ------------------------------------
     * bit 15-10    : OCSIDL disabled; OCTSEL Peripheral clock (Fcy).
     * bit 7-4      : ENFLT<2:0> disabled; OCFLT<2:0> disabled.
     * bit 3-0      : TRIGMODE Only Software; OCM Output compare disable.
     */
    OC1CON1 = 0x1C00;//old value : 0x1C06. 
    
    /*
     * OCxCON2: OUTPUT COMPARE 1 CONTROL REGISTER 2 :
     * ---------------------------------------------
     * bit 7        : OCTRIG : Trigger designated by SYNCSEL.
     * bit 4-0      : SYNCSEL TMR5.
     * other bits   : All other OFF.
     */
    OC1CON2 = 0x8F;
    
    
}
//*************************************************************************************************

void pwm_on_off(unsigned short choix_pwm)
/*
 * 
 */
{
    //PWM ON.
    if(choix_pwm == 1)
    {
        OC1CON1bits.OCM = 0b110;//Edge-Aligned PWM mode on OCx.
    }
    //PWM OFF dans tous les autres cas.
    else
    { 
       OC1CON1bits.OCM = 0;
    }
}
//*************************************************************************************************



