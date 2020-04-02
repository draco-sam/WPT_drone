/*************************************************************************************************** 
 * File             : ext_int.h
 * Date             : 02/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#ifndef _EXT_INT_H
#define _EXT_INT_H

/**
    Section: Includes
*/

#include <xc.h>

#define pwm_on      1
#define pwm_off     0      
#define pwm_5_h     PG5CONLbits.ON

// Provide C++ Compatibility
#ifdef __cplusplus  

extern "C" {

#endif

/**
    Section: Macros
*/
/**
  @Summary
    Clears the interrupt flag for INT1

  @Description
    This routine clears the interrupt flag for the external interrupt, INT1.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
    {
        // User Area Begin->code: External Interrupt 1

        // User Area End->code: External Interrupt 1
        EX_INT1_InterruptFlagClear();
    }
    </code>

*/
#define EX_INT1_InterruptFlagClear()       (IFS0bits.INT1IF = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will not be serviced by the 
    interrupt handler, _INT1Interrupt.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Changing the external interrupt edge detect from negative to positive
    <code>
    // clear the interrupt enable
    EX_INT1_InterruptDisable();
    // change the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and re-enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_InterruptDisable()     (IEC0bits.INT1IE = 0)
/**
  @Summary
    Clears the interrupt enable for INT1

  @Description
    This routine clears the interrupt enable for the external interrupt, INT1.
    After calling this routine, external interrupts on this pin will be serviced by the 
    interrupt handler, _INT1Interrupt.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_InterruptEnable()       (IEC0bits.INT1IE = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to negative edge.

  @Description
    This routine set the edge detect of the extern interrupt to negative edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a high to low level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle negative edge interrupts
    <code>
    // set the edge
    EX_INT1_NegativeEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_NegativeEdgeSet()          (INTCON2bits.INT1EP = 1)
/**
  @Summary
    Sets the edge detect of the external interrupt to positive edge.

  @Description
    This routine set the edge detect of the extern interrupt to positive edge.  
    After this routine is called the interrupt flag will be set when the external 
    interrupt pins level transitions from a low to high level.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Setting the external interrupt to handle positive edge interrupts
    <code>
    // set the edge
    EX_INT1_PositiveEdgeSet();
    // clear the interrupt flag and enable the interrupt
    EX_INT1_InterruptFlagClear();
    EX_INT1_InterruptEnable();
    </code>

*/
#define EX_INT1_PositiveEdgeSet()          (INTCON2bits.INT1EP = 0)

/**
  @Summary
    Callback for EX_INT1.

  @Description
    This routine is callback for EX_INT1

  @Param
    None.

  @Returns
    None
 
  @Example 
	<code>
    EX_INT1_CallBack();
    </code>
*/
void EX_INT1_CallBack(void);


/**
    Section: External Interrupt Initializers
 */
/**
  @Summary
    Initializes the external interrupt pins

  @Description
    This routine initializes the EXT_INT driver to detect the configured edge, clear
    the interrupt flag and enable the interrupt.

    The following external interrupts will be initialized:
    INT1 - EX_INT1
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    Initialize the external interrupt pins
    <code>
    EXT_INT_Initialize();
    </code>

*/
void EXT_INT_Initialize(void);
// Provide C++ Compatibility
#ifdef __cplusplus  

}

#endif
#endif
