/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 12/02/2020.   
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
    unsigned short      menu_number     = 0xfffe;//Bad menu number.
    unsigned short      f_data_sending  = 0;//Flag for write USB COM and main loop.
    char                t_data_i2c[64]  = "";//!!! Changer taille car 16 bits max !!!
    char                t_data_usb_com[64]  = "";
    char                t_data_1[64]    = "";
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
        if(menu_number == 0xffff){
            write_usb_com("\r\nMenu : \r\n",&f_data_sending);//Bug si M collé,ancienne data??
        }
        
        read_usb_com(&menu_number);
        
        CDCTxService();
        
        empty_table(t_data_i2c);
        empty_table(t_data_usb_com);
        empty_table(t_data_1);
        
        if(menu_number == 1){
            led_blue    = off;
            led_green   = off;
            led_red     = on;
            
            float_to_ascii(4.567,t_data_i2c);
            
            //Prepare data COM with string copy and concatenation :            
            strcpy(t_data_usb_com," : Vbat = ");
            strcpy(t_data_1," Vvvvvolts \r\n");
            strcat(t_data_usb_com,t_data_i2c);
            strcat(t_data_usb_com,t_data_1);
            
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
        
        
    }

    return 1;
}
/**
 End of File
*/

