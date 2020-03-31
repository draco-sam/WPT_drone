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
    
#define lundi       0x01;
#define mardi       2;
#define mercredi    0x03;
#define jeudi       0x04;
#define vendredi    0x05;
#define samedi      0x06;
#define dimanche    0x07;
    

void set_data_time(int year,int month,int day,int weekDay,int hours,int minutes,int seconds);
unsigned long convertTimeToSeconds(unsigned int hour,unsigned int minutes,unsigned int seconds);
    
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
    bool            rtcc_status     = false;
    unsigned long   seconds_main    = 0;
    //-----------------------------------------------------
    
    unsigned long   data    = 0;
    
    //data = convertBcdTimeToSeconds(0x23,0x59,0x59);
    Nop();
    
    data = 0;//Reset.
    data = convertBcdToHex(0x40);
    Nop();
 
    rtcc_status = RTCC_TimeGet(&str_data_time);
    
    set_data_time(20,3,31,2,15,40,0);//Year,month,day,weekday,hour,min,sec.
    
    rtcc_status = RTCC_TimeGet(&str_data_time);
    Nop();

    while (1)
    {
        rtcc_status = RTCC_TimeGet(&str_data_time);
        seconds_main = convertTimeToSeconds(str_data_time.tm_hour,str_data_time.tm_min,
                      str_data_time.tm_sec);
        
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
 * Ex : 2020 ->0x20 ; 20h42/min/57sec ->0x20/0x42/0x57.
 * 
 * In parameters : integer data in hex format. 
 */  
    Date_time date_time_structure;
    date_time_structure.tm_year = convertHexToBcd(year);
    date_time_structure.tm_mon  = convertHexToBcd(month);
    date_time_structure.tm_mday = convertHexToBcd(day);
    date_time_structure.tm_wday = convertHexToBcd(weekDay);
    date_time_structure.tm_hour = convertHexToBcd(hours);
    date_time_structure.tm_min  = convertHexToBcd(minutes);
    date_time_structure.tm_sec  = convertHexToBcd(seconds);
    
    RTCC_BCDTimeSet(&date_time_structure);
}
//__________________________________________________________________________________________________

unsigned long convertTimeToSeconds(unsigned int hour,unsigned int minutes,unsigned int seconds){
/*
 * Type of variables long because of the max hour multiply by the seconds (23*3600 = 82800).
 * The multiplication doesn't like different type. 
 */ 
     unsigned long total_seconds = 0;
    
    if(hour >= 1){
        total_seconds = hour * 3600;//1h <-> 3600s.
    }
    if(minutes >= 1){
        total_seconds = (minutes * 60) + total_seconds;//Add previous hour conversion.
    }
    if(seconds >= 1){
        total_seconds = seconds + total_seconds;
    }
    
    return total_seconds;
}