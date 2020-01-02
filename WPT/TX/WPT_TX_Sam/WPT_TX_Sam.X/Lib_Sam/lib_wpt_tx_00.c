/* 
 * File             : lib_wpt_tx_00.c
 * Date             : 29/12/2019.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "lib_wpt_tx_00.h"
#include "dsPIC33CK256MP206.h"


void oscillator_init(void)
/*
 * 
 */
{
    /*
     * CLOCK DIVIDER REGISTER :
     * -----------------------
     * bit 14-12    : FP (fréquency processor) divided by 8 (default).
     * bit 11       : Processor clock and peripheral clock ratio is forced to 1:1.
     * bit 10-8     : Internal Fast RC Oscillator Postscaler divided by 1.
     * bit 3-0      : PLLPRE[3:0] Input divided by 1.
     */
    CLKDIV = 0x3001;
    
    /*
     * PLL FEEDBACK DIVIDER REGISTER :
     * ------------------------------
     * bit 7-0      : 150 (default).
     */
    PLLFBD = 0x96;
    
    // FRC OSCILLATOR TUNING REGISTER. Center frequency (8.00 MHz nominal).
    OSCTUN = 0x00;
    
    /*
     * PLL OUTPUT DIVIDER REGISTER :
     * ----------------------------
     * bit 9-8      : FVCO/4.
     * bit 6-4      : POST1DIV[2:0] PLL Output #1 Divider by 4.
     * bit 2-0      : POST2DIV[2:0] PLL Output #2 Divider by 1.
     */ 
    PLLDIV = 0x41;
    
    /*
     * AUXILIARY CLOCK CONTROL REGISTER :
     * ---------------------------------
     * bit 15       : AFPLLO is connected to the APLL post-divider output.
     * bit 8        : FRC is the clock source for APLL.
     * bit 3-0      : Auxiliary PLL Phase Detector Input divided by 1.
     */ 
    ACLKCON1 = 0x8101;
    
    // APLL Feedback Divider bits 125; 
    APLLFBD1 = 0x7D;
    // APOST1DIV 1:2; APOST2DIV 1:1; AVCODIV FVCO/4; 
    APLLDIV1 = 0x21;
    
    // ROEN disabled; ROSWEN disabled; ROSLP disabled; ROSEL FOSC; ROOUT disabled; ROSIDL disabled; 
    REFOCONL = 0x00;
    // RODIV 0; 
    REFOCONH = 0x00;
    
    /*
     * PERIPHERAL REMAPPING CONFIGURATION REGISTER :
     * --------------------------------------------
     * bit 11       : All Peripheral Remapping registers are unlocked and can be written.
     */
    __builtin_write_RPCON(0);
    //RPCON = 0x00;
    
    
    // PMDLOCK disabled; 
    PMDCON = 0x00;
    // ADC1MD enabled; T1MD enabled; U2MD enabled; U1MD enabled; SPI2MD enabled; SPI1MD enabled; QEIMD enabled; PWMMD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; CCP7MD enabled; CCP8MD enabled; CCP5MD enabled; CCP6MD enabled; CCP9MD enabled; 
    PMD2 = 0x00;
    // I2C3MD enabled; PMPMD enabled; U3MD enabled; QEI2MD enabled; CRCMD enabled; I2C2MD enabled; 
    PMD3 = 0x00;
    // REFOMD enabled; 
    PMD4 = 0x00;
    // DMA1MD enabled; SPI3MD enabled; DMA2MD enabled; DMA3MD enabled; DMA0MD enabled; 
    PMD6 = 0x00;
    // CMP3MD enabled; PTGMD enabled; CMP1MD enabled; CMP2MD enabled; 
    PMD7 = 0x00;
    // DMTMD enabled; CLC3MD enabled; OPAMPMD enabled; BIASMD enabled; CLC4MD enabled; SENT2MD enabled; SENT1MD enabled; CLC1MD enabled; CLC2MD enabled; 
    PMD8 = 0x00;
    
    /*
     * OSCCON: OSCILLATOR CONTROL REGISTER :
     * ------------------------------------
     * bit 14-12    : Fast RC Oscillator (FRC).
     * bit 10-8     : Fast RC Oscillator (FRC) with Divide-by-n (FRCDIVN).
     */
    // CF no clock failure; NOSC FRCDIV; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x07));
    __builtin_write_OSCCONL((uint8_t) (0x00));
}
//*************************************************************************************************

void pwm_init (void)
/*
 * 
 */
{
    /*
     * PWM CLOCK CONTROL REGISTER :
     * ---------------------------
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
    
    // MPER
    //MPER = 0x10;
    MPER = 0x00;
    
    // LFSR 0; 
    LFSR = 0x00;
    // CTA7EN disabled; CTA8EN disabled; CTA1EN disabled; CTA2EN disabled; CTA5EN disabled; CTA6EN disabled; CTA3EN disabled; CTA4EN disabled; 
    CMBTRIGL = 0x00;
    // CTB8EN disabled; CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB7EN disabled; CTB6EN disabled; CTB5EN disabled; CTB4EN disabled; 
    CMBTRIGH = 0x00;
    
    /*
     * COMBINATORIAL PWM LOGIC CONTROL REGISTER y :
     * ----------------------------------------------------
     * !!! PAS utilisé !!!
     */
    LOGCONA = 0x00;
    LOGCONB = 0x00;
    LOGCONC = 0x00;
    LOGCOND = 0x00;
    LOGCONE = 0x00;
    LOGCONF = 0x00;
    
    /*
     * PWM EVENT OUTPUT CONTROL REGISTER y :
     * ---------------------------------------------
     * !!! PAS utilisé !!!
     */
    PWMEVTA = 0x00;
    PWMEVTB = 0x00;
    PWMEVTC = 0x00;
    PWMEVTD = 0x00;
    PWMEVTE = 0x00;
    PWMEVTF = 0x00;
    
    /*
     * PWM GENERATOR x CONTROL REGISTER HIGH :
     * -----------------------------------------------
     * bit 15       : PWM Generator uses PGxDC register for duty cycle.
     * bit 14       : PWM Generator uses PGxPER register for period.
     * bit 10-8     : SOC update.
     * bit 3-0      : Local EOC ? PWM Generator is self-triggered.
     * bit other    : 0.
     * 
     */
    PG5CONH = 0x00;
    
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG5STAT = 0x00;
    
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH disabled; OVRENL disabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG5IOCONL = 0x00;
    
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
    
    PG5PHASE = 0x00;// PHASE 0;
    PG5DC = 0x128;// Duty Cycle 296;
    PG5DCA = 0x00;// Duty Cycle adjust 0;
    PG5PER = 0x248;// Period 584; 
    
    //PWM GENERATOR x TRIGGER REGISTER :
    PG5TRIGA = 0x00; 
    PG5TRIGB = 0x00; 
    PG5TRIGC = 0x00;
    PG5DTL = 0x00; 
    PG5DTH = 0x00;
    

    // HREN enabled; MODSEL Independent Edge; TRGCNT 1; CLKSEL Master clock; ON disabled;
    /*
     * PWM GENERATOR x CONTROL REGISTER LOW :
     * ----------------------------------------------
     * bit 15       : PWM Generator enable.
     * bit 10-8     : PWM Generator produces one PWM cycle after triggered
     * bit 7        : PWM Generator x operates in High-Resolution mode.
     * bit 4-3      : PWM Generator uses Master clock selected by the MCLKSEL[1-0],
     *                AFPLLO ? Auxiliary PLL post-divider.
     * bit 2-0      : Independent Edge PWM mode.
     */
    PG5CONL = 0x88;

    
    
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



