/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 07/04/2020.   
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
    unsigned short      f_data_sending_1    = 0;
    char                t_data_i2c[64]      = "";//!!! Changer taille car 16 bits max !!!
    char                t_i2c_time[7]       = "";
    char                t_i2c_vbat[7]       = "";
    char                t_i2c_ibat[7]       = "";
    char                t_i2c_vbat_time[7]  = "";
    char                t_i2c_ibat_time[7]  = "";
    char                t_i2c_state[9]      = "";
    char                t_i2c_status[20]    = "";//"CC on \n\r" ou "CC/CV error \n\r.
    char                t_data_usb_com[250] = "";
    char                t_data[4]           = "";
    char                t_menu[255]         = "";
    /***********************************************************************************/
    
    /************************************************************************************
     * Master I2C 1 variables declaration :
     * ----------------------------------- 
     */
    unsigned short      tm_address              = 0;
    unsigned short      flag_i2c_data_ready     = 0;//"0" = Data i2c not ready.
    unsigned short      i2c_num_data_decoded    = 0;//Number of i2c data decoded.
    unsigned short      f_i2c_end_writing       = 0;//"0"=not ending,"1"=ending.
    unsigned short      f_start_stop_charge     = 0;//"0"=stop, "1"=start.
    unsigned short      i_tm                    = 0;
    float               i2c_tm_analog_data      = 0;
    I2c_tm_analog       s_i2c_tm_analog;//Structure for I2C TM.
    /***********************************************************************************/
    
    /************************************************************************************
     * Main variables declaration :
     * ---------------------------- 
     */
    //According to the value of the flag,we send minimum or maximum
    //TM informations over the USB virtual COM bus.
    //"0" = terminal COM, "1" = Qt interface.
    unsigned short      f_type_interface    = 0;
    bool                rtcc_status         = false;
    unsigned long       seconds_main        = 0;
    Date_time           str_data_time;
    /***********************************************************************************/
    
    
