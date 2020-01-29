/* 
 * File             : serial_com_00.h
 * Date             : 05/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

#include "PIC24FJ128GC006.h"
#include <stddef.h>

//Sub addresses of read register on i2c slave IC charger :
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
#define CELL_COUNT          4

//void i2c_master_start_read_tm(unsigned short data);
void i2c_master_start_read_tm(unsigned short tm_address,unsigned short *f_data_ready);
void i2c_master_init(void);
float i2c_master_get_tm(unsigned short tm_address);