/*************************************************************************************************** 
 * File             : main_rx_usb_i2c_00.c
 * Date             : 12/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#include "01_lib_wpt_rx/lib_mplab/system.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        MCC_USB_CDC_DemoTasks();
    }

    return 1;
}
/**
 End of File
*/

