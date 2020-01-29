/* 
 * File             : main_wpt_rx_00.c
 * Date             : 25/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\PIC24F\h.
#include "lib_wpt_rx/lib_wpt_rx_00.h"



int main(void) {
    
       
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
    
    
    

    unsigned short  flag_i2c_data_ready = 0;//"0" = not ready.
    float             i2c_analog_measure        = 0;
    
    Nop();
    
    
    pin_init();
    oscillator_init();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    i2c_master_init();

    //i2c_master_start_read_tm(TM_VIN,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_VSYS,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_DIE_TEMP,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_NTC_RATIO,&flag_i2c_data_ready);
    i2c_master_start_read_tm(TM_CHEM_CELLS,&flag_i2c_data_ready);
    
    
//    unsigned long counter = 0;
    
    
    while (1)
    {
        if(flag_i2c_data_ready == 1)
        {
            i2c_analog_measure    = i2c_master_get_tm(TM_VIN);//Analog value of the TM.
            
                          
            if(10e3 + 1 == 10001)
            {
                led_red = on;
            }
            
        }
        
        
//        if(counter <1000)
//        {
//            counter++;
//        }
//        else
//        {
//            LATDbits.LATD9 = !LATDbits.LATD9;
//            led_red = !led_red;
//            counter = 0;
//        }
    }
    
    return 0;
}
