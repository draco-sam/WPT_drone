/* 
 * File             : serial_com_00.c
 * Date             : 05/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "serial_com_00.h"

static unsigned short   i2c_address                 = 0b1101000;//104.
static unsigned short   flag_i2c_start              = 0;//Flag start pour code C.
static unsigned short   flag_i2c_write_address      = 0;
static unsigned short   flag_i2c_write_data         = 0;
static unsigned short   i2c_data                    = 0;

//Déclarations structures :
static I2C2STATBITS     i2c_2_stat_bits;
static I2C2TRNBITS      i2c_2_trn_bits;//I2C transmit register.
static I2C2CONLBITS     i2c_2_conl_bits;//I2Cx CONTROL REGISTER LOW.

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
 * 1ère interruption    : Start condition.
 * 2ème                 : ACK slave pour adresse.
 * 3ème                 : ACK slave pour commande.
 * 4ème                 : RSEN = 1, restart condition pour passer en adresse + read.
 * 5ème                 : ACK slave, ok pour read, RCEN = 1.
 * 6ème                 : Lire buffeur de réception, RCEN = 0.
 */    
    
    IFS2bits.MI2C2IF = 0;//Reset flag master I2C 2.
    
    //Interruption après start condition.
    if(flag_i2c_start == 1)
    {
        //S bit at "1" et P bit at "0".
        //Master module drives SCL2 low.
        
        //2)Ecrire adresse dans I2C2TRN registre :
        if(flag_i2c_write_address == 0 && flag_i2c_write_data == 0)
        {
            flag_i2c_write_address = 1;
            
            //Vérifier si bus libre.
            if(i2c_2_stat_bits.TRSTAT == 0)//0 : Master transmit is not in progress.
            {
                i2c_2_trn_bits.I2CTXDATA = i2c_address;
            }
            //si non attendre ????
        }
        //4)Vérifier ACK sur clock n°9 :
        else if(flag_i2c_write_address == 1 && flag_i2c_write_data == 0)
        {
            if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave.
            {
                //SCLx remains low until the next event.
            }
            else
            {
                //PAS recu ACK slave, arreter et reseter tout :
                i2c_2_conl_bits.PEN     = 1;//1 = Initiates Stop condition on SDAx and SCLx pins.
                flag_i2c_start          = 0;
                flag_i2c_write_address  = 0;
                flag_i2c_write_data     = 0;
                i2c_data                = 0;
                
            }
            
        }
        
        
        
        
        
    }
}
//**************************************************************************************************

void i2c_master_write(unsigned short data)
/*
 * 
 */
{  
    //Vérifier si ancien stop détecté :
    if(i2c_2_stat_bits.P == 1)//1 = Indicates that a Stop bit has been detected last.
    {
        flag_i2c_start = 1;
        //flag_i2c_write_address = 1;
        
        //1)Générer condition de start :
        i2c_2_conl_bits.SEN = 1;//Initiates Start condition on SDAx and SCLx pins.
        
        //Sauvegarder data pour routine de service d'intérruption.
        i2c_data = data;
    }
    
    
}
//**************************************************************************************************