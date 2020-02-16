/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 13/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/


#include "01_lib_wpt_rx/lib_wpt_usb_i2c.h"

/*
                         Main application
 */
int main(void)
{
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1

    /************************************************************************************
     * USB COM variables declaration :
     * ------------------------------
     */
    unsigned short      menu_number         = 0xfffe;//Bad menu number.
    unsigned short      f_data_sending      = 0;//Flag for write USB COM and main loop.
    char                t_data_i2c[64]      = "";//!!! Changer taille car 16 bits max !!!
    char                t_data_usb_com[250] = "";
    /***********************************************************************************/
    
    /************************************************************************************
     * Master I2C 1 variables declaration :
     * ----------------------------------- 
     */
    unsigned short      tm_address              = 0;
    unsigned short      flag_i2c_data_ready     = 0;//"0" = Data i2c not ready.
    float               i2c_tm_analog_data      = 0;
    I2c_tm_analog       s_i2c_tm_analog;//Structure for I2C TM.
    /***********************************************************************************/
    
    
    // initialize the device
    SYSTEM_Initialize();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    

    
    //Plugger l'USB pour démarrer le code.
    while(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended()== true){};
    led_red     = on;
    led_green   = off;

    while (1)
    {   
        read_usb_com(&menu_number);
        
        CDCTxService();
        
        empty_table(t_data_i2c);
        empty_table(t_data_usb_com);
        
        i2c_tm_analog_data = 0;//Reset variable.
        
        if(menu_number == 0xffff){
            write_usb_com("\r\nMenu : \r\n",&f_data_sending);//Bug si M collé,ancienne data??
        }
        else if(menu_number == 1){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_VIN,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_VIN);
                i2c_tm_analog_data  = s_i2c_tm_analog.data_1;//Analog value of the TM.
                flag_i2c_data_ready = 0;//Reset flag.
                
                float_to_ascii(i2c_tm_analog_data,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com," : Vin = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," Vvvvvolts \r\n");
            
                write_usb_com(t_data_usb_com,&f_data_sending);
            }
        }
        else if(menu_number == 2){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_DIE_TEMP,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_DIE_TEMP);
                i2c_tm_analog_data  = s_i2c_tm_analog.data_1;//Analog value of the TM.
                flag_i2c_data_ready = 0;//Reset flag.
                
                float_to_ascii(i2c_tm_analog_data,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com," : Temp Die = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," deg C \r\n");
            
                write_usb_com(t_data_usb_com,&f_data_sending);
            }
        }
        else if(menu_number == 3){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_VBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_VBAT);
                i2c_tm_analog_data  = s_i2c_tm_analog.data_1;//Analog value of the TM.
                flag_i2c_data_ready = 0;//Reset flag.
                
                float_to_ascii(i2c_tm_analog_data,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com," : Vbat = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," V \r\n");
            
                write_usb_com(t_data_usb_com,&f_data_sending);
            }
        }
        else if(menu_number == 4){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_IBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_IBAT);
                i2c_tm_analog_data  = s_i2c_tm_analog.data_1;//Analog value of the TM.
                flag_i2c_data_ready = 0;//Reset flag.
                
                float_to_ascii(i2c_tm_analog_data,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com," : Ibat = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," A \r\n");
            
                write_usb_com(t_data_usb_com,&f_data_sending);
            }
        }
        else if(menu_number == 5){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_CHARGER_STATE,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                flag_i2c_data_ready = 0;//Reset flag.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_CHARGER_STATE);
                
                strcpy(t_data_usb_com," : STATE -> ");
                
                if(s_i2c_tm_analog.data_1 == 0){//OFF.
                    strcat(t_data_usb_com,"ch susp : off ; ");
                }
                else{
                    strcat(t_data_usb_com,"ch susp : on ; ");
                }
                if(s_i2c_tm_analog.data_2 == 0){//OFF.
                    strcat(t_data_usb_com,"prech : off ; ");
                }
                else{
                    strcat(t_data_usb_com,"prech : on ; ");
                }
                if(s_i2c_tm_analog.data_3 == 0){//OFF.
                    strcat(t_data_usb_com,"cc_cv : off ; ");
                }
                else{
                    strcat(t_data_usb_com,"cc_cv : on ; ");
                }
                if(s_i2c_tm_analog.data_4 == 0){//OFF.
                    strcat(t_data_usb_com,"bat_miss : off ; ");
                }
                else{
                    strcat(t_data_usb_com,"bat_miss : on ; ");
                }
                if(s_i2c_tm_analog.data_5 == 0){//OFF.
                    strcat(t_data_usb_com,"bat_short : off \r\n");
                }
                else{
                    strcat(t_data_usb_com,"bat_short : on \r\n");
                }

                write_usb_com(t_data_usb_com,&f_data_sending);
            }
        }
        else if(menu_number == 6){
            led_blue    = off;
            led_green   = off;
            led_red     = on;
            
            strcpy(t_data_usb_com," : Suspend battery \r\n ");
            write_usb_com(t_data_usb_com,&f_data_sending);
            
            unsigned short flag_i2c_end_writing = 1;
            i2c_master_start_write_data(TX_CONFIG_BITS,0x0100,&flag_i2c_end_writing);
        }
        else if(menu_number == 7){
            led_blue    = off;
            led_green   = off;
            led_red     = on;
            
            strcpy(t_data_usb_com," : Restart charge battery \r\n ");
            write_usb_com(t_data_usb_com,&f_data_sending);
            
            unsigned short flag_i2c_end_writing = 1;
            i2c_master_start_write_data(TX_CONFIG_BITS,0x0000,&flag_i2c_end_writing);
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
        
        
    }

    return 1;
}
/**
 End of File
*/

