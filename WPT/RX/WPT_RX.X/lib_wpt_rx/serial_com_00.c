/* 
 * File             : serial_com_00.c
 * Date             : 08/01/2020.   
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
static I2C2STATBITS     i2c_2_stat_bits;
static I2C2TRNBITS      i2c_2_trn_bits;//I2C transmit register.
static I2C2RCVBITS      i2c_2_rcv_bits;//I2C receive register.
static I2C2CONLBITS     i2c_2_con_l_bits;//I2Cx CONTROL REGISTER LOW.

void i2c_master_init(void)
/*
 * 
 */
{
    // Baud Rate Generator Value.   
    I2C2BRG = 2932;//I2CBRG 18 (ox12);
    
    //Enables the I2Cx module, and configures the SDAx and SCLx pins as serial port pins.
    i2c_2_con_l_bits.I2CEN      = 1;
    i2c_2_con_l_bits.I2CEN      = 0;
    i2c_2_con_l_bits.STREN      = 0;
    i2c_2_con_l_bits.A10M       = 0;//I2CxADD is a 7-bit Slave address.
    //Slew rate control is disabled for Standard Speed mode (100kHz, 1MHz).
    i2c_2_con_l_bits.DISSLW     = 1;
    i2c_2_con_l_bits.SMEN       = 0;//Disables SMBus-specific inputs.
    i2c_2_con_l_bits.STREN      = 0;//Disables clock stretching.
    i2c_2_con_l_bits.ACKDT      = 0;
    i2c_2_con_l_bits.ACKEN      = 0;//Acknowledge sequence is Idle.
    i2c_2_con_l_bits.RCEN       = 0;//Receive sequence is not in progress.
    i2c_2_con_l_bits.PEN        = 0;//Stop condition is Idle (inactif).
    i2c_2_con_l_bits.RSEN       = 0;//Restart condition is Idle.
    i2c_2_con_l_bits.SEN        = 0;//Start condition is Idle.
    
    I2C2STAT = 0;//I2Cx STATUS REGISTER.
        
    IFS2bits.MI2C2IF = 0;//Clear the master interrupt flag.
    IEC2bits.MI2C2IE = 1;//Enable the master interrupt.
    //INTCON2bits.GIE = 1;
}
//**************************************************************************************************

void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C2Interrupt ( void )
{
/*
 * 
 */    
    
    //INTCON2bits.GIE = 0;
    IEC2bits.MI2C2IE = 0;//disable the master interrupt.
    
    //!!! Ajouter code pour LED en debug !!!
    
    IFS2bits.MI2C2IF = 0;//Reset flag master I2C 2.
    
    i2c_interrupt_counter++;
    
    //1)Send slave address with a future write communication :
    if(i2c_interrupt_counter == 1)
    {
        i2c_2_trn_bits.I2CTXDATA = i2c_slave_add_write;//Write address in buffeur out.
    }
    //2)Send a data command to the slave :
    else if(i2c_interrupt_counter == 2)
    {
        if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
        {
            i2c_2_trn_bits.I2CTXDATA = i2c_data;//Command to the slave.
        }
        else
        {
            i2c_interrupt_counter = 98;
        }
    }
    //3)Restart condition for future read communication :
    else if(i2c_interrupt_counter == 3)
    {
        if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
        {
            i2c_2_con_l_bits.RSEN   = 1;//1 = Initiates Restart condition on SDAx and SCLx pins.
        }
        else
        {
            i2c_interrupt_counter = 98;
        }
    }
    //4)Send the slave address with a future read communication :
    else if(i2c_interrupt_counter == 4)
    {
        i2c_2_trn_bits.I2CTXDATA = i2c_slave_add_read;
    }
    //5)Master will send 8 clocks to receive the data byte from the slave :
    else if(i2c_interrupt_counter == 5)
    {
        if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave
        {
            i2c_2_con_l_bits.RCEN = 1;//1 = Enables Receive mode for I2C.
        }
        else
        {
            i2c_interrupt_counter = 98;
        }
    }
    //6)Read the I2CxRCV receive buffer and send a NACK to the slave :
    else if(i2c_interrupt_counter == 6)
    {
        if(i2c_2_stat_bits.RBF == 1)//1 = Receive is complete, I2CxRCV is full.
        {
            i2c_data = i2c_2_rcv_bits.I2CRXDATA;//Read receive buffer I2CxRCV and auto clear RBF bit
            
            //1 = Initiates Acknowledge sequence on SDAx and SCLx pins
            //and transmits NACK bit on 9th clock,ACKDT =1.
            i2c_2_con_l_bits.ACKEN = 1;
        }
    }
    //7)Initiates Stop condition on SDAx and SCLx pins :
    else if(i2c_interrupt_counter == 7 || i2c_interrupt_counter == 99)
    {
        i2c_2_con_l_bits.PEN    = 1; 
    }
    //8)Reset counter for next communication, SDAx and SCLx pins are at "1" :
    else if(i2c_interrupt_counter == 8 || i2c_interrupt_counter == 100)
    {
        //1 = Indicates that a Stop bit has been detected last.
        if(i2c_2_stat_bits.P != 1 || i2c_interrupt_counter == 100)
        {
             i2c_data = 0xffff;//Bad data info !!!
        }
        i2c_interrupt_counter = 0;//Reset.  
    }
    
    //INTCON2bits.GIE = 1;
    IEC2bits.MI2C2IE = 1;//Enable the master interrupt.
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
    if(i2c_2_stat_bits.TRSTAT == 0 && i2c_2_stat_bits.P == 1)
    {
        i2c_2_con_l_bits.SEN = 1;//Initiates Start condition on SDAx and SCLx pins.
        i2c_data = data;//Save data for subroutine interrupt.
    }
    //si non attendre ????
    
    
    
}
//**************************************************************************************************

