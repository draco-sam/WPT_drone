/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 19/02/2020.   
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
    
//    //Testing :
//    unsigned short size_sam = 0;
//    char test_sam[250] = "";
//    strcpy(test_sam,"1234567891234567891234567891234567891234567891234 \r\n");
//    strcat(test_sam,"1234567891234567891234567891234567891234567891234 \r\n");
//    strcat(test_sam,"1234567891234567891234567891234567891234567891234 \r\n");
//    strcat(test_sam,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTSamm \r\n");
//    size_sam = strlen(test_sam);
//    write_usb_com(test_sam,&f_data_sending);

    while (1)
    {   
        read_usb_com(&menu_number);
        
        CDCTxService();
        
        empty_table(t_data_i2c,sizeof(t_data_i2c));
        empty_table(t_data_usb_com,sizeof(t_data_usb_com));
        
        i2c_tm_analog_data = 0;//Reset variable.
        
        if(menu_number == 0){
            //!!! Trop long pour "strcpy()", pq ???
            char test_menu[250] =   "\n---------------\r\n"
                                    "Menu : \r\n"
                                    "-----\r\n"
                                    "1 : Vin \r\n"
                                    "2 : Die T \r\n"
                                    "3 : Vbat \r\n"
                                    "4 : Ibat \r\n"
                                    "5 : State \r\n"
                                    "---------------\r\n";
            write_usb_com(test_menu,&f_data_sending);
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
                strcpy(t_data_usb_com,"1 : Vin = ");
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
                strcpy(t_data_usb_com,"2 : Temp Die = ");
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
                strcpy(t_data_usb_com,"3 : Vbat = ");
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
                strcpy(t_data_usb_com,"4 : Ibat = ");
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
                
                //Bug si on utilise "t_data_usb_com",pq??
                //N'affiche pas la fin du tableau char...
                char t_data_usb_com_1[250] = "";
                
                strcpy(t_data_usb_com_1,"5 : STATE -> ");
                
                if(s_i2c_tm_analog.data_1 == 0){//OFF.
                    strcat(t_data_usb_com_1,"ch susp : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"ch susp : on ; ");
                }
                if(s_i2c_tm_analog.data_2 == 0){//OFF.
                    strcat(t_data_usb_com_1,"prech : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"prech : on ; ");
                }
                if(s_i2c_tm_analog.data_3 == 0){//OFF.
                    strcat(t_data_usb_com_1,"cc_cv : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"cc_cv : on ; ");
                }
                if(s_i2c_tm_analog.data_4 == 0){//OFF.
                    strcat(t_data_usb_com_1,"bat_miss : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"bat_miss : on ; ");
                }
                if(s_i2c_tm_analog.data_5 == 0){//OFF.
                    strcat(t_data_usb_com_1,"bat_short : off \r\n");
                }
                else{
                    strcat(t_data_usb_com_1,"bat_short : on \r\n");
                }

                write_usb_com(t_data_usb_com_1,&f_data_sending);
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

