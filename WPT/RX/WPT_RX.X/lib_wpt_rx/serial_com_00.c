/* 
 * File             : serial_com_00.c
 * Date             : 25/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "serial_com_00.h"

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
static unsigned short   i2c_flag_read               = 0;//Read OFF.

//Déclarations structures :
static I2C1STATBITS     i2c_1_stat_bits;
static IFS1BITS         i2c_interrupt_flag;
static IEC1BITS         i2c_int_enable;
static I2C1CONBITS      i2c_1_con;//I2Cx CONTROL REGISTER LOW.


void i2c_master_init(void)
/*
 * 
 */
{
    // Baud Rate Generator Value.
    //Recalculer !!!! changement de PIC dsPIC33 -->PIC24 !!!
    I2C1BRG = 0x27;//39 @100 kHz (9 @400 kHz).
    

    /***********************************************************************************************
     * I2C1CON : I2C 1 Control Register :
     * ---------------------------------     
     */
    I2C1CONbits.I2CEN       = 1;//Enables the I2Cx module, SDAx and SCLx pins as serial port pins.
    I2C1CONbits.I2CSIDL     = 0;//0 = Continues module operation in Idle mode.
    I2C1CONbits.SCLREL      = 0;//Holds SCLx clock low (clock stretch).
    I2C1CONbits.IPMIEN      = 0;//IPMI Support mode is disabled.
    I2C1CONbits.A10M        = 0;//I2CxADD is a 7-bit Slave address.
    
    //Slew rate control is disabled for Standard Speed mode (100kHz, 1MHz).
    I2C1CONbits.DISSLW      = 0;//Enable (comme ex MPLAB...)
    
    I2C1CONbits.SMEN        = 1;//!!!0 : Disables SMBus-specific inputs.
    
    //Enables interrupt when a general call address is received in the I2CxRSR 
    //(module is enabled for reception)
    I2C1CONbits.GCEN        = 1;
    
    I2C1CONbits.STREN       = 0;//Disables clock stretching.
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
    
    //INTCON2bits.GIE = 0;
    IEC1bits.MI2C1IE = 0;//disable the master interrupt.
    IFS1bits.MI2C1IF = 0;//Reset flag master I2C 2.
    
    led_red     = off;
    led_blue    = on;
    led_green   = off;
    
    i2c_interrupt_counter++;
    
    if(i2c_flag_read == 1)//Read value from slave :
    {
        //1)Send slave address with a future write communication :
        if(i2c_interrupt_counter == 1)
        {
            I2C1TRN = i2c_slave_add_write;//Write address in buffeur out.
        }
        //2)Send a data command to the slave :
        else if(i2c_interrupt_counter == 2)
        {
            if(i2c_1_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
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
            if(i2c_1_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
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
            if(i2c_1_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
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
        //6)Read the I2CxRCV receive buffer and begin the read of the 2th data :
        else if(i2c_interrupt_counter == 6)
        {
            if(i2c_1_stat_bits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
            {
                i2c_data_l = I2C1RCV;//Read receive buffer I2CxRCV and auto clear RBF bit
                
                //Enables Receive mode for the 2th data byte.
                //Bit hardware cleared.
                I2C1CONbits.RCEN = 1;
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }
        //7)Read the 2th data on receive buffer and send a NACK to the slave :
        else if(i2c_interrupt_counter == 7)
        {
            if(i2c_1_stat_bits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
            {
                i2c_data_h = I2C1RCV;//Read receive buffer I2CxRCV and auto clear RBF bit
                
                //1 = Initiates Acknowledge sequence on SDAx and SCLx pins
                //and transmits NACK bit on 9th clock,ACKDT =1.
                I2C1CONbits.ACKEN = 1;
            }
            else
            {
                i2c_interrupt_counter = 98;
            }
        }   
        //8)Initiates Stop condition on SDAx and SCLx pins :
        else if(i2c_interrupt_counter == 8 || i2c_interrupt_counter == 99)
        {
            I2C1CONbits.PEN    = 1; 
        }
        //9)Reset counter for next communication, SDAx and SCLx pins are at "1" :
        else if(i2c_interrupt_counter == 9 || i2c_interrupt_counter == 100)
        {
            //1 = Indicates that a Stop bit has been detected last.
            if(i2c_1_stat_bits.P != 1 || i2c_interrupt_counter == 100)
            {
                 i2c_data_l = 0;//Bad data info !!!
                 i2c_data_h = 0;//Bad data info !!!
            }
            i2c_interrupt_counter = 0;//Reset.  
        }
    }
    
    //INTCON1bits.GIE = 1;
    i2c_int_enable.MI2C1IE = 1;//Enable the master interrupt.
}
//__________________________________________________________________________________________________

void i2c_master_start_read_tm(unsigned short tm_address)
/*
 * Start i2C master read telemetry from slave IC charger and save it on static variables.
 */
{
    i2c_flag_read   = 1;//Read ongoing, flag for interrupt.
    i2c_command     = tm_address;
    
    //!!! Reset le µP, PQ ???
    I2C1CONbits.SEN   = 1;//Initiates Start condition on SDAx and SCLx pins.
   
    /*
     * Vérifier si :
     *      - Bus libre.
     *      - Stop bit anciennement détecté.
     */
    /*
    if(i2c_1_stat_bits.TRSTAT == 0 && i2c_1_stat_bits.P == 1)
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

int i2c_master_get_tm(void)
/*
 * I2C master get telemetry to main program .
 * The 16-bit data is decomposed into 2 bytes.
 */
{
    int data = 0;
    
    data        = i2c_data_h << 8;//High 8-bit of data 16-bit.
    data        = data | i2c_data_l;//Low 8-bit add on final data 16-bit.
    
    //Clear variables for next TM.
    i2c_data_h  = 0;
    i2c_data_l  =0;

    return data;
};
//__________________________________________________________________________________________________
