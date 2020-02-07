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

void get_menu(char *data);

#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1

unsigned long       counter_while           = 0;






int main(void) {
    
    // initialize the device
    SYSTEM_Initialize();
    
    unsigned short  flag_menu       = 1;//"1" : Bloquer le menu.
    unsigned short  numBytesRead    = 0;
    unsigned short  i               = 0;
    uint8_t         data_write_com[64];
    uint8_t         data_read_com[64];
    char            menu_com[64];
    
    
    //Plugger l'USB pour démarrer le code.
    while(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended()== true){};
    
    led_red     = on;
    led_green   = off;
    
    get_menu(menu_com);
    
    while(1){
        if(flag_menu == 0){
            if(USBUSARTIsTxTrfReady() == true){
                putsUSBUSART(menu_com);
                flag_menu = 1;//Bloquer le menu.
            }
        }
        
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
            
            if(numBytesRead > 0){
                //putsUSBUSART(data_write_com);
                putUSBUSART(data_write_com,numBytesRead);
                //flag_menu = 0;//Relancer le menu.
            }
        }
        
        CDCTxService();
        
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
