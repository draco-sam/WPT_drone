/* 
 * File             : oscillator_pic24f_00.c
 * Date             : 28/12/2019.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "oscillator_pic24f_00.h"
#include "p24FJ128GC006.h"

//Primary Oscillator HS,HS Oscillator,Clock switching and Fail disabled.
_CONFIG2(FNOSC_PRI & POSCMD_HS & FCKSM_CSDCMD)

void oscillator_init(void)
{
    //Déclaration structure.
    OSCCONBITS reg_osccon;
    
    /*
     * Primary Oscillator (XT, HS, EC).
     * Idem à "_COSC = 0b010;".
     */
    reg_osccon.COSC = 0b010;
    
}


