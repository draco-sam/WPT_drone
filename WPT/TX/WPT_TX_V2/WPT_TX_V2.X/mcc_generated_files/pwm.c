/*************************************************************************************************** 
 * File             : pwm.c
 * Date             : 21/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/


/**
  Section: Included Files
*/

#include "pwm.h"
#include "clock.h"

/**
 Section: Driver Interface Function Definitions
*/

void PWM_Initialize (void)
{
    /* PWM CLOCK CONTROL REGISTER :
     * ---------------------------
     * bit 8        : Write-protected registers and bits are unlocked.
     * bit 5-4      : PWM Clock Divider ratio is 1:2.
     * bit 1-0      : AFPLLO Auxiliary PLL post-divider output.
     ********************************************************************/
    PCLKCON = 0x03;
    
     
    FSCL        = 0x00;// FSCL 0;
    FSMINPER    = 0x00;// FSMINPER 0; 
    
     
    MPHASE      = 0x00;// MPHASE 0;
    MDC         = 0x00;// MDC 0;
    MPER        = 0x10;// MPER 16;
     
    LFSR        = 0x00;// LFSR 0;
    
    CMBTRIGL    = 0x00;//COMBINATIONAL TRIGGER REGISTER LOW : All disable.
    CMBTRIGH    = 0x00;//COMBINATIONAL TRIGGER REGISTER HIGH : All disable.
    
    //COMBINATORIAL PWM LOGIC CONTROL : All off.
    LOGCONA = 0x00;
    LOGCONB = 0x00;
    LOGCONC = 0x00;
    LOGCOND = 0x00;
    LOGCONE = 0x00;
    LOGCONF = 0x00;
    
    //PWM EVENT OUTPUT CONTROL REGISTER : All "0".
    PWMEVTA = 0x00;
    PWMEVTB = 0x00;
    PWMEVTC = 0x00;
    PWMEVTD = 0x00;
    PWMEVTE = 0x00;
    PWMEVTF = 0x00;
    
    /* PWM GENERATOR x CONTROL REGISTER HIGH :
     * --------------------------------------
     * bit 15       : For duty cycle, PWM Generator uses PGxDC register.
     * bit 14       : For period, PWM Generator uses PGxPER register.
	 * bit 13		: For phase, PWM Generator uses PGxPHASE register. 
     * bit 10-8     : SOC update.
     * bit 3-0      : Local EOC ? PWM Generator is self-triggered.
     * bit other    : 0.
     *********************************************************************/
    PG5CONH = 0x00;
    
    //PGxSTAT: PWM GENERATOR x STATUS REGISTER : All status "0".
    PG5STAT = 0x00;
    
    //PWM GENERATOR x I/O CONTROL REGISTER LOW : All "0".
    PG5IOCONL = 0x00;
    
    /* PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH :
     * -----------------------------------------------------
     * bit 5-4  "01"    : PWM Generator outputs operate in Independent mode.
     * bit 3    "1"     : PWM Generator controls the PWMxH output pin.
     * bit 2    "1"     : PWM Generator does not control the PWMxL output pin.
     * bit 1    "0"     : Output PWMxH pin is active-high (D = 10% for T_pwm_on).
     * bit 0    "0"     : Output PWMxL pin is active-high (if low, D = 10% for T_pwm_off)
     ****************************************************************************************/
    PG5IOCONH = 0x1c;//old value = 0x1f.
    
    /* PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW :
     * --------------------------------------------
     * bit 4-3  "01"    : A write of the PGxDC register automatically sets the UPDATE bit.
     * bit 2-0  "000"   : EOC event is the PWM Generator trigger.
     * 
     * PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH :
     * ---------------------------------------------
     * All "0".
     ****************************************************************************************/
    PG5EVTL = 0x08;//old value = 0x00.
    PG5EVTH = 0x00;
    
    //All "0" :
    PG5FPCIL = 0x00;
    PG5FPCIH = 0x00;
    
    //All "0" :
    PG5CLPCIL = 0x00;
    PG5CLPCIH = 0x00;
    
    //All "0" :
    PG5FFPCIL = 0x00;
    PG5FFPCIH = 0x00;
    
    //All "0" :
    PG5SPCIL = 0x00;
    PG5SPCIH = 0x00;
    
    PG5LEBL = 0x00;// LEB 0; 
    PG5LEBH = 0x00;// PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    
    //PWM features :
    PG5PHASE    = 0x00;//PHASE 0; 
    PG5DC       = 0x7D0;//Duty Cycle 2000; 
    PG5DCA      = 0x00;//Duty Cycle Adjustment.
    PG5PER      = 0xF98;//PER 3992;
    
    //PWM GENERATOR x TRIGGER REGISTER all "0" : 
    PG5TRIGA = 0x00;
    PG5TRIGB = 0x00;
    PG5TRIGC = 0x00;
    
    PG5DTL = 0x00;//Dead-time low 0.
    PG5DTH = 0x00;//Dead-time high 0.
    

    //Wait until AUX PLL clock is locked
    while(!CLOCK_AuxPllLockStatusGet());

    // HREN enabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG5CONL = 0x88;
}
//__________________________________________________________________________________________________

