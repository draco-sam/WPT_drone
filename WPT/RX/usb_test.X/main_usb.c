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
unsigned short ascii_to_integer(unsigned char *table);
void integer_to_ascii(unsigned short data,uint8_t *table);


#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1



int main(void) {
    
    // initialize the device
    SYSTEM_Initialize();
    
    unsigned short  numBytesRead    = 0;
    unsigned short  i               = 0;
    unsigned short  menu_number     = 0xffff;//Bad menu number.
    unsigned long   counter_while   = 0;
    uint8_t         data_write_com[64];
    uint8_t         data_read_com[64];
    uint8_t         menu_com[64];
    //char            menu_com[64];
    //char            t_data_i2c[64];
    uint8_t         t_data_i2c[7];
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
    
    //get_menu(menu_com);
    
    menu_com[0] = 0x0d;//Carriage return.
    menu_com[1] = 0x0a;//Line Feed.
    menu_com[2] = 'M';
    menu_com[3] = 'e';
    menu_com[4] = 'n';
    menu_com[5] = 'u';
    menu_com[6] = 0x0d;//Carriage return.
    menu_com[7] = 0x0a;//Line Feed.

    
    while(1){
        /********************************************************************************
         * Display menu if USB COM ready :
         * ------------------------------
         */
        if(menu_number == 0xffff){
            if(USBUSARTIsTxTrfReady() == true){
                //putsUSBUSART(menu_com);
                putUSBUSART(menu_com,8);
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
                    menu_number = 0xffff;//Relancer le menu.
                    led_red     = off;
                    led_green   = off;
                    led_blue    = on;
                }
                data_write_com[i] = data_read_com[i];
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
        else if (menu_number == 3){
            led_red     = off;
            led_blue    = on;
            led_green   = on;
//            
            if(USBUSARTIsTxTrfReady() == true){
////                while(counter_while < 500000){
////                    counter_while++;
////                }
////                counter_while = 0;//Reset.
//                
//                //get_data_i2c(t_data_i2c);
//                //putsUSBUSART(t_data_i2c);
                //t_data_i2c[0] = '\n\r';
                t_data_i2c[0] = 0x0d;//Carriage return.
                t_data_i2c[1] = 0x0a;//Line Feed.
                t_data_i2c[2] = 'V';
                t_data_i2c[3] = 'b';
                t_data_i2c[4] = 'a';
                t_data_i2c[5] = 0x0d;//Carriage return.
                t_data_i2c[6] = 0x0a;//Line Feed.
                putUSBUSART(t_data_i2c,7);
                menu_number = 0xffff;
//              
//////                numBytesRead = getsUSBUSART(data_read_com, sizeof(data_read_com));
//////                if(numBytesRead > 0){
//////                    menu_number = 0xffff;//Utile ???
//////                }
//////                else{
//////                    get_data_i2c(t_data_i2c);
//////                    putsUSBUSART(t_data_i2c);
//////                }
////                
            }
////            //menu_number = 0xffff;//Reset.
        }
//        
    }//End of principal while.
    
    
    return 0;
}


void get_menu(char *data_com){
/*
 * 
 */
    char data[]     = "\n\nMain Menu :\r\n----------\r\n"
    "1 : Vbatttttttt \r\n"
    "2 : Ibat \r\n"
    "3 : Vbat ; Ibat ; T \r\n"
    "----------\r\n";
    
    strcpy(data_com,data); 
}
//__________________________________________________________________________________________________

void get_data_i2c(char *t_data){
/*
 * 
 */
    char data[]     = "\r\nVbat = 3.94 V ; Ibat = 0.912 A ; T = 36 deg C \r\n";
    
    strcpy(t_data,data); 
}
//__________________________________________________________________________________________________


unsigned short ascii_to_integer(unsigned char *table){
/*
 * 
 */
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    unsigned short  table_integer[11]   = {0,1,2,3,4,5,6,7,8,9};
    unsigned short  i                   = 0;
    unsigned short  data_integer        = 0;
    
    //for(i=0 ; i < strlen(table) ; i++){
    for(i=0 ; i < 64 ; i++){
        if(table_ascii[i] == table[0]){
            data_integer = table_integer[i];
        }
    }
    
    return data_integer;
}
//__________________________________________________________________________________________________

void integer_to_ascii(unsigned short data,uint8_t *table){
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



