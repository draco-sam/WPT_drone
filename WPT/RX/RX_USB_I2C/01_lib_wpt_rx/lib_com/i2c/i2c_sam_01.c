/*************************************************************************************************** 
 * File             : i2c_sam_01.c
 * Date             : 12/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "i2c_sam_01.h"

 #define led_red         LATGbits.LATG7
 #define led_green       LATGbits.LATG6
 #define led_blue        LATEbits.LATE7
 #define on              0
 #define off             1

static unsigned short   i2c_slave_add_write         = 0xd0;//Adresse 208 (0xd0) et bit 0 � "0".
static unsigned short   i2c_slave_add_read          = 0b11010001;//Adresse 104 et bit 0 � "1".
static int              i2c_data_l                  = 0;//Low 8-bit from 16-bit data.
static int              i2c_data_h                  = 0;//High 8-bit from 16-bit data.
static unsigned short   i2c_command                 = 0;
static unsigned short   i2c_interrupt_counter       = 0;
static unsigned short   i2c_flag_read               = 0;//Flag read off for interrupt.
static unsigned short   i2c_flag_write              = 0;//Flag write off for interrupt.
static unsigned short   *s_flag_data_ready          = NULL;
static unsigned short   *s_flag_end_writing         = NULL;

void i2c_master_init(void)
/*
 * 
 */
{
    // Baud Rate Generator Value.
    I2C1BRG = 157;//157 at 100 kHz (f_cy = 16 MHz, f_usb = 48 MHz).
    

    /***********************************************************************************************
     * I2C1CON : I2C 1 Control Register :
     * ---------------------------------     
     */
    I2C1CONbits.I2CEN       = 1;//Enables the I2Cx module, SDAx and SCLx pins as serial port pins.
    I2C1CONbits.I2CSIDL     = 0;//"0" : Continues module operation in Idle mode.
    I2C1CONbits.SCLREL      = 0;//"0" : Holds SCLx clock low (clock stretch).
    I2C1CONbits.IPMIEN      = 0;//IPMI Support mode is disabled.
    I2C1CONbits.A10M        = 0;//I2CxADD is a 7-bit Slave address.
    
    //Slew rate control is disabled for Standard Speed mode (100kHz, 1MHz).
    I2C1CONbits.DISSLW      = 0;//"0" : Enable (comme ex MPLAB...)
    
    I2C1CONbits.SMEN        = 1;//!!!0 : Disables SMBus-specific inputs.
    
    //Enables interrupt when a general call address is received in the I2CxRSR 
    //(module is enabled for reception)
    I2C1CONbits.GCEN        = 1;
    
    I2C1CONbits.STREN       = 0;//"0" : Disables clock stretching.
    I2C1CONbits.ACKDT       = 0;
    I2C1CONbits.ACKEN       = 0;//Acknowledge sequence is Idle.
    I2C1CONbits.RCEN        = 0;//Receive sequence is not in progress.
    I2C1CONbits.PEN         = 0;//Stop condition is Idle (inactif).
    I2C1CONbits.RSEN        = 0;//Restart condition is Idle.
    I2C1CONbits.SEN         = 0;//Start condition is Idle.
    //**********************************************************************************************
        
    I2C1STAT = 0;//Reset I2Cx STATUS REGISTER.
    
    /* MI2C1 - I2C1 Master Events */
    IFS1bits.MI2C1IF = 0;// clear the master interrupt flag.
    IEC1bits.MI2C1IE = 1;// enable the master interrupt.
}
//__________________________________________________________________________________________________

