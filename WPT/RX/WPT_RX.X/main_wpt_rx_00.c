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
    unsigned short      counter_while                   = 0;
    unsigned short      tm_address                      = 0;
    unsigned short      counter_max                     = 0;
    I2c_tm_analog       i2c_tm_analog;
    
    Nop();
    
    
    pin_init();
    oscillator_init();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    i2c_master_init();

    i2c_master_start_read_tm(TM_VIN,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_VSYS,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_DIE_TEMP,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_NTC_RATIO,&flag_i2c_data_ready);
    //i2c_master_start_read_tm(TM_CHEM_CELLS,&flag_i2c_data_ready);
    
    
//    unsigned long counter = 0;
    
    //printf("hello");
    
    
    while (1)
    {        
        /********************************************************************************
         * Get analog compute TM from slave to master :
         * ------------------------------------
         */
        if(flag_i2c_data_ready == 1)
        {
            i2c_tm_analog = i2c_master_get_tm(tm_address);//Analog value of the TM.
            led_red = on;
            
            
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
                
                //led_red     = off;
                //led_green   = on;
            }
            
            counter_while++;
            
            /***************************************************************************
             * Prepare TM address for function "i2c_master_start_read_tm(...)" :
             * ----------------------------------------------------------------
             */
            if(counter_while == 1)
            {
                tm_address = TM_CHARGER_STATE;
            }
            //**************************************************************************

            if(counter_while <= counter_max)
            {
                i2c_master_start_read_tm(tm_address,&flag_i2c_data_ready);
            }
             else
            {
                counter_while = 0;//Reset counter in other cases.
            }
            
            flag_i2c_data_ready = 0;//Reset main flag.
            //counter_while++;
            
        }
        //*******************************************************************************
        
        
        
        
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
