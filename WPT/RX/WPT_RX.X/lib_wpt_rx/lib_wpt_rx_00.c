/* 
 * File             : lib_wpt_rx_00.c
 * Date             : 22/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "lib_wpt_rx_00.h"


void oscillator_init(void)
/*
 * 
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
//**************************************************************************************************

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
    LATG = 0x0040;
    
    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISB = 0xF0FF;
    TRISC = 0x1000;
    TRISD = 0x0FFF;
    TRISE = 0x00FF;
    TRISF = 0x00BB;
    TRISG = 0x030C;//11 0000 1100. TRISG_old = 0x3cc.

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
     * 
     * "0" : Digital pin.
     * "1" : Analog pin.
     ***************************************************************************/
    ANSB = 0xF0FC;
    ANSD = 0xFFFF;
    ANSE = 0x00F0;
    ANSF = 0x00B9;
    ANSG = 0x03C0;

    //Setting UTRDIS bit to use RG2 and RG3 as GPIO 
    U1CNFG2bits.UTRDIS = 1;
    
    
}

