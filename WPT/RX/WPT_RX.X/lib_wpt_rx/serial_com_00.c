/* 
 * File             : serial_com_00.c
 * Date             : 11/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "serial_com_00.h"

static unsigned short   i2c_slave_add_write         = 0b11010000;//Adresse 104 et bit 0 à "0".
static unsigned short   i2c_slave_add_read          = 0b11010001;//Adresse 104 et bit 0 à "1".
static unsigned short   i2c_data                    = 0;
static unsigned short   i2c_interrupt_counter       = 0;

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
    I2C2BRG = 2932;//I2CBRG 18 (ox12);
        
    i2c_1_con.I2CEN     = 1;//Enables the I2Cx module, SDAx and SCLx pins as serial port pins.
    i2c_1_con.I2CSIDL   = 0;//0 = Continues module operation in Idle mode.
    i2c_1_con.IPMIEN    = 0;//IPMI Support mode is disabled.
    i2c_1_con.A10M      = 0;//I2CxADD is a 7-bit Slave address.
    //Slew rate control is disabled for Standard Speed mode (100kHz, 1MHz).
    i2c_1_con.DISSLW    = 1;
    i2c_1_con.SMEN      = 0;//Disables SMBus-specific inputs.
    i2c_1_con.STREN     = 0;//Disables clock stretching.
    i2c_1_con.ACKDT     = 0;
    i2c_1_con.ACKEN     = 0;//Acknowledge sequence is Idle.
    i2c_1_con.RCEN      = 0;//Receive sequence is not in progress.
    i2c_1_con.PEN       = 0;//Stop condition is Idle (inactif).
    i2c_1_con.RSEN      = 0;//Restart condition is Idle.
    i2c_1_con.SEN       = 0;//Start condition is Idle.
    
    I2C1STAT = 0;//I2Cx STATUS REGISTER.
    
    i2c_interrupt_flag.MI2C1IF = 0;//Clear the master interrupt flag.
    i2c_int_enable.MI2C1IE = 1;//Enable the master interrupt.
    //INTCON2bits.GIE = 1;
}
//**************************************************************************************************

void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C2Interrupt ( void )
{
/*
 * 
 */    
    
    //INTCON2bits.GIE = 0;
    i2c_int_enable.MI2C1IE = 0;//disable the master interrupt.
    
    //!!! Ajouter code pour LED en debug !!!
    
    i2c_interrupt_flag.MI2C1IF = 0;//Reset flag master I2C 2.
    
    i2c_interrupt_counter++;
    
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
            I2C1TRN = i2c_data;//Command to the slave.
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
            i2c_1_con.RSEN   = 1;//1 = Initiates Restart condition on SDAx and SCLx pins.
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
            i2c_1_con.RCEN = 1;//1 = Enables Receive mode for I2C.
        }
        else
        {
            i2c_interrupt_counter = 98;
        }
    }
    //6)Read the I2CxRCV receive buffer and send a NACK to the slave :
    else if(i2c_interrupt_counter == 6)
    {
        if(i2c_1_stat_bits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
        {
            i2c_data = I2C1RCV;//Read receive buffer I2CxRCV and auto clear RBF bit
            
            //1 = Initiates Acknowledge sequence on SDAx and SCLx pins
            //and transmits NACK bit on 9th clock,ACKDT =1.
            i2c_1_con.ACKEN = 1;
        }
    }
    //7)Initiates Stop condition on SDAx and SCLx pins :
    else if(i2c_interrupt_counter == 7 || i2c_interrupt_counter == 99)
    {
        i2c_1_con.PEN    = 1; 
    }
    //8)Reset counter for next communication, SDAx and SCLx pins are at "1" :
    else if(i2c_interrupt_counter == 8 || i2c_interrupt_counter == 100)
    {
        //1 = Indicates that a Stop bit has been detected last.
        if(i2c_1_stat_bits.P != 1 || i2c_interrupt_counter == 100)
        {
             i2c_data = 0xffff;//Bad data info !!!
        }
        i2c_interrupt_counter = 0;//Reset.  
    }
    
    //INTCON2bits.GIE = 1;
    i2c_int_enable.MI2C1IE = 1;//Enable the master interrupt.
}
//**************************************************************************************************

void i2c_master_write(unsigned short data)
/*
 * 
 */
{  
    /*
     * Vérifier si :
     *      - Bus libre.
     *      - Stop bit anciennement détecté.
     */
    if(i2c_1_stat_bits.TRSTAT == 0 && i2c_1_stat_bits.P == 1)
    {
        i2c_1_con.SEN = 1;//Initiates Start condition on SDAx and SCLx pins.
        i2c_data = data;//Save data for subroutine interrupt.
    }
    //si non attendre ????
    
    
    
}
//**************************************************************************************************

