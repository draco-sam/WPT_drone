/*************************************************************************************************** 
 * File             : usb_sam_00.h
 * Date             : 12/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include <string.h>
//#include "usb_device_cdc.h"
#include "usb_mplab/usb_device_cdc.h"

void get_menu(char *data);
void get_data_i2c(char *t_data);
unsigned short ascii_to_integer(unsigned char *table);
void float_to_ascii(float data_float,char *t_table);
void write_usb_com(char *t_data,unsigned short *flag_sending);
void read_usb_com(unsigned short  *menu_number);
void extract_integer_decimal(float data,unsigned short *data_integer,unsigned short *data_decimal);
void empty_table(char *table);