void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C1Interrupt ( void )
{
/*
 * 
 */  
    IEC1bits.MI2C1IE = 0;//disable the master interrupt.
    IFS1bits.MI2C1IF = 0;//Reset flag master I2C 1.
    
    i2c_interrupt_counter++;
    
    if(i2c_flag_read == 1){//Read value from slave :
        //1)Send slave address with a future write communication :
        if(i2c_interrupt_counter == 1)
        {
            I2C1TRN = i2c_slave_add_write;//Write address in buffeur out.
        }
        //2)Send a data command to the slave :
        else if(i2c_interrupt_counter == 2)
        {
            if(I2C1STATbits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
            {   
                I2C1TRN = i2c_command;//Command to the slave.
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        //3)Restart condition for future read communication :
        else if(i2c_interrupt_counter == 3)
        {
            if(I2C1STATbits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
            {
                I2C1CONbits.RSEN   = 1;//1 = Initiates Restart condition on SDAx and SCLx pins.
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        //4)Send the slave address with a future read communication :
        else if(i2c_interrupt_counter == 4)
        {
            I2C1TRN = i2c_slave_add_read;
        }
        //5)Master will send 8 clocks to receive the data byte from the slave :
        else if(i2c_interrupt_counter == 5)
        {
            if(I2C1STATbits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
            {
                //1 = Enables Receive mode for I2C.
                //Hardware is clear at the end of the 8th bit of the master receive data byte.
                I2C1CONbits.RCEN = 1;
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        /*
         * 6)Read the I2CxRCV receive buffer.
         * Prepare master to send a ACK to the slave.
         * Initiates Acknowledge sequence and transmit ACKDT bit (ACK) to the slave.
         */
        else if(i2c_interrupt_counter == 6)
        {
            if(I2C1STATbits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
            {
                i2c_data_l          = I2C1RCV;
                I2C1CONbits.ACKDT   = 0;//"0" : Sends ACK during Acknowledge.
                I2C1CONbits.ACKEN   = 1;
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        //7)Master sends ACK to slave. (??? v�rifier validit� data avant d'envoyer ACK ???)
        else if(i2c_interrupt_counter == 7)
        {
            if(I2C1STATbits.ACKSTAT == 0)//0 = Acknowledge was sent from master to slave.
            {
                //Hardware is clear at the end of the 8th bit of the master receive data byte.
                I2C1CONbits.RCEN = 1;//1 = Enables Receive mode for I2C.
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        //8)Read the 2th data on receive buffer and send a NACK to the slave :
        else if(i2c_interrupt_counter == 8)
        {   
            if(I2C1STATbits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
            {
                i2c_data_h = I2C1RCV;
                I2C1CONbits.ACKDT = 1;//1 = Sends NACK during Acknowledge.
                I2C1CONbits.ACKEN = 1;//Initiates ACK sequence,transmits the ACKDT bit to slave.
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        } 
        //9)Initiates Stop condition on SDAx and SCLx pins :
        //!!! V�rifier NACK status bit master envoy� vers slave pour commencer le stop???
        else if(i2c_interrupt_counter == 9 || i2c_interrupt_counter == 99)
        {
            I2C1CONbits.PEN    = 1; 
        }
        //10)Reset counter for next communication, SDAx and SCLx pins are at "1" :
        else if(i2c_interrupt_counter == 10 || i2c_interrupt_counter == 100)
        {
            //1 = Indicates that a Stop bit has been detected last.
            if(I2C1STATbits.P != 1 || i2c_interrupt_counter == 100)
            {
                 i2c_data_l = 0;//Bad data info !!!
                 i2c_data_h = 0;//Bad data info !!!
            }
            *s_flag_data_ready      = 1;//Rising flag data ready for the main.
            i2c_flag_read           = 0;//Reset flag for if interrupt.
            i2c_interrupt_counter   = 0;//Reset.  
        }
    }
    /*
     * Master writes a byte to the slave LiPo charger :
     * -----------------------------------------------
     */
    else if(i2c_flag_write == 1){
        //1)Send slave address with a future write communication :
        if(i2c_interrupt_counter == 1){
            I2C1TRN = i2c_slave_add_write;//Write address in buffeur out.
        }
        //2)Send a data command to the slave :
        else if(i2c_interrupt_counter == 2){
            if(I2C1STATbits.ACKSTAT == 0){//0 = Acknowledge was received from Slave
                I2C1TRN = i2c_command;//Address of one register on the slave.
            }
            else{
                i2c_interrupt_counter = 98;
            }
        }
        //3)If ACK, send data byte low :
        else if(i2c_interrupt_counter == 3){
            if(I2C1STATbits.ACKSTAT == 0){//0 = Acknowledge was received from Slave
                I2C1TRN = i2c_data_l;
            }
            else{
                i2c_interrupt_counter = 98;
            }
        }
        //4)If ACK, send data byte high :
        else if(i2c_interrupt_counter == 4){
            if(I2C1STATbits.ACKSTAT == 0){//0 = Acknowledge was received from Slave
                I2C1TRN = i2c_data_h;
            }
            else{
                i2c_interrupt_counter = 98;
            }
        }
        //5)Check if ACK has been sent from the slave for the reception of the byte high :
        else if(i2c_interrupt_counter == 5 || i2c_interrupt_counter == 99){
            if(I2C1STATbits.ACKSTAT != 0){//0 = Acknowledge was received from Slave
               *s_flag_end_writing = 2;//2 = bad code for main loop.
            }
            I2C1CONbits.PEN    = 1;
        }
        //6)Reset counter for next communication, SDAx and SCLx pins are at "1" :
        else if(i2c_interrupt_counter == 6 || i2c_interrupt_counter == 100){
            //1 = Indicates that a Stop bit has been detected last.
            if(I2C1STATbits.P != 1 || i2c_interrupt_counter == 100){
                 *s_flag_end_writing    = 3;//3 = bad code for main loop.
            }
            *s_flag_end_writing         = 1;//1 = end of writing ok for main loop.
            i2c_flag_write              = 0;//Reset flag for if interrupt.
            i2c_interrupt_counter       = 0;//Reset.  
        }
    }
    
    IEC1bits.MI2C1IE = 1;//Enable the master interrupt.
}
//__________________________________________________________________________________________________

void i2c_master_start_read_tm(unsigned short tm_address,unsigned short *f_data_ready){
/*
 * Start i2C master read telemetry from slave IC charger and save it on static variables.
 */
    if(I2C1STATbits.TRSTAT == 0)
    {
        //LATG = 0b01000000;
        i2c_flag_read   = 1;//Read ongoing, flag for interrupt.
        i2c_command     = tm_address;
        s_flag_data_ready   = f_data_ready;//Copier adresse du flag dans variable statique.
        *f_data_ready       = 2;//"2" = TM ongoing.
        
        I2C1CONbits.SEN   = 1;//Initiates Start condition on SDAx and SCLx pins.
    }
    
    //si non attendre ????    
}
//__________________________________________________________________________________________________

unsigned long get_i2c_sample_time(){
/* The time comes from RTCC (Real-Time Clock and Calendar) PIC.
 * 
 * 
 */ 
    #define         time_out_max        5000000
    Date_time       str_date_time;
    bool            rtcc_status = false;
    unsigned long   seconds     = 0;
    unsigned long   time_out    = 0;
    
    //While rtcc_status = false, run "RTCC_TimeGet()".
    //If time out, get out of the while.
    while(rtcc_status == false || time_out > time_out_max){
        rtcc_status = RTCC_TimeGet(&str_date_time);//Pass address of structure Date_time.
        seconds     = convertTimeToSeconds(str_date_time.tm_hour,str_date_time.tm_min,
                      str_date_time.tm_sec);
    }
    
    return seconds;
}
//__________________________________________________________________________________________________

I2c_tm_analog i2c_master_get_tm(unsigned short tm_address){
/*
 * I2C master get telemetry to main program .
 * The 16-bit data is decomposed into 2 bytes.
 */
    unsigned short  digital_data        = 0;
    short           digital_data_signed = 0;
    I2c_tm_analog   i2c_tm_analog;
    
    //Reset value :
    i2c_tm_analog.sample_time   = 0.0;
    i2c_tm_analog.data_1        = 0.0;
    i2c_tm_analog.data_2        = 0.0;
    i2c_tm_analog.data_3        = 0.0;
    i2c_tm_analog.data_4        = 0.0;
    i2c_tm_analog.data_5        = 0.0;
    
    //get sample time in seconds (RTCC [s] : hour + min + sec).
    i2c_tm_analog.sample_time = get_i2c_sample_time();//Return a long !!!
    
    digital_data        = i2c_data_h << 8;//High 8-bit of data 16-bit.
    digital_data        = digital_data | i2c_data_l;//Low 8-bit add on final data 16-bit.
    
    digital_data_signed = digital_data;//Copy for signed calculations.
    
    if(tm_address == TM_VBAT){
        //!!! Lancer d'abord TM "TM_CHEM_CELLS" pour connaitre la valeur de "CELL_COUNT" !!!
        i2c_tm_analog.data_1 = digital_data * 192.264e-6 * CELL_COUNT;//192.264 �V.
    }
    else if(tm_address == TM_VIN || tm_address == TM_VSYS){
        i2c_tm_analog.data_1 = digital_data * 0.001648;//LSB = 1.648 mV.
    }
    else if(tm_address == TM_IBAT){
        if(digital_data >= 32768){//Negative ibat.
            //2^16 = 65536 and 32768 is the most negative value.
            digital_data_signed = digital_data - 65536;
        }
        i2c_tm_analog.data_1 = (digital_data_signed * 1.46487e-6)/R_SENS_BATTERY;
        Nop();
    }
    else if(tm_address == TM_I_IN){
        i2c_tm_analog.data_1 = (digital_data * 1.46487e-6)/R_SENS_IN;
    }
    else if(tm_address == TM_DIE_TEMP){
        i2c_tm_analog.data_1 = (digital_data - 12010)/45.6;//45.6 �C.
    }
    //R_NTC = (digital_data * R_NTC_BIAS)/(21845 - digital_data);
    //digital_data = NTC_RATIO (datasheet p21/76).
    //The digital value is sent to the PC. Qt code decoded this value to determine the T�.
    else if(tm_address == TM_NTC_RATIO){
        i2c_tm_analog.data_1 = digital_data;
    }
    else if (tm_address == TM_CHEM_CELLS){
        i2c_tm_analog.data_1 = 0.0;//!!! A coder !!!
        i2c_tm_analog.data_2 = digital_data && 0x0F;//bits 3:0 = 4 bits for number of cells.
    }
    else if (tm_address == TM_CHARGER_STATE){
        /*
         * CHARGER_STATE :
         * --------------
         * Sub-address      : 0x34.
         * R/W              : Read.
         * Number of bit    : 16 bits (15:0).
         * 
         * bit at "1"       : state bit = ON.
         * bit at "0"       : state bit = OFF.
         * 
         * Comment          : Not all bits are stored on the structure "i2c_tm_analog".
         */
        
        i2c_tm_analog.data_1 = ((digital_data & 0x100) >> 8);//bit 8  : charger_suspended.
        i2c_tm_analog.data_2 = ((digital_data & 0x80) >> 7);//bit 7   : precharge.
        i2c_tm_analog.data_3 = ((digital_data & 0x40) >> 6);//bit 6   : cc_cv_charge.
        i2c_tm_analog.data_4 = ((digital_data & 0x02) >> 1);//bit 1   : bat_missing_fault.
        i2c_tm_analog.data_5 = digital_data & 0x01;//bit 0   : bat_short_fault.
    }
    else if(tm_address == TM_I_CHARGE_DAC){
        i2c_tm_analog.data_1 = ((digital_data + 1) * 1e-3) / R_SENS_BATTERY;
    }
    else if(tm_address == TM_V_CHARGE_DAC){//PAS de loi de conversion ???
        i2c_tm_analog.data_1 = digital_data;
    }
    else if(tm_address == TM_TC_ICHARGE_TARGET){//0x1a, 5-bit [4:0].
        i2c_tm_analog.data_1 = ((digital_data & 0x1f) + 1) * (1e-3 / R_SENS_BATTERY);
    }
    else if(tm_address == TM_VCHARGE_SETTING){//0x1a, 5-bit [4:0].
        i2c_tm_analog.data_1 = (((digital_data & 0x1f)/80.0) + 3.8125) * CELL_COUNT ;
    }
    else if(tm_address == TM_CHARGE_STATUS){//0x35, 4-bit [3:0].
        i2c_tm_analog.data_1 = (digital_data & 0x08) >> 3;//vin_uvcl_active.
        i2c_tm_analog.data_2 = (digital_data & 0x04) >> 2;//iin_limit_active.
        i2c_tm_analog.data_3 = (digital_data & 0x02) >> 1;//constant_current based on CHARGE_DAC.
        i2c_tm_analog.data_4 = (digital_data & 0x01);//constant_voltage based on VCHARGE_DAC.
    }
    else if(tm_address == TM_SYSTEM_STATUS){//0x39, 14-bit [13:0].
        /*
         * bit at "1"       : state bit = ON ???
         * bit at "0"       : state bit = OFF ???
         */
        i2c_tm_analog.data_1 = (digital_data & 0x2000)  >> 13;//Bit 13 : charger_enabled.
        i2c_tm_analog.data_2 = (digital_data & 0x40)    >> 6;//Bit 6 : ok_to_charge.
        i2c_tm_analog.data_3 = (digital_data & 0x10)    >> 4;//Bit 4 : thermal_shutdown (160 �C).
        i2c_tm_analog.data_4 = (digital_data & 0x04)    >> 2;//Bit 2 : vin_gt_vbat.
    }
    else if(tm_address == TM_MAX_CHARGE_TIMER){
        /*
        * MAX_CHARGE_TIMER (Sub-Address 0x30, Bits 15:0, R) :
        * --------------------------------------------------
        * The MAX_CHARGE_TIMER starts with the battery charger soft-start after battery detection.
        * If the total time charging the battery exceeds MAX_CHARGE_TIME, the charger will enter the
        * MAX_CHARGE_TIME FAULT state and cease charging.
        * 
        * The MAX_CHARGE_TIME fault state can also be exited with SUSPEND_CHARGER is written to a 1.
        */
        i2c_tm_analog.data_1 = digital_data;//Time in [s].
    }
    else if(tm_address == TM_CV_TIMER){//CV_TIMER (Sub-Address 0x31, Bits 10:0, R).
        i2c_tm_analog.data_1 = digital_data;//Time in [s]. 16 or 10 bits???
    }
    
    
    
    //Clear variables for next TM.
    i2c_data_h  = 0;
    i2c_data_l  = 0;

    return i2c_tm_analog;
}
//__________________________________________________________________________________________________

void i2c_master_start_write_data(   unsigned short tx_address,unsigned short data,
                                    unsigned short *f_end_writing){
/*
 * Start i2C master write command from slave IC charger.
 */
    s_flag_end_writing      = f_end_writing;//Copy the address of the flag on static variable.
    
    //Check if Master transmit is not in progress ("0") :
    if(I2C1STATbits.TRSTAT == 0){
        i2c_flag_write      = 1;//Write ongoing, flag for interrupt.
        i2c_command         = tx_address;
        
        i2c_data_l          = data & 0x00ff;
        i2c_data_h          = data >> 8;
        
        I2C1CONbits.SEN     = 1;//Initiates Start condition on SDAx and SCLx pins.
    }
}
//__________________________________________________________________________________________________

void get_i2c_tm_and_send_to_usb(unsigned short TM_ADDRESS,char *text_1,char *text_2,
                                unsigned short *flag_sending){
/*
 * 
 */
    static unsigned short   flag_i2c_data_ready     = 0;//"0" = Data i2c not ready.
    char                    t_data_usb_com_11[64]   = "";
    char                    t_data_i2c[32]          = "";//!!! Changer taille car 16 bits max !!!
    I2c_tm_analog           s_i2c_tm_analog;//Structure for I2C TM.
    
    if(flag_i2c_data_ready == 0){
        i2c_master_start_read_tm(TM_VIN,&flag_i2c_data_ready);
    }
    else if(flag_i2c_data_ready == 1){//Data is ready.
        s_i2c_tm_analog     = i2c_master_get_tm(TM_VIN);

        float_to_ascii(s_i2c_tm_analog.data_1,t_data_i2c);

        //Prepare data COM with string copy and concatenation :            
//        strcpy(t_data_usb_com_11,"1 : Vin = ");
//        strcat(t_data_usb_com,t_data_i2c);
//        strcat(t_data_usb_com_11," Vvvvvolts \r\n");
        
        char t_1[] = "1 : Vin = ";

        write_usb_com(t_1,flag_sending);
        //write_usb_com("1 : Vin = ...",flag_sending);

        if(*flag_sending == 1){//"1" if USB ready.
            flag_i2c_data_ready = 0;//Reset flag after USB ready to send.
        }
    }
}
//__________________________________________________________________________________________________

void float_to_ascii(float data_float,char *t_table){
/*
 * data max : 65535.
 * 
 * !!! Modier code partie d�cimale pour ressembler � celui partie enti�re !!!
 */
    //short           data_integer        = 0;
    long            data_integer        = 0;
    //unsigned short  abs_data_integer    = 0;
    unsigned long   abs_data_integer    = 0;
    unsigned short  abs_data_decimal    = 0;
    unsigned short  i                   = 0;
    unsigned short  i_t                 = 0;
    unsigned short  f_zero              = 1;
    unsigned long   d_temp              = 0;
    unsigned long   d_div               = 10000;
    short           data_decimal        = 0;
    unsigned short  data_1              = 0;
    unsigned short  data_2              = 0;
    char            table_ascii[11]     = {'0','1','2','3','4','5','6','7','8','9'};
    char            t_integer[7]        = {0};//[7] : sign + 5 digits + \0.
    char            t_decimal[5]        = {0};
    
    extract_integer_decimal(data_float,&data_integer,&data_decimal);
    
    //Absolute value for searching numbers.
    //abs_data_integer = abs(data_integer);
    if(data_integer < 0){
        abs_data_integer = data_integer * -1;//(-10) * (-1) = +10.
    }
    else{
        abs_data_integer = data_integer;
    }
    abs_data_decimal = abs(data_decimal);
    
    if(data_integer != 0){
        //*****************************
        //Check de sign :
        if(data_integer > 0){
            t_table[0] = '+';
        }
        else{
            t_table[0] = '-';
        }
        //*****************************
        
        //*******************************************************************************
        //Construct the integer table and remove unnecessary "0" :
        for(i=0 ; i < 5 ; i++){
            d_temp = abs_data_integer / d_div;

            if(f_zero == 1){
                if(d_temp != 0){
                    f_zero = 0;
                }
            }
            if(f_zero == 0 && i_t < sizeof(t_integer)){
                t_integer[i_t] = table_ascii[d_temp];
                i_t++;//++ a chaque sauvegarde.
            }

            abs_data_integer = abs_data_integer - (d_temp * d_div);//5432.

            d_div = d_div / 10;//1000,100,10,1.
        }
        //*******************************************************************************
    }
    //*****************************************************
    //Check de sign of decimal part if integer = 0:
    else{
        t_integer[0] = '0';
        
        if(data_decimal >= 0){
            t_table[0] = '+';
        }
        else{
            t_table[0] = '-';
        }
    }
    //*****************************************************
    
    if(abs_data_decimal > 0){//Ex : 728 mA.
        t_decimal[4] = '\0';
        
        data_1 = 0;//Reset.
        data_2 = 0;//Reset.
        
        data_1          = abs_data_decimal / 10;                
        data_2          = data_1 * 10;                 
        t_decimal[3]    = table_ascii[abs_data_decimal - data_2];//8.  

        data_2          = (data_1 / 10) * 10;
        t_decimal[2]    = table_ascii[data_1 - data_2];
        data_1          = data_1 / 10;//2.
        
        t_decimal[1]    = table_ascii[data_1];//7.
        
        t_decimal[0]    = '.';
    }
    
    strcat(t_table,t_integer);
    strcat(t_table,t_decimal);
}
//__________________________________________________________________________________________________

void extract_integer_decimal(float data,long *data_integer,short *data_decimal){
/*
 * Extraire la partie enti�re et d�cimale d'un nombre float.
 * Ne fonctionne que jusque 10^-3.
 * 
 * Ex avec 248 mA :
 *      data_integer = 0.
 *      data_decimal = 248 - 0 = 248.
 * 
 * Ex avec 23.746 V :
 *      data_integer = 23.
 *      data_decimal = 23746 - 23000 = 746.
 */
    
    *data_integer   = data;//Integer part of the float.
    *data_decimal   = (data * 1000) - (*data_integer * 1000);//-1.234
}
//__________________________________________________________________________________________________

void set_RTCC_data_time(int year,int month,int day,int weekDay,int hours,int minutes,int seconds){
/* Set Real-Time Clock and Calendar (RTCC) :
 * ----------------------------------------
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
//__________________________________________________________________________________________________

void soft_start_charge(){
/*
 * ICHARGE_TARGET = Ich * (R_SNS_B/1mV) - 1.
 * 
 * A faire :    - Coder fonction qui convertit un courant en ICHARGE_TARGET.
 */
    static unsigned short   soft_counter        = 0;
    static unsigned long    start_time_second   = 0;
    unsigned long           time_second         = 0;
    unsigned short          f_i2c_end_writing   = 0;
    
    if(start_time_second == 0){//At first call.
        start_time_second = get_i2c_sample_time();//Save first start time.
    }
    time_second = get_i2c_sample_time();//Get new time.
    time_second = time_second - start_time_second;
    
    if(soft_counter == 0 && time_second > 10){
        i2c_master_start_write_data(TM_TC_ICHARGE_TARGET,9,&f_i2c_end_writing);
        while(f_i2c_end_writing != 1){Nop();}
        f_i2c_end_writing = 0;//Reset.
        soft_counter++;
    }
    else if(soft_counter == 1 && time_second > 20){
        i2c_master_start_write_data(TM_TC_ICHARGE_TARGET,11,&f_i2c_end_writing);
        while(f_i2c_end_writing != 1){Nop();}
        f_i2c_end_writing = 0;//Reset.
        soft_counter++;
    }
    else if(soft_counter == 2 && time_second > 30){
        i2c_master_start_write_data(TM_TC_ICHARGE_TARGET,13,&f_i2c_end_writing);
        while(f_i2c_end_writing != 1){Nop();}
        f_i2c_end_writing = 0;//Reset.
        soft_counter++;
    }
    else if(soft_counter == 3 && time_second > 40){
        i2c_master_start_write_data(TM_TC_ICHARGE_TARGET,15,&f_i2c_end_writing);
        while(f_i2c_end_writing != 1){Nop();}
        f_i2c_end_writing = 0;//Reset.
        soft_counter++;
    }

//    
//    if(soft_counter == 0 && time_second < 10){
//        i2c_write_i_charge(7,&s_counter);//I bat charge at 0.5 A <-> ICHARGE_TARGET = 7.
//        soft_counter++;
//        if(s_counter == 1){
//            led_red     = off;
//            led_blue    = on;
//        }
//    }
//    else if(soft_counter == 1 && time_second >= 10){
//        i2c_write_i_charge(9,&soft_counter);//I bat charge at 0.625 A <-> ICHARGE_TARGET = 9.
//    }
//    else if(soft_counter == 2 && time_second >= 20){
//        i2c_write_i_charge(11,&soft_counter);//I bat charge at 0.75 A <-> ICHARGE_TARGET = 11.
//    }
//    else if(soft_counter == 3 && time_second >= 30){
//        i2c_write_i_charge(13,&soft_counter);//I bat charge at 0.875 A <-> ICHARGE_TARGET = 13.
//    }
//    else if(soft_counter == 4 && time_second >= 40){
//        i2c_write_i_charge(15,&soft_counter);//I bat charge at 1 A <-> ICHARGE_TARGET = 15.
//    }
    
    
    
    
    
    
}
//__________________________________________________________________________________________________

void i2c_write_i_charge(unsigned short i_charge_target,unsigned short *counter){
/* Function for "soft_start_charge()".
 * 
 * Increase counter every time the function is called. 
 */
    unsigned short f_i2c_end_writing = 0;
    
    i2c_master_start_write_data(TM_TC_ICHARGE_TARGET,i_charge_target,&f_i2c_end_writing);
    while(f_i2c_end_writing != 1){Nop();}//Wait i2c write interrupt ending.
    
    //*counter++;
}
//__________________________________________________________________________________________________
