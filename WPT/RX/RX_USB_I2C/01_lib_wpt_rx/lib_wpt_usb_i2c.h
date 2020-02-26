/*************************************************************************************************** 
 * File             : lib_wpt_usb_i2c.h
 * Date             : 26/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#ifndef LIB_WPT_USB_I2C_H
#define	LIB_WPT_USB_I2C_H

#include <stdio.h>
#include <string.h>
#include "lib_mplab/system.h"
#include "lib_com/usb/usb_sam_00.h"
#include "lib_com/i2c/i2c_sam_01.h"

typedef struct I2C_x_y_data I2C_x_y_data;
struct I2C_x_y_data
{
    float x;
    float y;//Time.
};

void random_i2c_data(unsigned short type_data,I2C_x_y_data *s_i2c_x_y);
void get_menu(unsigned short menu_number, char *t_menu, unsigned short t_menu_size);


#endif	/* LIB_WPT_USB_I2C_H */
/**
 End of File
*/