/*************************************************************************************************** 
 * File             : system.c
 * Date             : 21/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/


#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "system_types.h"
#include "ext_int.h"
#include "interrupt_wpt_tx.h"
#include "traps.h"
#include "pwm.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    CLOCK_Initialize();
    INTERRUPT_Initialize();
    PWM_Initialize();
    EXT_INT_Initialize();
    INTERRUPT_GlobalEnable();
    SYSTEM_CORCONModeOperatingSet(CORCON_MODE_PORVALUES);
}

/**
 End of File
*/