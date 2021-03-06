/**
  PWM Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.c

  @Summary
    This is the generated driver implementation file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.145.0
        Device            :  dsPIC33CK256MP206
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36b
        MPLAB 	          :  MPLAB X v5.25
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "pwm.h"

/**
 Section: Driver Interface Function Definitions
*/
void PWM_Initialize (void)
{
    // MCLKSEL AFPLLO - Auxiliary Clock with PLL Enabled; HRERR disabled; LOCK disabled; DIVSEL 1:2; 
    /*
     * bit 8        : Write-protected registers and bits are unlocked.
     * bit 5-4      : PWM Clock Divider ratio is 1:2.
     * bit 1-0      : AFPLLO ? Auxiliary PLL post-divider output.
     */
    PCLKCON = 0x03;
    
    // FSCL 0; 
    FSCL = 0x00;
    // FSMINPER 0; 
    FSMINPER = 0x00;
    // MPHASE 0; 
    MPHASE = 0x00;
    // MDC 0; 
    MDC = 0x00;
    
    // MPER 16; 
    //??? 0x00 ???
    MPER = 0x10;
    
    // LFSR 0; 
    LFSR = 0x00;
    // CTA7EN disabled; CTA8EN disabled; CTA1EN disabled; CTA2EN disabled; CTA5EN disabled; CTA6EN disabled; CTA3EN disabled; CTA4EN disabled; 
    CMBTRIGL = 0x00;
    // CTB8EN disabled; CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB7EN disabled; CTB6EN disabled; CTB5EN disabled; CTB4EN disabled; 
    CMBTRIGH = 0x00;
    
    /*
     * LOGCONy: COMBINATORIAL PWM LOGIC CONTROL REGISTER y :
     * ----------------------------------------------------
     * !!! PAS utilis� !!!
     */
    // PWMLFA PWMS1 or PWMS2;; S1APOL Positive logic; S2APOL Positive logic; PWMLFAD No Assignment; PWMS1A PWM1H; PWMS2A PWM1H; 
    LOGCONA = 0x00;
    // PWMLFB PWMS1 | PWMS2; S2BPOL Positive logic; PWMLFBD No Assignment; S1BPOL Positive logic; PWMS2B PWM1H; PWMS1B PWM1H; 
    LOGCONB = 0x00;
    // PWMLFC PWMS1 | PWMS2; PWMLFCD No Assignment; S2CPOL Positive logic; S1CPOL Positive logic; PWMS1C PWM1H; PWMS2C PWM1H; 
    LOGCONC = 0x00;
    // PWMS1D PWM1H; S1DPOL Positive logic; PWMLFD PWMS1 | PWMS2; PWMLFDD No Assignment; S2DPOL Positive logic; PWMS2D PWM1H; 
    LOGCOND = 0x00;
    // PWMS1E PWM1H; PWMS2E PWM1H; S1EPOL Positive logic; PWMLFE PWMS1 | PWMS2; S2EPOL Positive logic; PWMLFED No Assignment; 
    LOGCONE = 0x00;
    // S1FPOL Positive logic; PWMS2F PWM1H; PWMS1F PWM1H; S2FPOL Positive logic; PWMLFFD No Assignment; PWMLFF PWMS1 | PWMS2; 
    LOGCONF = 0x00;
    
    /*
     * PWMEVTy: PWM EVENT OUTPUT CONTROL REGISTER y :
     * ---------------------------------------------
     * !!! PAS utilis� !!!
     */
    // EVTASEL PGTRGSEL bits; EVTASYNC Not synchronized; EVTAPOL Active-high; EVTAPGS PG1; EVTASTRD Stretched to 8 PWM clock cycles minimum; EVTAOEN disabled; 
    PWMEVTA = 0x00;
    // EVTBPGS PG1; EVTBSYNC Not synchronized; EVTBPOL Active-high; EVTBSEL PGTRGSEL bits; EVTBSTRD Stretched to 8 PWM clock cycles minimum; EVTBOEN disabled; 
    PWMEVTB = 0x00;
    // EVTCPGS PG1; EVTCPOL Active-high; EVTCSEL PGTRGSEL bits; EVTCSTRD Stretched to 8 PWM clock cycles minimum; EVTCSYNC Not synchronized; EVTCOEN disabled; 
    PWMEVTC = 0x00;
    // EVTDOEN disabled; EVTDSTRD Stretched to 8 PWM clock cycles minimum; EVTDPOL Active-high; EVTDPGS PG1; EVTDSEL PGTRGSEL bits; EVTDSYNC Not synchronized; 
    PWMEVTD = 0x00;
    // EVTEOEN disabled; EVTEPOL Active-high; EVTEPGS PG1; EVTESTRD Stretched to 8 PWM clock cycles minimum; EVTESEL PGTRGSEL bits; EVTESYNC Not synchronized; 
    PWMEVTE = 0x00;
    // EVTFPOL Active-high; EVTFPGS PG1; EVTFSTRD Stretched to 8 PWM clock cycles minimum; EVTFSEL PGTRGSEL bits; EVTFOEN disabled; EVTFSYNC Not synchronized; 
    PWMEVTF = 0x00;
    
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    /*
     * PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH :
     * -----------------------------------------------
     * bit 15       : PWM Generator uses PGxDC register for duty cycle.
     * bit 14       : PWM Generator uses PGxPER register for period.
     * bit 10-8     : SOC update.
     * bit other    : 0.
     * 
     */
    PG5CONH = 0x00;
    
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG5STAT = 0x00;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH disabled; OVRENL disabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG5IOCONL = 0x00;
    
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Independent; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
    /*
     * PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH :
     * -----------------------------------------------------
     * bit 5-4      : PWM Generator outputs operate in Independent mode.
     * bit 3        : PWM Generator controls the PWMxH output pin.
     * bit 2        : PWM Generator does not control the PWMxL output pin.
     * bit 1        : ??? Output PWMxH pin is active-high ???
     * bit 0        : ??? Output PWMxL pin is active-high ???
     */
    //PG5IOCONH = 0x1C;
    PG5IOCONH = 0x18;
    
    /*
     * PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW :
     * --------------------------------------------
     * bit 2-0      : EOC event is the PWM Generator trigger.
     */
    PG5EVTL = 0x00;
    
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG5EVTH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5FPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5FPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5CLPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5CLPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5FFPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5FFPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5SPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5SPCIH = 0x00;
    // LEB 0; 
    PG5LEBL = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG5LEBH = 0x00;
    
    // PHASE 0; 
    PG5PHASE = 0x00;
    // DC 296; 
    PG5DC = 0x128;
    // DCA 0; 
    PG5DCA = 0x00;
    // PER 584; 
    PG5PER = 0x248;
    
    // TRIGA 0; 
    PG5TRIGA = 0x00;
    // TRIGB 0; 
    PG5TRIGB = 0x00;
    // TRIGC 0; 
    PG5TRIGC = 0x00;
    // DTL 0; 
    PG5DTL = 0x00;
    // DTH 0; 
    PG5DTH = 0x00;
    

    // HREN enabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON disabled;
    /*
     * PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW :
     * ----------------------------------------------
     * bit 15       : PWM Generator enable.
     * bit 10-8     : PWM Generator produces one PWM cycle after triggered
     * bit 7        : PWM Generator x operates in High-Resolution mode.
     * bit 4-3      : ??? 0b00 ou 0b01 ???
     * bit 2-0      : Independent Edge PWM mode.
     */
    PG5CONL = 0x88;
}