//    unsigned short i_1      = 0;
//    char t_vbat[]           = "bonjour_ABCD";
//    unsigned short size_t1  = 0;
//    
//    size_t1 = sizeof(t_vbat);
//    
//    strcpy(t_i2c_vbat_time,"54321");
//    strcpy(t_i2c_ibat,"-1.234");
//    strcpy(t_i2c_ibat_time,"12345");
//    strcpy(t_i2c_state,"on;off");
//    strcpy(t_i2c_status,"CC/CV ERROR");
//        
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_vbat,
//                              sizeof(t_vbat),&i_1);
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_vbat_time,
//                  sizeof(t_i2c_vbat_time),&i_1);
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_ibat,
//                  sizeof(t_i2c_ibat),&i_1);
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_ibat_time,
//                  sizeof(t_i2c_ibat_time),&i_1);
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_state,
//                  sizeof(t_i2c_state),&i_1);
//    table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_status,
//                  sizeof(t_i2c_status),&i_1);
//    
//    Nop();
    
    
    // initialize the device
    SYSTEM_Initialize();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    //Set Real-Time Clock and Calendar.
    //Useful for time sample of TM LiPo charger.
    set_RTCC_data_time(20,3,31,2,15,40,0);//Year,month,day,weekday,hour,min,sec.
        
    //Plugger l'USB pour démarrer le code.
    while(USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended()== true){};
    led_red     = on;
    
    
    //Stop the charge battery at the beginning of the code :
    //f_i2c_end_writing encore utile???
    i2c_master_start_write_data(TX_CONFIG_BITS,0x0100,&f_i2c_end_writing);
    write_usb_com("PIC24FJ128GC006 USB virtual COMx \r\n"
                  "STOP charge battery \r\n",&f_data_sending);

    while (1)
    {   
        read_usb_com(&menu_number);
        
        CDCTxService();
        
        empty_table(t_data_i2c,sizeof(t_data_i2c));
        empty_table(t_i2c_time,sizeof(t_i2c_time));
        empty_table(t_data_usb_com,sizeof(t_data_usb_com));
        
        //Reset variable :
        i2c_tm_analog_data  = 0;
        
        //!!! For debug !!!
        //flag_i2c_data_ready = 1;
        
        if(menu_number == 0){
            if(f_data_sending == 0 && f_data_sending_1 == 0){
                get_menu(1,t_menu,sizeof(t_menu));
                write_usb_com(t_menu,&f_data_sending_1);
            }
            else if(f_data_sending_1 == 1){
                char t_menu_2[255] = "";//Améliorer le code pour enlever variable !!!
                get_menu(2,t_menu_2,sizeof(t_menu_2));
                write_usb_com(t_menu_2,&f_data_sending);
                if(f_data_sending == 1){
                    f_data_sending_1    = 0;//Reset flag.
                }
            }
        }
        else if(menu_number == 1){
            //get_i2c_tm_and_send_to_usb(TM_VIN,"1 : Vin =","V",&f_data_sending);
            
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_VIN,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_VIN);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);
                //float_to_ascii(s_i2c_tm_analog.sample_time,t_i2c_time);
                float_to_ascii(76543,t_i2c_time);
                //strcpy(t_i2c_time,"20 s");
                
                if(f_type_interface == 0){//Terminal COM.
                    //Prepare data COM with string copy and concatenation :            
                    strcpy(t_data_usb_com,"1 : Vin = ");
                    strcat(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com," V \r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                else{//Qt interface.
                    strcpy(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com,";");
                    strcat(t_data_usb_com,t_i2c_time);
                    strcat(t_data_usb_com,"\r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 2){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_DIE_TEMP,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_DIE_TEMP);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com,"2 : Temp Die = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," deg C \r\n");
            
                write_usb_com(t_data_usb_com,&f_data_sending);
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 3){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_VBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_VBAT);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);
                float_to_ascii(s_i2c_tm_analog.sample_time,t_i2c_time);
                
                if(f_type_interface == 0){//Terminal COM.
                    //Prepare data COM with string copy and concatenation :            
                    strcpy(t_data_usb_com,"3 : Vbat = ");
                    strcat(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com," V \r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                else{//Qt interface.
                    strcpy(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com,";");
                    strcat(t_data_usb_com,t_i2c_time);
                    strcat(t_data_usb_com,"\r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 4){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_IBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_IBAT);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);
                float_to_ascii(s_i2c_tm_analog.sample_time,t_i2c_time);
                
                if(f_type_interface == 0){//Terminal COM.
                    //Prepare data COM with string copy and concatenation :            
                    strcpy(t_data_usb_com,"4 : Ibat = ");
                    strcat(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com," A \r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                else{//Qt interface.
                    strcpy(t_data_usb_com,t_data_i2c);
                    strcat(t_data_usb_com,";");
                    strcat(t_data_usb_com,t_i2c_time);
                    strcat(t_data_usb_com,"\r\n");
                    write_usb_com(t_data_usb_com,&f_data_sending);
                }
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 5){
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_CHARGER_STATE,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_CHARGER_STATE);
                
                //Bug si on utilise "t_data_usb_com",pq??
                //N'affiche pas la fin du tableau char...
                char t_data_usb_com_1[250] = "";
                
                strcpy(t_data_usb_com_1,"5 : STATE ; ");
                
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
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 6){//TM_CHARGE_STATUS.
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_CHARGE_STATUS,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_CHARGE_STATUS);
                
                char t_data_usb_com_1[250] = "";
                
                strcpy(t_data_usb_com_1,"6 : TM_CHARGE_STATUS -> ");
                                
                if(s_i2c_tm_analog.data_3 == 0){//OFF.
                    strcat(t_data_usb_com_1,"CC with ICHARGE_DAC : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"CC with ICHARGE_DAC : on ; ");
                }
                if(s_i2c_tm_analog.data_4 == 0){//OFF.
                    strcat(t_data_usb_com_1,"CV with VCHARGE_DAC : off \r\n");
                }
                else{
                    strcat(t_data_usb_com_1,"CV with VCHARGE_DAC : on \r\n");
                }
            
                write_usb_com(t_data_usb_com_1,&f_data_sending);
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 7){//TM_SYSTEM_STATUS.
            if(flag_i2c_data_ready == 0){
                i2c_master_start_read_tm(TM_SYSTEM_STATUS,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_SYSTEM_STATUS);
                
                char t_data_usb_com_1[250] = "";
                
                strcpy(t_data_usb_com_1,"7 : TM_SYSTEM_STATUS -> ");
                                
                if(s_i2c_tm_analog.data_1 == 0){//OFF.
                    strcat(t_data_usb_com_1,"charger_enabled : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"charger_enabled : on ; ");
                }
                if(s_i2c_tm_analog.data_2 == 0){//OFF.
                    strcat(t_data_usb_com_1,"ok_to_charge : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"ok_to_charge : on ; ");
                }
                if(s_i2c_tm_analog.data_3 == 0){//OFF.
                    strcat(t_data_usb_com_1,"thermal_shutdown : off ; ");
                }
                else{
                    strcat(t_data_usb_com_1,"thermal_shutdown : on ; ");
                }
                if(s_i2c_tm_analog.data_4 == 0){//OFF.
                    strcat(t_data_usb_com_1,"Vin > Vbat : off \r\n");
                }
                else{
                    strcat(t_data_usb_com_1,"Vin > Vbat : on \r\n");
                }
            
                write_usb_com(t_data_usb_com_1,&f_data_sending);
                
                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
                }
            }
        }
        else if(menu_number == 8){//TM_I_CHARGE_DAC and TM_V_CHARGE_DAC.
            if(flag_i2c_data_ready == 0){
                if(i_tm == 0){
                    i2c_master_start_read_tm(TM_I_CHARGE_DAC,&flag_i2c_data_ready);
                    tm_address = TM_I_CHARGE_DAC;
                    //strcpy(t_data," A \r\n");
                    i_tm++;//1.
                }
                else if(i_tm == 2){
                    i2c_master_start_read_tm(TM_V_CHARGE_DAC,&flag_i2c_data_ready);
                    tm_address = TM_V_CHARGE_DAC;
                    //strcpy(t_data," V \r\n");
                    i_tm++;//3.
                }
            }
            else if(flag_i2c_data_ready == 1){//Data is ready.
                //flag_i2c_data_ready = 0;//Reset flag.
                s_i2c_tm_analog     = i2c_master_get_tm(tm_address);
                float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);
                
                //Prepare data COM with string copy and concatenation :            
                strcpy(t_data_usb_com,"8 : data = ");
                strcat(t_data_usb_com,t_data_i2c);
                strcat(t_data_usb_com," A or V \r\n");
                //strcat(t_data_usb_com,t_data);
                
                if(i_tm == 1){
                    if(f_data_sending_1 == 0){
                        write_usb_com(t_data_usb_com,&f_data_sending_1);//Fake flag to keep menu 8.
                    }
                    else if(f_data_sending_1 == 1){
                        flag_i2c_data_ready = 0;//Reset flag.
                        //empty_table(t_data,sizeof(t_data));
                        i_tm++;//2.
                    }
                }
                else if(i_tm == 3){
                    write_usb_com(t_data_usb_com,&f_data_sending);//Real flag to loose menu 8.
                    i_tm = 0;//Reset for next 2 TM.
                    f_data_sending_1 = 0;//Reset.
                    flag_i2c_data_ready = 0;//Reset flag utilie ???
                }
            }
        }
        else if(menu_number == 9){//9  : V/I,times,status
            //--------------------------------------------------------------------------------
            //TM I2C Vbat and decoding :
            if(flag_i2c_data_ready == 0 && i2c_num_data_decoded == 0){
                i2c_master_start_read_tm(TM_VBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1 && i2c_num_data_decoded == 0){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_VBAT);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_i2c_vbat);
                float_to_ascii(s_i2c_tm_analog.sample_time,t_i2c_vbat_time);
                
                i2c_num_data_decoded    = 1;
                flag_i2c_data_ready     = 0;//Reset flag for next TM.     
            }
            //--------------------------------------------------------------------------------
            
            //--------------------------------------------------------------------------------
            //TM I2C Ibat and decoding :
            else if(flag_i2c_data_ready == 0 && i2c_num_data_decoded == 1){
                i2c_master_start_read_tm(TM_IBAT,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1 && i2c_num_data_decoded == 1){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_IBAT);
                
                float_to_ascii(s_i2c_tm_analog.data_1,t_i2c_ibat);
                float_to_ascii(s_i2c_tm_analog.sample_time,t_i2c_ibat_time);
                
                i2c_num_data_decoded    = 2;
                flag_i2c_data_ready     = 0;//Reset flag for next TM.
            }
            //--------------------------------------------------------------------------------
            
            //--------------------------------------------------------------------------------
            //TM state :
            else if(flag_i2c_data_ready == 0 && i2c_num_data_decoded == 2){
                i2c_master_start_read_tm(TM_CHARGER_STATE,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1 && i2c_num_data_decoded == 2){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_CHARGER_STATE);
                                
                //Charge suspended on/off.
                if(s_i2c_tm_analog.data_1 == 0){//OFF.
                    strcpy(t_i2c_state,"off;");
                }
                else{
                    strcpy(t_i2c_state,"on;");
                }
                //Precharge on/off.
                if(s_i2c_tm_analog.data_2 == 0){//OFF.
                    strcat(t_i2c_state,"off;");
                }
                else{
                    strcat(t_i2c_state,"on;");
                }
                
                i2c_num_data_decoded    = 3;
                flag_i2c_data_ready     = 0;//Reset flag for next TM.
            }
            //--------------------------------------------------------------------------------
            
            //--------------------------------------------------------------------------------
            //TM status :
            else if(flag_i2c_data_ready == 0 && i2c_num_data_decoded == 3){
                i2c_master_start_read_tm(TM_CHARGE_STATUS,&flag_i2c_data_ready);
            }
            else if(flag_i2c_data_ready == 1 && i2c_num_data_decoded == 3){//Data is ready.
                s_i2c_tm_analog     = i2c_master_get_tm(TM_CHARGE_STATUS);
                                                
                if(s_i2c_tm_analog.data_3 == 1){//CC with ICHARGE_DAC ON.
                    strcpy(t_i2c_status,"CC on");
                }
                else if(s_i2c_tm_analog.data_4 == 1){//CV with VCHARGE_DAC ON.
                    strcpy(t_i2c_status,"CV on");
                }
                else{
                    strcpy(t_i2c_status,"CC/CV error");
                    led_red     = off;
                    led_blue    = off;
                    led_green   =  on;
                }
                
                i2c_num_data_decoded    = 4;
            }
            //--------------------------------------------------------------------------------
            
            //--------------------------------------------------------------------------------
            //Prepare data to send on USB :
            if(flag_i2c_data_ready == 1 && i2c_num_data_decoded == 4){
                
                unsigned short i_1          = 0;//For table_concatenation().
                
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_vbat,
                              sizeof(t_i2c_vbat),&i_1);
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_vbat_time,
                              sizeof(t_i2c_vbat_time),&i_1);
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_ibat,
                              sizeof(t_i2c_ibat),&i_1);
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_ibat_time,
                              sizeof(t_i2c_ibat_time),&i_1);
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_state,
                              sizeof(t_i2c_state),&i_1);
                table_concatenation(t_data_usb_com,sizeof(t_data_usb_com),t_i2c_status,
                              sizeof(t_i2c_status),&i_1);
                
