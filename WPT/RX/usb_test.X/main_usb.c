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
void write_usb_com(char *t_data,unsigned short *flag_sending);




#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1



int main(void) {
    unsigned short  numBytesRead    = 0;
    unsigned short  i               = 0;
    unsigned short  menu_number     = 0xfffe;//Bad menu number.
    unsigned short  f_data_sending  = 0;//Flag for write USB COM and main loop.
    unsigned long   counter_while   = 0;
    char            t_empty[64]     = "";//Pour effacer les 64 bytes.<-> à NULL.
    char            t_data_i2c[64]  = "";
    uint8_t         data_write_com[64];
    uint8_t         data_read_com[64];
    uint8_t         menu_com[64];
    //char            menu_com[64];
    //char            t_data_i2c[64];
    
    //char            t_data_i2c      = "Vbat = 3.97 V ; Ibat = 0.965 A ; T = 36 \r";
    
    //    unsigned char   t_data_usb_com_3[] = " : T die = 36 deg Celicuuuuuuuuuuuuus";
    //    unsigned short  i_3 = 0;
    //    unsigned short  counter_max = 27;
    //    
    //    strcpy(t_data_i2c,t_data_usb_com_3);
    //    
    //    for(i_3=0 ; i_3 < (64-38); i_3++){
    //        t_data_i2c[39 + i_3] = 0;
    //    }
    
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
            write_usb_com("\r\nMenu : \r\n",&f_data_sending);//Bug si M collé,ancienne data??
            
//            if(USBUSARTIsTxTrfReady() == true){
//                //putsUSBUSART(menu_com);
//                putUSBUSART(menu_com,8);
//                menu_number = 0xfffe;//Bloquer le menu.
//            }
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
            
            write_usb_com(" : Vbattery = 3.97 Vvvvvvvvvvvvvvvvvvv \r\n",&f_data_sending);
        }
        else if (menu_number == 2){
            led_red     = off;
            led_blue    = off;
            led_green   = on;
            
            write_usb_com(" : Ibattery = 1387 mA \r\n",&f_data_sending);
        }
        else if (menu_number == 3){
            led_red     = off;
            led_blue    = on;
            led_green   = on;
           
            write_usb_com(" : T die = 36 deg Celicuuuuuuuuuuuuus \r\n",&f_data_sending);
            
        }
        
        /************************************************************
         * If data USB COM is sending with "write_usb_com()", 
         * bad menu_number to not display the menu.
         */
        if(f_data_sending == 1){
            menu_number     = 0xfffe;
            f_data_sending  = 0;//Reset flag.
        }
        /***********************************************************/
        
    }//End of principal while.
    
    
    return 0;
}


void get_menu(char *data_menu){
/*
 * 
 */
    char data[]     = "\n\nMain Menu :\r\n----------\r\n"
    "1 : Vbatttttttt \r\n"
    "2 : Ibat \r\n"
    "3 : Vbat ; Ibat ; T \r\n"
    "----------\r\n";
    
    strcpy(data_menu,data); 
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

void integer_to_ascii(unsigned short data,uint8_t *t_table){
/*
 * data max : 65535.
 */
    //unsigned short  table_lenght        = 0;
    unsigned short  data_1              = 0;
    unsigned short  data_2              = 0;
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    
    //table_lenght = sizeof(table);
    
    //Ex : 54321.
    data_1      = data / 10;                    //54321 / 10        = 5432.
    data_2      = data_1 * 10;                  //5432 * 10         = 54320.
    t_table[4]    = table_ascii[data - data_2];   //54321 - 54320     = 1.
    
    data_2      = (data_1 / 10) * 10;           //(5432 / 10) * 10  = 5430.
    t_table[3]    = table_ascii[data_1 - data_2]; //4532 - 5430       = 2.
    data_1      = data_1 / 10;                  //5432 / 10         = 543.
    
    data_2      = (data_1 / 10) * 10;           //(543 /10) * 10    = 540.  
    t_table[2]    = table_ascii[data_1 - data_2]; //543 - 540         = 3.
    data_1      = data_1 / 10;                  //543 / 10          = 54.
    
    data_2      = (data_1 / 10) * 10;           //(54/10) * 10      = 50.
    t_table[1]    = table_ascii[data_1 - data_2]; //54 - 50           = 4.
    data_1      = data_1 / 10;                  //54 / 10           = 5.
    
    t_table[0]    = table_ascii[data_1];
}
//__________________________________________________________________________________________________

void write_usb_com(char *t_data,unsigned short *flag_sending){
/*
 * 
 */
    unsigned short  i               = 0;
    char            t_data_com[64]  = "";
    
            
    //Nettoyer le tableau avant utilisation :
    for(i=0 ; i < sizeof(t_data_com) ; i++){
            t_data_com[i] = 0;//NULL.
    }

    strcpy(t_data_com,t_data);

    if(USBUSARTIsTxTrfReady() == true){
        putUSBUSART(t_data_com,sizeof(t_data_com));
        *flag_sending = 1;
    }
}
//__________________________________________________________________________________________________

