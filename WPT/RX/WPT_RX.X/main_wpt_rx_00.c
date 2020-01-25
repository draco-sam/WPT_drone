/* 
 * File             : main_wpt_rx_00.c
 * Date             : 23/01/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 */

//D:\Program Files (x86)\Microchip\xc16\v1.41\support\PIC24F\h.
//#include "lib_wpt_rx/PIC24FJ128GC006.h"
#include "lib_wpt_rx/lib_wpt_rx_00.h"



int main(void) {
    
       
    #define led_red         LATGbits.LATG7
    #define led_green       LATGbits.LATG6
    #define led_blue        LATEbits.LATE7
    #define on              0
    #define off             1
    
    
    //Sub addresses of read register on i2c slave IC charger :
    #define TM_VBAT           0x3a
    #define TM_IBAT           0x3d
    #define TM_VIN            0x3b
    #define TM_VSYS           0x3c
    #define TM_I_IN           0x3e
    #define TM_DIE_TEMP       0x3f
    #define TM_NTC_RATIO      0x40
    #define TM_I_CHARGE_DAC   0x44
    #define TM_V_CHARGE_DAC   0x45

    
      
    
    Nop();
    
    
    pin_init();
    oscillator_init();
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
    i2c_master_init();
    
    
    //!!! Vérifier Pull-up !!!
    i2c_master_start_read_tm(TM_VIN);
    
    
    led_red     = off;
    led_green   = off;
    led_blue    = off;
    
 
    
    while (1)
    {
        // Add your application code
    }
    
    return 0;
}