//                i_1--;//Retirer le dernier ';'.
//                t_data_usb_com[i_1] = '\0';
                
//                i_1--;
//                t_data_usb_com[i_1] = '\r';
//                i_1++;
//                t_data_usb_com[i_1] = '\n';
                                
                write_usb_com(t_data_usb_com,&f_data_sending);

                if(f_data_sending == 1){//"1" if USB ready.
                    flag_i2c_data_ready     = 0;//Reset flag after USB ready to send.
                    i2c_num_data_decoded    = 0;//Reset data number for next turn.
                    
                    empty_table(t_i2c_vbat,sizeof(t_i2c_vbat));
                    empty_table(t_i2c_vbat_time,sizeof(t_i2c_vbat_time));
                    empty_table(t_i2c_ibat,sizeof(t_i2c_ibat));
                    empty_table(t_i2c_ibat_time,sizeof(t_i2c_ibat_time));
                    empty_table(t_i2c_state,sizeof(t_i2c_state));
                    empty_table(t_i2c_state,sizeof(t_i2c_status));
                }
            }
            //--------------------------------------------------------------------------------
        }
        else if(menu_number == 11){//11 : START/STOP charge.
            unsigned short tc_data      = 0x0100;//Stop charge.
            char menu_text[25]          = "";
            char menu_text_start[]      = "START charge battery \r\n";
            char menu_text_stop[]       = "STOP charge battery \r\n";
            
            if(f_start_stop_charge == 0){//stop to start.
                strcpy(menu_text,menu_text_start);
                tc_data                 = 0x0000;//Start charge.
                f_start_stop_charge     = 1;//Charge running.
            }
            else{//start to stop.
                strcpy(menu_text,menu_text_stop);
                tc_data                 = 0x0100;//Stop charge.
                f_start_stop_charge     = 0;//Charge stopped.
            }
            
            strcpy(t_data_usb_com,menu_text);
            write_usb_com(t_data_usb_com,&f_data_sending);
            
            unsigned short flag_i2c_end_writing = 1;
            i2c_master_start_write_data(TX_CONFIG_BITS,tc_data,&flag_i2c_end_writing);
        }
        else if(menu_number == 20){//Choose Qt interface.
            if(f_type_interface == 0){
                f_type_interface = 1;
                strcpy(t_data_usb_com,"Qt interface ON \r\n");
            }
            else{
                f_type_interface = 0;
                strcpy(t_data_usb_com,"Qt interface OFF \r\n");
            }
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

void get_menu(unsigned short menu_number, char *t_menu, unsigned short t_menu_size){
/*
 */ 
    empty_table(t_menu,t_menu_size);
    
    
    char t_menu_1[] =   "\n-----------------------------------\r\n"
                        "Menu : \r\n"
                        "-----\r\n"
                        "1  : Vin \r\n"
                        "2  : Die T \r\n"
                        "3  : Vbat \r\n"
                        "4  : Ibat \r\n"
                        "5  : State \r\n"
                        "6  : TM_CHARGE_STATUS \r\n"
                        "7  : TM_SYSTEM_STATUS \r\n"
                        "8  : TM_I/V_CHARGE_DAC \r\n";
    
    char t_menu_2[] =   "9  : V/I,times,status \r\n"
                        "11 : START/STOP charge \r\n"
                        "20 : Qt interface ON/OFF \r\n"
                        "-----------------------------------\r\n";
    
    
    if(menu_number == 1){
        strcpy(t_menu,t_menu_1);
    }
    else if(menu_number == 2){
        strcpy(t_menu,t_menu_2);
        
//        //A tester pour amélioration problème double char dans main.
//        unsigned short i;
//        for(i=0; i < sizeof(t_menu_2 ) ; i++){
//            t_menu[i] = t_menu_2[i];
//        } 
//        i = i + 1;
//        for(;i < t_menu_size ; i++){
//            t_menu[i] = '\0';
//        }
    }
    else{//Menu n°1 by default.
        strcpy(t_menu,t_menu_1);
    }
}
//__________________________________________________________________________________________________

void random_i2c_data(unsigned short type_data,I2C_x_y_data *s_i2c_x_y){
/*
 */ 
    static float coeff = 0.1;
    
    if(type_data == TM_VBAT){
        if(s_i2c_x_y->x >= 4.5){
            coeff = -0.1;
        }
        else if(s_i2c_x_y->x <= 2.5){
            coeff = 0.1;
        }
        s_i2c_x_y->x = s_i2c_x_y->x + coeff;
    }
    else if(type_data == TM_IBAT){
        
    }
    else{
       s_i2c_x_y->x = 0.0;
       s_i2c_x_y->y = 0.0;
    }
    
    s_i2c_x_y->y = s_i2c_x_y->y + 1;//+1s.
    if(s_i2c_x_y->y > 3600){
        s_i2c_x_y->y = 0;
    }
}
//__________________________________________________________________________________________________

void table_concatenation(char *t_final,unsigned short t_final_size,char *t_new,
                            unsigned short t_new_size,unsigned short *i_t_final){
/* Concatenation of 2 tables char.
 * If the final table is not empty, add a ';' separator between data.
 */
    unsigned short i_1  = 0;//Index for final table.
    unsigned short i_2  = 0;//Index for new table to add.
        
    i_1 = *i_t_final;
    
    //Add data separator if table not empty :
    if(i_1 > 0){
        t_final[i_1] = ';';
        i_1++;//Go to next index.
    }
    
    //Add char in final table if char is not '\0' :
    for(i_2 = 0; i_2 <  t_new_size ; i_2++){
        if(t_new[i_2] != '\0'){
            t_final[i_1] = t_new[i_2];
            //Security to not exceed size max of t_final.
            if((i_1+1) < t_final_size){
                i_1++;
            }
        }
    }
    
    *i_t_final = i_1;
}
//__________________________________________________________________________________________________

/**
 End of File
*/

