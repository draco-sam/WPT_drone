
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <stdio.h>
#include "PIC24FJ128GC006.h"  
#include "lib_com/serial_com_01.h"
#include "system.h"

void oscillator_init(void);
void pin_init(void);
void interrupt_init(void);
void i2c_bus_high(void);
void wait(unsigned long count);

#endif	/* XC_HEADER_TEMPLATE_H */

