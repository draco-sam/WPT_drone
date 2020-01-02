/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    clock.c

  @Summary:
    This is the clock.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.145.0
        Device            :  dsPIC33CK256MP206
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36b
        MPLAB             :  MPLAB X v5.25
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

#include <stdint.h>
#include "xc.h"
#include "clock.h"

void CLOCK_Initialize(void)
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
