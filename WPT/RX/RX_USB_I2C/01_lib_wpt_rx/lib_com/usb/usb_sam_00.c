/*************************************************************************************************** 
 * File             : usb_sam_00.c
 * Date             : 12/02/2020.   
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

//void integer_to_ascii(unsigned short data_integer,unsigned short data_decimal,char *t_table){
void float_to_ascii(float data_float,char *t_table){
/*
 * data max : 65535.
 */
    unsigned short  data_integer        = 0;
    unsigned short  data_decimal        = 0;
    unsigned short  data_1              = 0;
    unsigned short  data_2              = 0;
    unsigned short  i                   = 0;
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    char            t_integer[6]        = {0};
    char            t_decimal[5]        = {0};
    
    extract_integer_decimal(data_float,&data_integer,&data_decimal);
    
    if(data_integer > 0){
        t_integer[5] = '\0';
        //Ex : 54321.
        data_1          = data_integer / 10;                    //54321 / 10        = 5432.
        data_2          = data_1 * 10;                  //5432 * 10         = 54320.
        t_integer[4]    = table_ascii[data_integer - data_2];   //54321 - 54320     = 1.

        data_2          = (data_1 / 10) * 10;           //(5432 / 10) * 10  = 5430.
        t_integer[3]    = table_ascii[data_1 - data_2]; //4532 - 5430       = 2.
        data_1          = data_1 / 10;                  //5432 / 10         = 543.

        data_2          = (data_1 / 10) * 10;           //(543 /10) * 10    = 540.  
        t_integer[2]    = table_ascii[data_1 - data_2]; //543 - 540         = 3.
        data_1          = data_1 / 10;                  //543 / 10          = 54.

        data_2          = (data_1 / 10) * 10;           //(54/10) * 10      = 50.
        t_integer[1]    = table_ascii[data_1 - data_2]; //54 - 50           = 4.
        data_1          = data_1 / 10;                  //54 / 10           = 5.

        t_integer[0]    = table_ascii[data_1];//5.
    }
    else{
       t_integer[0] = '0';
    }
    
    if(data_decimal > 0){//Ex : 728 mA.
        t_decimal[4] = '\0';
        
        data_1 = 0;//Reset.
        data_2 = 0;//Reset.
        
        data_1          = data_decimal / 10;                
        data_2          = data_1 * 10;                 
        t_decimal[3]    = table_ascii[data_decimal - data_2];//8.  

        data_2          = (data_1 / 10) * 10;
        t_decimal[2]    = table_ascii[data_1 - data_2];
        data_1          = data_1 / 10;//2.
        
        t_decimal[1]    = table_ascii[data_1];//7.
        
        t_decimal[0]    = ',';
    }
    
    
    strcpy(t_table,t_integer);
    strcat(t_table,t_decimal);
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
            writeBuffer[i] = readBuffer[i];
        }//End for.

        if(numBytesRead > 0){
            if(writeBuffer[0] == 0x0d){//Détecter le CR (ENTER dans console).
                //writeBuffer[1] = 0x0a;//LF

                putUSBUSART(writeBuffer,strlen(writeBuffer));//(...,2).

                //Si CR, convertir le tableau static :
                *menu_number =  ascii_to_integer(menuBuffer);
                if(*menu_number == 0){
                    led_red     = off;
                    led_green   = on;
                    led_blue    = on;
                }
                empty_table(menuBuffer,sizeof(menuBuffer));//Effacer à chaque CR.
                i_menu = 0;//Reset.
            }
            else{
                putUSBUSART(writeBuffer,numBytesRead);
            }
        }
    }
}
//__________________________________________________________________________________________________

void extract_integer_decimal(float data,unsigned short *data_integer,unsigned short *data_decimal){
/*
 * Extraire la partie entière et décimale d'un nombre float.
 * Ne fonctionne que jusque 10^-3.
 * 
 * Ex avec 248 mA :
 *      data_integer = 0.
 *      data_decimal = 248 - 0 = 248.
 * 
 * Ex avec 23.746 V :
 *      data_integer = 23.
 *      data_decimal = 23746 - 23000 = 746.
 */
    *data_integer   = data;
    *data_decimal   = (data * 1000) - (*data_integer * 1000);
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

