/* 
 * File             : serial_com_00.c
 * Date             : 07/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "serial_com_00.h"

static unsigned short   i2c_slave_add_write         = 0b11010000;//Adresse 104 et bit 0 � "0".
static unsigned short   i2c_slave_add_read          = 0b11010001;//Adresse 104 et bit 0 � "1".
static unsigned short   i2c_data                    = 0;
static unsigned short   i2c_interrupt_counter       = 0;

//D�clarations structures :
static I2C2STATBITS     i2c_2_stat_bits;
static I2C2TRNBITS      i2c_2_trn_bits;//I2C transmit register.
static I2C2RCVBITS      i2c_2_rcv_bits;//I2C receive register.
static I2C2CONLBITS     i2c_2_con_l_bits;//I2Cx CONTROL REGISTER LOW.

void i2c_master_init(void)
/*
 * 
 */
{
    
}
//**************************************************************************************************

void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C2Interrupt ( void )
{
/*
 * 
 */    
    
    //!!! Bloquer toutes les int�rruptions !!!
    
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
}
//**************************************************************************************************

void i2c_master_write(unsigned short data)
/*
 * 
 */
{  
    /*
     * V�rifier si :
     *      - Bus libre.
     *      - Stop bit anciennement d�tect�.
     */
    if(i2c_2_stat_bits.TRSTAT == 0 && i2c_2_stat_bits.P == 1)
    {
        i2c_2_con_l_bits.SEN = 1;//Initiates Start condition on SDAx and SCLx pins.
        i2c_data = data;//Save data for subroutine interrupt.
    }
    //si non attendre ????
    
    
    
}
//**************************************************************************************************

