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

void integer_to_ascii(unsigned short data,char *table);
void get_menu(char *data);

int main(void){
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
    
    unsigned long       counter_while           = 0;
    

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
    
    //0x0D : Carriage return.
    //0x0A : Line feed.
    char data_4[]   = {0x0d,0x0a};
    char table[5]   = {'0'};//Tableau pour tester la conversion vers ascii.
        
    char data_com1[]    = "Menu I2C...";
    char vbat_com[]     = "16.82 V\r\n";
    char ibat_com[]     = "1.8 A\r\n\n";
    
    unsigned short  flag_menu       = 1;//"1" : Bloquer le menu.
    unsigned short  numBytesRead    = 0;
    unsigned short  i               = 0;
    unsigned short  i_a               = 0;
    //char            data_write_com[64];
    //char            data_read_com[64];
    unsigned int    data_write_com[64];
    unsigned int    data_read_com[64];
    char            menu_com[64];
    //unsigned short  menu_sam     = 0;

    
    integer_to_ascii(54321,table);
    Nop();
    Nop();
    
    //Plugger l'USB pour d�marrer le code.
    while(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended()== true){};
    
    led_red     = on;
    led_green   = off;
    
    get_menu(menu_com);
    
    while (1){
        //MCC_USB_CDC_DemoTasks();
        
        /********************************************************************************
         * Display menu if USB COM ready :
         * ------------------------------
         */
        if(flag_menu == 0){
            if(USBUSARTIsTxTrfReady() == true){
                putsUSBUSART(menu_com);
                flag_menu = 1;//Bloquer le menu.
            }
        }
        /*******************************************************************************/
            
        /********************************************************************************
         * Read buffer if USB COM ready :
         * -----------------------------
         */
        if(USBUSARTIsTxTrfReady() == true){
            numBytesRead = getsUSBUSART(data_read_com, sizeof(data_read_com));

            for(i=0; i<numBytesRead; i++){
                if(data_read_com[i] == 0x0d){
                    data_write_com[i] = 0x0d;
                    flag_menu = 0;//Relancer le menu.
                    led_red = off;
                    led_blue = on;
                }
                else{
                    data_write_com[i] = data_read_com[i];
                }
            }
            
//            if(data_read_com[0] != 0x0d){
//                menu_number = data_read_com[0];
//            }
            
            if(numBytesRead > 0){
                //putsUSBUSART(data_write_com);
                putUSBUSART(data_write_com,numBytesRead);
                //flag_menu = 0;//Relancer le menu.
            }
        }
        /*******************************************************************************/
        
        
        CDCTxService();
        
//        while(counter_while < 1e+6){
//        counter_while++; 
//        } 
    }

    return 1;
}
//__________________________________________________________________________________________________

void integer_to_ascii(unsigned short data,char *table){
/*
 * data max : 65535.
 */
    //unsigned short  table_lenght        = 0;
    unsigned short  data_1              = 0;
    unsigned short  data_2              = 0;
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    
    //table_lenght = sizeof(table);
    
    //Ex : 54321.
    data_1      = data / 10;    //54321 / 10 = 5432.
    data_2      = data_1 * 10;  //5432 * 10 = 54320.
    table[4]    = table_ascii[data - data_2]; //54321 - 54320 = 1.

    data_2      = (data_1 / 10) * 10;//(5432 / 10) * 10 = 5430.
    table[3]    = table_ascii[data_1 - data_2]; //5432 - 5430 = 2.
    
    data_1      = data_1 / 10;//5432 / 10 = 543.
    data_2      = (data_1 / 10) * 10;//(543 / 10) * 10 = 540.
    table[2]    = table_ascii[data_1 - data_2]; //543 - 540 = 3.
    
    data_1      = data_1 / 10;//543 / 10 = 54.
    data_2      = (data_1 / 10) * 10;//(54 / 10) * 10 = 50.
    table[1]    = table_ascii[data_1 - data_2]; //54 - 50 = 4.
    
    table[0]    = table_ascii[data_1 / 10]; //54 / 10 = 5.
}
//__________________________________________________________________________________________________

void get_menu(char *data_com){
/*
 * 
 */
    char data[]     = "\n\nMain Menu :\r\n----------\r\n"
    "1 : Vbat \r\n"
    "2 : Ibat \r\n"
    "----------\r\n";
    
    strcpy(data_com,data);
    
   
                           
}
//__________________________________________________________________________________________________