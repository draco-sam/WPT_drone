/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 31/03/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/rtcc.h"
//#include <time.h>

/*
                         Main application
 */

typedef struct
	{	/* date and time components */
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	}Date_time;

void set_data_time(int year,int month,int day,int weekDay,int hours,int minutes,int seconds);
    
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //-----------------------------------------------------
    //For RGB LEDs :
    //-------------
    //Configurer les IO des leds en output :
    TRISEbits.TRISE7    = 0;//"0" : Output.
    TRISGbits.TRISG6    = 0;
    TRISGbits.TRISG7    = 0;
    
    //Pour les leds en digital io.    
    ANSEbits.ANSELE7 = 0;
    ANSGbits.ANSELG6 = 0;
    ANSGbits.ANSELG7 = 0;
    
    //Define IO for leds :
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
    
    //All leds OFF :
    led_red     = off;
    led_blue    = off;
    led_green   = off;
    //-----------------------------------------------------
    
    led_red = on;
    
    //-----------------------------------------------------
    //Déclaration des variables main :
    //-------------------------------
    Date_time       str_data_time;
    bool            rtcc_status = false;
    //-----------------------------------------------------
    
    
 
    rtcc_status = RTCC_TimeGet(&str_data_time);
    
    set_data_time(0,0,0,0,0,0,0);
    
    rtcc_status = RTCC_TimeGet(&str_data_time);
    Nop();

    while (1)
    {
        rtcc_status = RTCC_TimeGet(&str_data_time);
        
        Nop();
        Nop();
    }

    return 1;
}
/**
 End of File
*/
//__________________________________________________________________________________________________

void set_data_time(int year,int month,int day,int weekDay,int hours,int minutes,int seconds){
/*
 * Ecrire en BCD chaque valeur.
 * Ex : 2020 ->0x20 ; 20h42min57sec ->0x20/0x42/0x57. 
 */  
    Date_time date_time_structure;
    date_time_structure.tm_year = 0x20;
    date_time_structure.tm_mon  = 0x03;
    date_time_structure.tm_mday = 0x31;
    date_time_structure.tm_wday = 0x02;
    date_time_structure.tm_hour = 0x12;
    date_time_structure.tm_min  = 0x15;
    date_time_structure.tm_sec  = 0x00;
    
    RTCC_BCDTimeSet(&date_time_structure);
}