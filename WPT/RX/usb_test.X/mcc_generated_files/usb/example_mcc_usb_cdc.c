/*
    (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
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

/*
    MCC USB CDC Demo Usage:
 
    Call the MCC_USB_CDC_DemoTasks() function from your main loop.
    It will read data sent from the host and echo it back +1.  If you open
    up a terminal window and type 'a' then 'b' will be echoed back.
 */
#include <stdint.h>

#include "usb.h"


#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];

void MCC_USB_CDC_DemoTasks(void)
{
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    if( USBIsDeviceSuspended()== true )
    {
        return;
    }

    if( USBUSARTIsTxTrfReady() == true){
        led_red     = off;
        led_blue    = on;
        
        /*
         * Exemple pour envoyer un texte sur COM3 avec Putty :
         * --------------------------------------------------
         * Speed : 115200 bauds , Data bits : 8 bits ;
         * Parity : None ; Flow control : None.
         * 
         * Voir exemple dans fichier "usb_device_cdc.c".
         * 
         * !!! Envoie "Hello World" en boucle !!!
         * 
         * Il faudra gérer les caractères ASCII comme 0x40 <-> A.
         */
        char data[] = "Hello World";
        putsUSBUSART(data);
        
//        uint8_t i;
//        uint8_t numBytesRead;
//
//        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
//
//        for(i=0; i<numBytesRead; i++){
//            switch(readBuffer[i]){
//                /* echo line feeds and returns without modification. */
//                case 0x0A://LF (Line Feed, saut de ligne).
//                case 0x0D://CR (Carriage return, retour à la ligne) ??
//                    writeBuffer[i] = readBuffer[i];
//                    break;
//
//                /* all other characters get +1 (e.g. 'a' -> 'b') */
//                default:
//                    //writeBuffer[i] = readBuffer[i] + 1;
//                    //writeBuffer[i] = readBuffer[i];
//                    writeBuffer[0] = 0x55;
//                    writeBuffer[1] = 0x53;
//                    writeBuffer[2] = 0x42;
////                    writeBuffer[1] = 1;
////                    writeBuffer[2] = 2;
//                    break;
//            }
//        }
//
//        if(numBytesRead > 0){
//            putUSBUSART(writeBuffer,numBytesRead);
//        }
    }

    CDCTxService();
}
