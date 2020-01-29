
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include "PIC24FJ128GC006.h"  
#include "serial_com_01.h"

void oscillator_init(void);
void pin_init(void);
void interrupt_init(void);
void i2c_bus_high(void);

#endif	/* XC_HEADER_TEMPLATE_H */

