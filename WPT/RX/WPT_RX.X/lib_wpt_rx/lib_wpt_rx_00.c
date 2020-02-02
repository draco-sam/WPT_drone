/* 
 * File             : lib_wpt_rx_00.c
 * Date             : 22/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "lib_wpt_rx_00.h"

#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1


void oscillator_init(void)
/*
 * fcy = 4 MHz (8MHz/2).
 */
{
    // CPDIV 1:1; PLLEN disabled; RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3000;
    //STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; 
    //STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; 
    //TUN Center frequency; 
    OSCTUN = 0x00;
    // ROEN disabled; ROSEL FOSC; RODIV 0; ROSSLP disabled; 
    REFOCON = 0x00;
    //ADC1MD enabled; T3MD enabled; T4MD enabled; T1MD enabled; U2MD enabled; T2MD enabled; 
    //U1MD enabled; SPI2MD enabled; SPI1MD enabled; T5MD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    //OC5MD enabled; OC6MD enabled; OC7MD enabled; OC8MD enabled; OC1MD enabled; IC2MD enabled; 
    //OC2MD enabled; IC1MD enabled; OC3MD enabled; OC4MD enabled; IC6MD enabled; 
    //IC7MD enabled; IC5MD enabled; IC8MD enabled; IC4MD enabled; IC3MD enabled; 
    PMD2 = 0x00;
    //DSMMD enabled; PMPMD enabled; U3MD enabled; RTCCMD enabled; CMPMD enabled; CRCMD enabled; 
    //I2C2MD enabled; DAC1MD enabled; 
    PMD3 = 0x00;
    // U4MD enabled; UPWMMD enabled; USB1MD enabled; CTMUMD enabled; REFOMD enabled; HLVDMD enabled; 
    PMD4 = 0x00;
    // IC9MD enabled; OC9MD enabled; 
    PMD5 = 0x00;
    // SDA1MD enabled; AMP2MD enabled; AMP1MD enabled; LCDMD enabled; DAC2MD enabled; 
    PMD6 = 0x00;
    // DMA1MD enabled; DMA0MD enabled; 
    PMD7 = 0x00;
    //CF no clock failure; NOSC FRCDIV; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; 
    //OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONH((uint8_t) (0x07));
    __builtin_write_OSCCONL((uint8_t) (0x00));
}
//__________________________________________________________________________________________________

void pin_init(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;
    LATE = 0x0000;
    LATF = 0x0000;
    LATG = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISB = 0xF0FF;
    TRISC = 0x1000;
    TRISD = 0x0FFF;
    TRISE = 0x00FF;
    TRISF = 0x00BB;
    TRISG = 0x03CC;
    
    //Configurer les IO des leds en output :
    TRISEbits.TRISE7    = 0;//"0" : Output.
    TRISGbits.TRISG6    = 0;
    TRISGbits.TRISG7    = 0;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPD3 = 0x0000;
    CNPD4 = 0x0000;
    CNPD5 = 0x0000;
    CNPD6 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;
    CNPU3 = 0x0000;
    CNPU4 = 0x0000;
    CNPU5 = 0x0000;
    CNPU6 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSB = 0xF0FC;
    ANSD = 0xF9FF;
    ANSE = 0x00F0;
    ANSF = 0x00B9;
    ANSG = 0x03C0;
    //Pour les leds en digital io.    
    ANSEbits.ANSELE7 = 0;
    ANSGbits.ANSELG6 = 0;
    ANSGbits.ANSELG7 = 0;

    //Setting UTRDIS bit to use RG2 and RG3 as GPIO 
    U1CNFG2bits.UTRDIS = 1;
}
//__________________________________________________________________________________________________

void interrupt_init(void)
/*
 */
{
    //MICI: MI2C1. I2C1 Master EventsPriority: 1.
    IPC4bits.MI2C1P = 1;
    //SICI: SI2C1 - I2C1 Slave Events. Priority: 1.
    IPC4bits.SI2C1P = 1;
}
//__________________________________________________________________________________________________

void i2c_bus_high(void)
/*
 * Met les signaux I2C SDA et SCL à "1" avant de démarrer la com.
 * Ceci est un bug du coté du slave.
 * Voir si I2C Master configuré en SMbus ???
 */
{
    unsigned long counter   = 0;
    unsigned long delay     = 1000000; 
    
    TRISDbits.TRISD9    = 0;//"0" : Output.
    TRISDbits.TRISD10   = 0;//"0" : Output.
    LATDbits.LATD9      = 1;
    LATDbits.LATD10     = 1;
    
    while(counter < delay)
    {
        counter++;
    }
}
//__________________________________________________________________________________________________

void wait(unsigned long count){
/*
 * 
 */
    unsigned long timer_counter = 0;
    
    while(timer_counter < count){
            timer_counter++;
    }
    
}