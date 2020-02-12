/*************************************************************************************************** 
 * File             : main_wpt_rx_00.c
 * Date             : 12/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\PIC24F\h.


#include "lib_wpt_rx/lib_wpt_rx_00.h"



int main(void) {
    
       
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
       
    

    unsigned short      flag_i2c_data_ready             = 0;//"0" = not ready.
    unsigned short      flag_i2c_end_writing            = 0;//"0" = write not ending.
    float               i2c_slave_v_in                  = 0;
    float               i2c_slave_charger_suspended     = 0;
    float               i2c_slave_precharge             = 0;
    float               i2c_slave_cc_cv_charge          = 0;
    float               i2c_slave_bat_missing           = 0;
    float               i2c_slave_bat_short             = 0;
    short               counter_while                   = 0;//Signed for a trick in while loop.
    unsigned short      tm_address                      = 0;
    unsigned short      tx_address                      = 0;
    unsigned long       timer_counter                   = 0;
    I2c_tm_analog       i2c_tm_analog;//Structure for I2C TM.
    
    /************************************************************************************
     * USB COM variables declaration :
     * ------------------------------
     */
    unsigned short      menu_number     = 0xfffe;//Bad menu number.
    unsigned short      f_data_sending  = 0;//Flag for write USB COM and main loop.
    /***********************************************************************************/
    
    Nop();
    
    
    //pin_init();
    //oscillator_init();
    
    // initialize the device
    SYSTEM_Initialize();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    i2c_master_init();
    
    
    //printf("hello");
    
    //tm_address  = 0xff;//Mauvaise adresse pour pas rentrer dans if TM.
    tx_address  = TX_CONFIG_BITS;
    
    /*
     * Write a 16-bit data on the slave LiPo charger :
     * ----------------------------------------------
     * data = 0x0100    : Suspend battery charger operation.
     * data = 0x0000    : Start new battery charge cycle.
     */
    //i2c_master_start_write_data(tx_address,0x0100,&flag_i2c_end_writing);
    
//    led_red = on;
//    wait(1000000);
//    led_red = off;
    
    while (1){
        if(menu_number == 0xffff){
            write_usb_com("\r\nMenu : \r\n",&f_data_sending);//Bug si M collé,ancienne data??
        }
        
        read_usb_com(&menu_number);
        
        /************************************************************
         * If data USB COM is sending with "write_usb_com()", 
         * bad menu_number to not display the menu.
         */
        if(f_data_sending == 1){
            menu_number     = 0xfffe;
            f_data_sending  = 0;//Reset flag.
        }
        /***********************************************************/
        
        CDCTxService();
        
        
        /********************************************************************************
         * Prepare TM address for function "i2c_master_start_read_tm(...)" :
         * ----------------------------------------------------------------
         */
//        if(flag_i2c_data_ready == 0 && tm_address == 0){//!! Enlever tm_address=0 dans le futur!!
        if(flag_i2c_data_ready == 0){
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
        if(flag_i2c_data_ready == 1){
            i2c_tm_analog = i2c_master_get_tm(tm_address);//Analog value of the TM.
            
            if(counter_while == 0)//TM_VIN.
            {
                i2c_slave_v_in = i2c_tm_analog.data_1;
                led_red     = on;
                led_green   = off;
            }
            else if(counter_while == 1){//TM_CHARGER_STATE.
                i2c_slave_charger_suspended     = i2c_tm_analog.data_1;
                i2c_slave_precharge             = i2c_tm_analog.data_2;
                i2c_slave_cc_cv_charge          = i2c_tm_analog.data_3;
                i2c_slave_bat_missing           = i2c_tm_analog.data_4;
                i2c_slave_bat_short             = i2c_tm_analog.data_5;
                
                counter_while = -1;//-1 + 1 = 0 : Trick for new loop while and TM cycle.
                
                led_red     = off;
                led_green   = on;
            }
            
            tm_address = 0;//Reset address.
            flag_i2c_data_ready = 0;//Reset main flag.
            //counter_while++;
            
            wait(500000);
            
//            //!!! A retirer !!!
//            if(counter_while >= 1)
//            {
//                tm_address = 0xff;//Lancer une seule fois les 2 TM.
//            }
        }
        //*******************************************************************************
        
        
//        wait(1000000);
//        led_red = !led_red;
        
        /*************************************************************************************
         * I2C write data from Master to slave LiPo charger :
         * -------------------------------------------------
         */
        if(flag_i2c_end_writing != 0){
            if(flag_i2c_end_writing == 1){
                if(counter_while == 0){
                    led_blue    = on;
                    i2c_master_start_write_data(tx_address,0x0100,&flag_i2c_end_writing);
                }
                else if (counter_while == 1){
                    led_blue    = off;
                    led_green   = on;
                    i2c_master_start_write_data(tx_address,0x0000,&flag_i2c_end_writing);
                }   
                counter_while++;
            flag_i2c_end_writing = 0;//Reset flag.
            }
            Nop();
            Nop();
        }
        //************************************************************************************
        
         
        
    }
    
    return 0;
}
