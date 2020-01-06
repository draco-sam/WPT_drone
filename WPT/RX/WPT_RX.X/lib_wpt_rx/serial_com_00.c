/* 
 * File             : serial_com_00.c
 * Date             : 05/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "serial_com_00.h"

static unsigned short   i2c_slave_address                 = 0b1101000;//104.
static unsigned short   flag_i2c_start              = 0;//Flag start pour code C.
static unsigned short   flag_i2c_repeated_start     = 0;
static unsigned short   flag_i2c_write_address      = 0;
static unsigned short   flag_i2c_write_data         = 0;
static unsigned short   flag_i2c_reception          = 0;
static unsigned short   flag_i2c_rbf_complete       = 0;
static unsigned short   i2c_data                    = 0;

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
    if(flag_i2c_start == 1 && flag_i2c_repeated_start == 0)
    {
        //S bit at "1" et P bit at "0".
        //Master module drives SCL2 low.
        
        //2)Ecrire adresse dans I2C2TRN registre :
        if(flag_i2c_write_address == 0 && flag_i2c_write_data == 0)
        {
            flag_i2c_write_address      = 1;
            i2c_2_trn_bits.I2CTXDATA    = i2c_slave_address;
        }
        //4)Vérifier ACK sur clock n°9 :
        else if(flag_i2c_write_address == 1 && flag_i2c_write_data == 0)
        {
            if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave.
            {
                //Envoyer la commande :
                flag_i2c_write_data         = 1;
                i2c_2_trn_bits.I2CTXDATA    = i2c_data;
            }
            else
            {
                //PAS recu ACK slave, arreter et reseter tout.
                i2c_stop_com();                                
            } 
        }
        else if(flag_i2c_write_address == 1 && flag_i2c_write_data == 1)
        {
            if(i2c_2_stat_bits.ACKSTAT == 0)//0 = Acknowledge was received from Slave.
            {
                //Envoyer repeated start :
                flag_i2c_repeated_start = 1;
                flag_i2c_write_address  = 0;//Reset flag pour repeated start.
                i2c_2_con_l_bits.RSEN   = 1;
            }
            else
            {
                //PAS recu ACK slave, arreter et reseter tout.
                i2c_stop_com();                                
            }
        }  
    }
    else if(flag_i2c_start == 0 && flag_i2c_repeated_start == 1)
    {
        if(flag_i2c_write_address == 0)
        {
            flag_i2c_write_address      = 1;
            i2c_2_trn_bits.I2CTXDATA    = i2c_slave_address;
        }
        else//flag_i2c_write_address = 1.
        {
            if(flag_i2c_rbf_complete == 0 && i2c_2_stat_bits.RBF == 0)
            {
                i2c_2_con_l_bits.RCEN = 1;
            }
            else if()
            {
                //
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
    /*
     * Vérifier si :
     *      - Bus libre.
     *      - Stop bit anciennement détecté.
     */
    if(i2c_2_stat_bits.TRSTAT == 0 && i2c_2_stat_bits.P == 1)
    {
        flag_i2c_start = 1;
        //flag_i2c_write_address = 1;
        
        //1)Générer condition de start :
        i2c_2_con_l_bits.SEN = 1;//Initiates Start condition on SDAx and SCLx pins.
        
        //Sauvegarder data pour routine de service d'intérruption.
        i2c_data = data;
    }
    //si non attendre ????
    
    
    
}
//**************************************************************************************************

//static i2c_stop_com(void)
void i2c_stop_com(void)
/*
 * 
 */
{
    i2c_2_con_l_bits.PEN    = 1;//1 = Initiates Stop condition on SDAx and SCLx pins.
    flag_i2c_start          = 0;
    flag_i2c_write_address  = 0;
    flag_i2c_write_data     = 0;
    flag_i2c_reception      = 0;
}
//**************************************************************************************************