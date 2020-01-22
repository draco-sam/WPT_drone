/* 
 * File             : main_wpt_rx_00.c
 * Date             : 11/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\PIC24F\h.
#include "lib_wpt_rx/PIC24FJ128GC006.h"
#include "lib_wpt_rx/lib_wpt_rx_00.h"

int main(void) {
    
    //Sub addresses of read register on i2c slave IC charger :
    #define ADDR_VBAT           0x3a;
    #define ADDR_IBAT           0x3d;
    #define ADDR_VIN            0x3b;
    #define ADDR_VSYS           0x3c;
    #define ADDR_I_IN           0x3e;
    #define ADDR_DIE_TEMP       0x3f;
    #define ADDR_NTC_RATIO      0x40;
    #define ADDR_I_CHARGE_DAC   0x44;
    #define ADDR_V_CHARGE_DAC   0x45;
    
    Nop();
    
    
    pin_init();
    oscillator_init();
    
    
     
    
    while (1)
    {
        // Add your application code
    }
    
    return 0;
}
