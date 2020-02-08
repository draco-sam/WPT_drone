/*
 * File:   main_usb.c
 * Author: Draco
 *
 * Created on 7 février 2020, 21:15
 */

#include <xc.h>
#include "mcc_generated_files/system.h"

//#include "mcc_generated_files/PIC24FJ128GC006.h"
#include "mcc_generated_files/usb/usb_device_cdc.h"
#include "mcc_generated_files/PIC24FJ128GC006.h"
#include <string.h>

void get_menu(char *data);
void get_data_i2c(char *t_data);

#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1

unsigned short ascii_to_integer(char *table);

int main(void) {
    
    // initialize the device
    SYSTEM_Initialize();
    
    unsigned short  numBytesRead    = 0;
    unsigned short  i               = 0;
    unsigned short  menu_number     = 0xffff;//Bad menu number.
    unsigned long   counter_while   = 0;
    uint8_t         data_write_com[64];
    uint8_t         data_read_com[64];
    char            menu_com[64];
    char            t_data_i2c[64];
    //char            t_data_i2c      = "Vbat = 3.97 V ; Ibat = 0.965 A ; T = 36 \r";
    
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
    
    
    //Plugger l'USB pour démarrer le code.
    while(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended()== true){};
    
    led_red     = on;
    led_green   = off;
    
    get_menu(menu_com);
    
    while(1){
        /********************************************************************************
         * Display menu if USB COM ready :
         * ------------------------------
         */
        if(menu_number == 0xffff){
            if(USBUSARTIsTxTrfReady() == true){
                putsUSBUSART(menu_com);
                menu_number = 0xfffe;//Bloquer le menu.
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
                    menu_number = 0xffff;//Relancer le menu.
                    led_red     = off;
                    led_green   = off;
                    led_blue    = on;
                }
                else{
                    data_write_com[i] = data_read_com[i];
                }
            }
            
            if(numBytesRead > 0){
                //putsUSBUSART(data_write_com);
                putUSBUSART(data_write_com,numBytesRead);
                
                if(data_read_com[0] != 0x0d){
                    menu_number = ascii_to_integer(data_read_com);
                }
            }
        }
        /*******************************************************************************/
        
        CDCTxService();
        
        if(menu_number == 1){
            led_blue    = off;
            led_green   = off;
            led_red     = on;
            menu_number = 0;//Reset.
        }
        else if (menu_number == 2){
            led_red     = off;
            led_blue    = off;
            led_green   = on;
            menu_number = 0;//Reset.
        }
//        else if (menu_number == 3){
//            led_red     = off;
//            led_blue    = on;
//            led_green   = on;
//            
//            if(USBUSARTIsTxTrfReady() == true){
//                while(counter_while < 500000){
//                    counter_while++;
//                }
//                counter_while = 0;//Reset.
//                
//                numBytesRead = getsUSBUSART(data_read_com, sizeof(data_read_com));
//                if(numBytesRead > 0){
//                    menu_number = 0;//Utile ???
//                    flag_menu   = 0;
//                }
//                else{
//                    get_data_i2c(t_data_i2c);
//                    putsUSBUSART(t_data_i2c);
//                }
//                
//            }
//        }
        
    }//End of principal while.
    
    
    return 0;
}


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

void get_data_i2c(char *t_data){
/*
 * 
 */
    char data[]     = "Vbat = 3.94 V ; Ibat = 0.912 A ; T = 36 \r";
    
    strcpy(t_data,data); 
}
//__________________________________________________________________________________________________


unsigned short ascii_to_integer(char *table){
/*
 * 
 */
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    unsigned short  table_integer[11]   = {0,1,2,3,4,5,6,7,8,9};
    unsigned short  i                   = 0;
    unsigned short  data_integer        = 0;
    
    for(i=0 ; i < strlen(table) ; i++){
        if(table_ascii[i] == table[0]){
            data_integer = table_integer[i];
        }
    }
    
    return data_integer;
}
//__________________________________________________________________________________________________