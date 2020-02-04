/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.155.0-a
        Device            :  PIC24FJ128GC006
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.40
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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/PIC24FJ128GC006.h"
#include "mcc_generated_files/usb/usb_device_cdc.h"

/*
                         Main application
 */



int main(void)
{
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
    
    unsigned long       counter_while           = 0;
    char                data_com                = "USB Virtual COM3";
    
    // initialize the device
    SYSTEM_Initialize();
    
    
    /******************************************************
     * Configuration des IO pour les 3 leds :
     * -------------------------------------
     */
    //Configurer les IO des leds en output :
    TRISEbits.TRISE7    = 0;//"0" : Output.
    TRISGbits.TRISG6    = 0;
    TRISGbits.TRISG7    = 0;
    
    //Pour les leds en digital io.    
    ANSEbits.ANSELE7 = 0;
    ANSGbits.ANSELG6 = 0;
    ANSGbits.ANSELG7 = 0;
    /*****************************************************/

    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    while(counter_while < 1e+6){
        counter_while++; 
    }
    led_red     = on;
    led_green   = off;
   
      
    unsigned short flag_tx      = 0;
    unsigned short flag_tx_2    = 0;
    unsigned short flag_tx_3    = 0;
    
    int data_2[1] = {0x0d};//0x0D : Carriage return.
    int data_3[1] = {0x0a};//0x0A : Line feed.
    
    while (1){
        //MCC_USB_CDC_DemoTasks();
        
        if(flag_tx == 0){
            if(USBUSARTIsTxTrfReady() == true){
                char data[] = "Hello World :";
                putsUSBUSART(data);
                flag_tx     = 1;
                flag_tx_2   = 1;
            }
        }
        if(flag_tx_2 == 1){
            if(USBUSARTIsTxTrfReady() == true){
                putsUSBUSART(data_2);
                flag_tx_2 = 0;
                flag_tx_3 = 1;
            }
        }
        if(flag_tx_3 == 1){
            if(USBUSARTIsTxTrfReady() == true){
                putsUSBUSART(data_3);
                flag_tx_3 = 0;
            }
        }
        
        CDCTxService();
        

        
        
    }

    return 1;
}
/**
 End of File
*/