void pwm_duty_cycle(float duty){
/*
 * Input parameter     : duty in [%], from 0.8 (0x20) to 100 %.
 */
    unsigned short duty_integer = 0;
    
    duty_integer    = (PG5PER + 8) * (duty / 100);
    PG5DC           = duty_integer;
}
//__________________________________________________________________________________________________

void __attribute__ ((weak)) PWM_Generator5_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator5_Tasks(void)
{
    if(IFS4bits.PWM5IF)
    {
        // PWM Generator5 callback function 
        PWM_Generator5_CallBack();

        // clear the PWM Generator5 interrupt flag
        IFS4bits.PWM5IF = 0;
    }
}


void __attribute__ ((weak)) PWM_EventA_CallBack(void)
{
    // Add Application code here
}

void PWM_EventA_Tasks(void)
{
    if(IFS10bits.PEVTAIF)
    {
     
        // PWM EventA callback function 
        PWM_EventA_CallBack();
	
        // clear the PWM EventA interrupt flag
        IFS10bits.PEVTAIF = 0;
    }
}
void __attribute__ ((weak)) PWM_EventB_CallBack(void)
{
    // Add Application code here
}

void PWM_EventB_Tasks(void)
{
    if(IFS10bits.PEVTBIF)
    {
     
        // PWM EventB callback function 
        PWM_EventB_CallBack();
	
        // clear the PWM EventB interrupt flag
        IFS10bits.PEVTBIF = 0;
    }
}
void __attribute__ ((weak)) PWM_EventC_CallBack(void)
{
    // Add Application code here
}

void PWM_EventC_Tasks(void)
{
    if(IFS10bits.PEVTCIF)
    {
     
        // PWM EventC callback function 
        PWM_EventC_CallBack();
	
        // clear the PWM EventC interrupt flag
        IFS10bits.PEVTCIF = 0;
    }
}
void __attribute__ ((weak)) PWM_EventD_CallBack(void)
{
    // Add Application code here
}

void PWM_EventD_Tasks(void)
{
    if(IFS10bits.PEVTDIF)
    {
     
        // PWM EventD callback function 
        PWM_EventD_CallBack();
	
        // clear the PWM EventD interrupt flag
        IFS10bits.PEVTDIF = 0;
    }
}
void __attribute__ ((weak)) PWM_EventE_CallBack(void)
{
    // Add Application code here
}

void PWM_EventE_Tasks(void)
{
    if(IFS10bits.PEVTEIF)
    {
     
        // PWM EventE callback function 
        PWM_EventE_CallBack();
	
        // clear the PWM EventE interrupt flag
        IFS10bits.PEVTEIF = 0;
    }
}
void __attribute__ ((weak)) PWM_EventF_CallBack(void)
{
    // Add Application code here
}

void PWM_EventF_Tasks(void)
{
    if(IFS10bits.PEVTFIF)
    {
     
        // PWM EventF callback function 
        PWM_EventF_CallBack();
	
        // clear the PWM EventF interrupt flag
        IFS10bits.PEVTFIF = 0;
    }
}
