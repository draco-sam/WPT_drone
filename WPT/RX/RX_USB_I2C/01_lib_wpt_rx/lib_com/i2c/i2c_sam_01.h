/*************************************************************************************************** 
 * File             : i2c_sam_01.h
 * Date             : 04/05/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "../../PIC24FJ128GC006.h"
#include <stddef.h>
#include "../usb/usb_sam_00.h"
#include "../../lib_mplab/rtcc.h"

//Sub addresses of read register on i2c slave IC charger :
#define TX_CONFIG_BITS          0x14
#define TM_TC_ICHARGE_TARGET    0x1a
#define TM_VCHARGE_SETTING      0x1b
#define TM_MAX_CHARGE_TIMER     0x30
#define TM_CV_TIMER             0x31
#define TM_CHARGER_STATE        0x34
#define TM_CHARGE_STATUS        0x35
#define TM_SYSTEM_STATUS        0x39
#define TM_VBAT                 0x3a
#define TM_IBAT                 0x3d
#define CHARGER_CONFIG_BITS     0x29//Read/write register.
#define TM_VIN                  0x3b
#define TM_VSYS                 0x3c
#define TM_I_IN                 0x3e
#define TM_DIE_TEMP             0x3f
#define TM_NTC_RATIO            0x40
#define TM_I_CHARGE_DAC         0x44
#define TM_V_CHARGE_DAC         0x45
#define TM_CHEM_CELLS           0x43

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
    float           sample_time;
}I2c_tm_analog;
//__________________________________________________________________________________________________

//void i2c_master_start_read_tm(unsigned short data);
void i2c_master_start_read_tm(unsigned short tm_address,unsigned short *f_data_ready);
void i2c_master_init(void);
I2c_tm_analog i2c_master_get_tm(unsigned short tm_address);
void i2c_master_start_write_data(   unsigned short tx_address,unsigned short data,
                                    unsigned short *f_end_writing);
void get_i2c_tm_and_send_to_usb(unsigned short TM_ADDRESS,char *text_1,char *text_2,
                                unsigned short *flag_sending);
void extract_integer_decimal(float data,long *data_integer,short *data_decimal);
void float_to_ascii(float data_float,char *t_table);
unsigned long get_i2c_sample_time();
unsigned long convertTimeToSeconds(unsigned int hour,unsigned int minutes,unsigned int seconds);
void set_RTCC_data_time(int year,int month,int day,int weekDay,int hours,int minutes,int seconds);
void soft_start_charge();
void i2c_write_i_charge(unsigned short i_charge_target,unsigned short *counter);