void __attribute__ ((weak)) PWM_Generator5CallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_Generator5(void)
{
    if(IFS4bits.PWM5IF)
    {
		PWM_Generator5CallBack();
	
        IFS4bits.PWM5IF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventACallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventA(void)
{
    if(IFS10bits.PEVTAIF)
    {
		PWM_EventACallBack();
		
        IFS10bits.PEVTAIF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventBCallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventB(void)
{
    if(IFS10bits.PEVTBIF)
    {
		PWM_EventBCallBack();
		
        IFS10bits.PEVTBIF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventCCallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventC(void)
{
    if(IFS10bits.PEVTCIF)
    {
		PWM_EventCCallBack();
		
        IFS10bits.PEVTCIF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventDCallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventD(void)
{
    if(IFS10bits.PEVTDIF)
    {
		PWM_EventDCallBack();
		
        IFS10bits.PEVTDIF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventECallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventE(void)
{
    if(IFS10bits.PEVTEIF)
    {
		PWM_EventECallBack();
		
        IFS10bits.PEVTEIF = 0;
        //Add your custom code here.
    }
}


void __attribute__ ((weak)) PWM_EventFCallBack(void)
{
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */
}

void PWM_Tasks_EventF(void)
{
    if(IFS10bits.PEVTFIF)
    {
		PWM_EventFCallBack();
		
        IFS10bits.PEVTFIF = 0;
        //Add your custom code here.
    }
}


