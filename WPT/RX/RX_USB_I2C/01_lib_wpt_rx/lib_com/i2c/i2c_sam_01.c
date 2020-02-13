/* 
 * File             : i2c_sam_01.c
 * Date             : 13/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "i2c_sam_01.h"

 #define led_red         LATGbits.LATG7
 #define led_green       LATGbits.LATG6
 #define led_blue        LATEbits.LATE7
 #define on              0
 #define off             1

static unsigned short   i2c_slave_add_write         = 0xd0;//Adresse 208 (0xd0) et bit 0 à "0".
static unsigned short   i2c_slave_add_read          = 0b11010001;//Adresse 104 et bit 0 à "1".
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
        //7)Master sends ACK to slave. (??? vérifier validité data avant d'envoyer ACK ???)
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
        //!!! Vérifier NACK status bit master envoyé vers slave pour commencer le stop???
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
    i2c_flag_read       = 1;//Read ongoing, flag for interrupt.
    i2c_command         = tm_address;
    s_flag_data_ready   = f_data_ready;//Copier adresse du flag dans variable statique.
    
    //!!! Reset le µP, PQ ???
    I2C1CONbits.SEN   = 1;//Initiates Start condition on SDAx and SCLx pins.
   
    /*
     * Vérifier si :
     *      - Bus libre.
     *      - Stop bit anciennement détecté.
     */
    /*
    if(I2C1STATbits.TRSTAT == 0 && I2C1STATbits.P == 1)
    {
        LATG = 0b01000000;
        i2c_flag_read   = 1;//Read ongoing, flag for interrupt.
        i2c_command     = address;
        I2C1CONbits.SEN   = 1;//Initiates Start condition on SDAx and SCLx pins.
    }
    */
    //si non attendre ????    
}
//__________________________________________________________________________________________________

I2c_tm_analog i2c_master_get_tm(unsigned short tm_address){
/*
 * I2C master get telemetry to main program .
 * The 16-bit data is decomposed into 2 bytes.
 */
    unsigned short  digital_data        = 0;
    I2c_tm_analog i2c_tm_analog;
    
    //Reset value :
    i2c_tm_analog.data_1 = 0.0;
    i2c_tm_analog.data_2 = 0.0;
    i2c_tm_analog.data_3 = 0.0;
    i2c_tm_analog.data_4 = 0.0;
    i2c_tm_analog.data_5 = 0.0;
    
    digital_data        = i2c_data_h << 8;//High 8-bit of data 16-bit.
    digital_data        = digital_data | i2c_data_l;//Low 8-bit add on final data 16-bit.
    
    if(tm_address == TM_VBAT)
    {
        i2c_tm_analog.data_1 = digital_data * 192.264e-6 * CELL_COUNT;//192.264 µV.
    }
    else if(tm_address == TM_VIN || tm_address == TM_VSYS)
    {
        i2c_tm_analog.data_1 = digital_data * 0.001648;//LSB = 1.648 mV.
    }
    else if(tm_address == TM_IBAT)
    {
        i2c_tm_analog.data_1 = (digital_data * 1.46487e-6)/R_SENS_BATTERY;
    }
    else if(tm_address == TM_I_IN)
    {
        i2c_tm_analog.data_1 = (digital_data * 1.46487e-6)/R_SENS_IN;
    }
    else if(tm_address == TM_DIE_TEMP)
    {
        i2c_tm_analog.data_1 = (digital_data - 12010)/45.6;//45.6 °C.
    }
    else if(tm_address == TM_NTC_RATIO)
    {
        i2c_tm_analog.data_1 = (digital_data * R_NTC_BIAS)/(21845 - digital_data);
    }
    else if (tm_address == TM_CHEM_CELLS)
    {
        i2c_tm_analog.data_1 = 0.0;//!!! A coder !!!
        i2c_tm_analog.data_2 = digital_data && 0x0F;//bits 3:0 = 4 bits for number of cells.
    }
    else if (tm_address == TM_CHARGER_STATE)
    {
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
    
    
    //Clear variables for next TM.
    i2c_data_h  = 0;
    i2c_data_l  = 0;

    return i2c_tm_analog;
}
//__________________________________________________________________________________________________

void i2c_master_start_write_data(   unsigned short tx_address,unsigned short data,
                                    unsigned short *f_end_writing){
/*
 * Start i2C master read telemetry from slave IC charger and save it on static variables.
 */
    s_flag_end_writing      = f_end_writing;//Copy the address of the flag on static variable.
    
    //Check if Master transmit is not in progress ("0") :
    if(I2C1STATbits.TRSTAT == 0){
        i2c_flag_write      = 1;//Read ongoing, flag for interrupt.
        i2c_command         = tx_address;
        
        i2c_data_l          = data & 0x00ff;
        i2c_data_h          = data >> 8;
        
        I2C1CONbits.SEN     = 1;//Initiates Start condition on SDAx and SCLx pins.
    }
}
//__________________________________________________________________________________________________