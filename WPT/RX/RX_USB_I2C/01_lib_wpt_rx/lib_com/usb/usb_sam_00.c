/*************************************************************************************************** 
 * File             : usb_sam_00.c
 * Date             : 25/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "usb_sam_00.h"

#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1

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
    unsigned short  i_table             = 0;
    unsigned short  i_ascii             = 0;
    unsigned short  data_integer        = 0;
    
    //Brows all char in the retrieved table :
    for(i_table=0 ; i_table < strlen(table) ; i_table++){
        //Compare with local ascii table :
        i_ascii = 0;//Reset every turn of for (and out of while).
        while(i_ascii < sizeof(table_ascii)){
            if(table_ascii[i_ascii] == table[i_table]){
                data_integer = table_integer[i_ascii] + (data_integer * 10);
            }
            i_ascii++;
        }
    }
    
    return data_integer;
}
//__________________________________________________________________________________________________

void write_usb_com(char *t_data,unsigned short *flag_sending){
/*
 * 
 */
//    char            t_data_com[250]  = "";
//
//    strcpy(t_data_com,t_data);//!!! Enlever ???
//    
//    unsigned short size_1 = 0;
//    unsigned short size_2 = 0;
//    size_1 = strlen(t_data);
//    size_2 = strlen(t_data_com);

    if(USBUSARTIsTxTrfReady() == true){
        putUSBUSART(t_data,strlen(t_data));//strlen(t_data).
        //putUSBUSART(t_data_com,strlen(t_data_com));
        *flag_sending = 1;
    }
}
//__________________________________________________________________________________________________

void read_usb_com(unsigned short  *menu_number){
/*
 * If bus USB COM ready, check if a byte is placed on the read buffer.
 */
    if( USBUSARTIsTxTrfReady() == true){
        uint8_t i;
        uint8_t numBytesRead;
        unsigned char readBuffer[64]        = "";
        unsigned char writeBuffer[64]       = "";//[128] fonctionne aussi.
        static unsigned char menuBuffer[5] 	= "";//max 9999.
        static unsigned short i_menu        = 0;

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

        for(i=0; i<numBytesRead; i++){
            if(readBuffer[i] == 0x0d){//0x0d = CR (0x0a = LF).
                led_red     = off;
                led_green   = off;
                led_blue    = on;
            }
            else if(readBuffer[i] != 0x0a){//Diff de LF.
                /*******************************************
                 * Save menu number :
                 * -----------------
                 */
                if(i_menu < sizeof(menuBuffer)){
                    menuBuffer[i_menu] = readBuffer[i];
                    i_menu++;//For next tour.
                }
                else{
                    i_menu = 0;//Reset.
                }
                /******************************************/
            }
        }//End for.

        if(numBytesRead > 0){
            /* Carriage return (CR, 0x0d) detection :
             * -------------------------------------
             * If CR, convert ASCII numbers into integer for main if.
             */
            if(readBuffer[0] == 0x0d){//Détecter le CR (ENTER dans console).
                //writeBuffer[1] = 0x0a;//LF

                *menu_number =  ascii_to_integer(menuBuffer);
                if(*menu_number == 0){
//                    led_red     = off;
//                    led_green   = on;
//                    led_blue    = on;
                }
                empty_table(menuBuffer,sizeof(menuBuffer));//Effacer à chaque CR.
                i_menu = 0;//Reset.
            }
        }
    }
}
//__________________________________________________________________________________________________

void empty_table(char *table,unsigned short t_size){
/*
 * Empty the table :
 * ----------------
 */
    unsigned short i_empty = 0;
    
    //for(i_empty=0 ; i_empty < sizeof(table) ; i_empty++){
    for(i_empty=0 ; i_empty < t_size ; i_empty++){
        table[i_empty] = '\0';//NULL.
    }
}
//__________________________________________________________________________________________________

