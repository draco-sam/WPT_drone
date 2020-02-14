/*************************************************************************************************** 
 * File             : i2c_sam_01.h
 * Date             : 13/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "../../PIC24FJ128GC006.h"
#include <stddef.h>

//Sub addresses of read register on i2c slave IC charger :
#define TX_CONFIG_BITS      0x14
#define TM_CHARGER_STATE    0x34
#define TM_VBAT             0x3a
#define TM_IBAT             0x3d
#define TM_VIN              0x3b
#define TM_VSYS             0x3c
#define TM_I_IN             0x3e
#define TM_DIE_TEMP         0x3f
#define TM_NTC_RATIO        0x40
#define TM_I_CHARGE_DAC     0x44
#define TM_V_CHARGE_DAC     0x45
#define TM_CHEM_CELLS       0x43

#define R_SENS_BATTERY      16e-3//16m ohms.
#define R_SENS_IN           32e-3//32m ohms.
#define R_NTC_BIAS          10e+3
#define CELL_COUNT          1

typedef struct I2c_tm_analog
/*
 * Structure for i2c TM data.
 */
{
    float           data_1;
    float           data_2;
    float           data_3;
    float           data_4;
    float           data_5;
}I2c_tm_analog;
//__________________________________________________________________________________________________

//void i2c_master_start_read_tm(unsigned short data);
void i2c_master_start_read_tm(unsigned short tm_address,unsigned short *f_data_ready);
void i2c_master_init(void);
I2c_tm_analog i2c_master_get_tm(unsigned short tm_address);
void i2c_master_start_write_data(   unsigned short tx_address,unsigned short data,
                                    unsigned short *f_end_writing);