/*************************************************************************************************** 
 * File             : main_usb.c
 * Date             : 18/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include <xc.h>
#include "mcc_generated_files/system.h"

//#include "mcc_generated_files/PIC24FJ128GC006.h"
#include "mcc_generated_files/usb/usb_device_cdc.h"
#include "mcc_generated_files/PIC24FJ128GC006.h"


void get_menu(char *data);
void get_data_i2c(char *t_data);
unsigned short ascii_to_integer(unsigned char *table);
void float_to_ascii(float data_float,char *t_table);
void write_usb_com(char *t_data,unsigned short *flag_sending);
void extract_integer_decimal(float data,unsigned short *data_integer,unsigned short *data_decimal);
void empty_table(char *table,unsigned short t_size);




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
    char            t_data_i2c[64]  = "";//!!! Changer taille car 16 bits max !!!
    char            t_data_usb_com[200]  = "";
    char            t_data_1[64]    = "";
    //uint8_t         data_write_com[64];
    //uint8_t         data_read_com[64];
    //uint8_t         menu_com[64];
    char            menu_com[64]    = "";
    
    

   
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
    

    
    //Plugger l'USB pour d�marrer le code.
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
         * Read buffer if USB COM ready :
         * -----------------------------
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
                if(writeBuffer[0] == 0x0d){//D�tecter le CR (ENTER dans console).
                    //writeBuffer[1] = 0x0a;//LF
                    
                    putUSBUSART(writeBuffer,strlen(writeBuffer));//(...,2).
                    
                    //Si CR, convertir le tableau static :
                    menu_number =  ascii_to_integer(menuBuffer);
                    if(menu_number == 0){
                        led_red     = off;
                        led_green   = on;
                        led_blue    = on;
                    }
                    empty_table(menuBuffer,sizeof(menuBuffer));//Effacer � chaque CR.
                    i_menu = 0;//Reset.
                }
                else{
                    putUSBUSART(writeBuffer,numBytesRead);
                }
            }
        }
        /*******************************************************************************/
        
        CDCTxService();
        
        unsigned short i2c_data_integer     = 0;
        unsigned short i2c_data_decimal     = 0;
        
        empty_table(t_data_i2c,sizeof(t_data_i2c));
        empty_table(t_data_usb_com,sizeof(t_data_usb_com));
        empty_table(t_data_1,sizeof(t_data_1));
        
        if(menu_number == 0){
            //!!! Trop long pour "strcpy()", pq ???
            char test_menu[250] =   "\n---------------\r\n"
                                    "Menu : \r\n"
                                    "-----\r\n"
                                    "1 : Vbat \r\n"
                                    "2 : Ibat \r\n"
                                    "3 : Die T \r\n"
                                    "---------------\r\n";
            write_usb_com(test_menu,&f_data_sending);
        }
        else if(menu_number == 1){
            
            float_to_ascii(4.567,t_data_i2c);
            
            //!!! A faire : write_usb_com("Vbat = ",t_data_i2c," Volts \r\n") !!!
            strcpy(t_data_usb_com,"1 : Vbat = ");
            strcat(t_data_usb_com,t_data_i2c);
            strcat(t_data_usb_com," Volllllltssss \r\n");
            
            write_usb_com(t_data_usb_com,&f_data_sending);
        }
        else if (menu_number == 2){
            
            float_to_ascii(0.783,t_data_i2c);
            
            //Prepare data COM with string copy and concatenation :            
            strcpy(t_data_usb_com,"2 : Ibat = ");
            strcpy(t_data_1," mA \r\n");
            strcat(t_data_usb_com,t_data_i2c);
            strcat(t_data_usb_com,t_data_1);
            
            write_usb_com(t_data_usb_com,&f_data_sending);
        }
        else if (menu_number == 3){
           
            float_to_ascii(36.413,t_data_i2c);
            
            //Prepare data COM with string copy and concatenation :            
            strcpy(t_data_usb_com,"3 : Die temperature = ");
            strcpy(t_data_1," deg C \r\n");
            strcat(t_data_usb_com,t_data_i2c);
            strcat(t_data_usb_com,t_data_1);
            
//            t_data_usb_com[0] = "T";
//            t_data_usb_com[1] = " ";
//            t_data_usb_com[2] = ":";
//            t_data_usb_com[3] = "";
//            t_data_usb_com[4] = "";
//            t_data_usb_com[5] = "";
//            t_data_usb_com[6] = "0";
//            t_data_usb_com[7] = ",";
//            t_data_usb_com[8] = "4";
//            t_data_usb_com[9] = "\0";
            
            write_usb_com(t_data_usb_com,&f_data_sending);
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
    unsigned short  i               = 0;
    char            t_data_com[200]  = "";
    
            
//    //Nettoyer le tableau avant utilisation :
//    for(i=0 ; i < sizeof(t_data_com) ; i++){
//            t_data_com[i] = 0;//NULL.
//    }

    strcpy(t_data_com,t_data);

    if(USBUSARTIsTxTrfReady() == true){
        //putUSBUSART(t_data_com,sizeof(t_data_com));
        //putUSBUSART(t_data_com,strlen(t_data_com));
        putUSBUSART(t_data,strlen(t_data));
        *flag_sending = 1;
    }
}
//__________________________________________________________________________________________________

void extract_integer_decimal(float data,unsigned short *data_integer,unsigned short *data_decimal){
/*
 * Extraire la partie enti�re et d�cimale d'un nombre float.
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
    unsigned short i_empty  = 0;
    
    //for(i_empty=0 ; i_empty < sizeof(table) ; i_empty++){
    for(i_empty=0 ; i_empty < t_size ; i_empty++){
        table[i_empty] = '\0';//NULL.
    }
}
//__________________________________________________________________________________________________

