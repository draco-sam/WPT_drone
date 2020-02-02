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
       
    

    unsigned short      flag_i2c_data_ready             = 0;//"0" = not ready.
    float               i2c_slave_v_in                  = 0;
    float               i2c_slave_charger_suspended     = 0;
    float               i2c_slave_precharge             = 0;
    float               i2c_slave_cc_cv_charge          = 0;
    float               i2c_slave_bat_missing           = 0;
    float               i2c_slave_bat_short             = 0;
    short               counter_while                   = 0;//Signed for a trick in while loop.
    unsigned short      tm_address                      = 0;
    unsigned short      timer_counter                   = 0;
    I2c_tm_analog       i2c_tm_analog;
    
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
    //i2c_master_start_read_tm(TM_CHEM_CELLS,&flag_i2c_data_ready);
    
    
    //printf("hello");
    
    
    
    //counter_max = 1;
    
    while (1)
    {
        /********************************************************************************
         * Prepare TM address for function "i2c_master_start_read_tm(...)" :
         * ----------------------------------------------------------------
         */
        if(flag_i2c_data_ready == 0 && tm_address == 0)
        {   
            if(counter_while == 0)
            {
               tm_address = TM_VIN;
            }
            else if(counter_while == 1)
            {
                tm_address = TM_CHARGER_STATE;
            }
            i2c_master_start_read_tm(tm_address,&flag_i2c_data_ready);
        }
        //*******************************************************************************
        
        /********************************************************************************
         * If com I2C completed, get analog compute TM from slave to master :
         * -----------------------------------------------------------------
         */
        if(flag_i2c_data_ready == 1)
        {
            i2c_tm_analog = i2c_master_get_tm(tm_address);//Analog value of the TM.
            
            if(counter_while == 0)//TM_VIN.
            {
                i2c_slave_v_in = i2c_tm_analog.data_1;
                led_red = on;
            }
            else if(counter_while == 1)//TM_CHARGER_STATE.
            {
                i2c_slave_charger_suspended     = i2c_tm_analog.data_1;
                i2c_slave_precharge             = i2c_tm_analog.data_2;
                i2c_slave_cc_cv_charge          = i2c_tm_analog.data_3;
                i2c_slave_bat_missing           = i2c_tm_analog.data_4;
                i2c_slave_bat_short             = i2c_tm_analog.data_5;
                
                //counter_while == -1;//-1 + 1 = 0 : Trick for new loop while and TM cycle.
                
                led_red     = off;
                led_green   = on;
            }
            
            tm_address = 0;//Reset address.
            flag_i2c_data_ready = 0;//Reset main flag.
            counter_while++;
            
            //!!! A retirer !!!
            if(counter_while > 1)
            {
                tm_address = 0xff;//Lancer une seule fois les 2 TM.
            }
            
        }
        //*******************************************************************************
        
        
        
//        
//        if(timer_counter <50000)
//        {
//            timer_counter++;
//        }
//        else
//        {
//            //LATDbits.LATD9 = !LATDbits.LATD9;
//            led_blue = !led_blue;
//            timer_counter = 0;
//        }
    }
    
    return 0;
}
