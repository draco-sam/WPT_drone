/*************************************************************************************************** 
 * File             : interrupt_wpt_tx.h
 * Date             : 21/02/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/

#ifndef _INTERRUPT_WPT_TX_H
#define _INTERRUPT_WPT_TX_H

#define led_red         LATCbits.LATC14
#define led_green       LATCbits.LATC13
#define led_blue        LATCbits.LATC12
#define on              0
#define off             1
#define pwm_on          1
#define pwm_off         0      
#define pwm_5_h         PG5CONLbits.ON

#define EX_INT0_InterruptFlagClear()    (IFS0bits.INT0IF = 0)
#define EX_INT0_InterruptDisable()      (IEC0bits.INT0IE = 0)
#define EX_INT0_InterruptEnable()       (IEC0bits.INT0IE = 1)
#define EX_INT0_NegativeEdgeSet()       (INTCON2bits.INT0EP = 1)
#define EX_INT0_PositiveEdgeSet()       (INTCON2bits.INT0EP = 0)
#define EX_INT1_InterruptFlagClear()    (IFS0bits.INT1IF = 0)
#define EX_INT1_InterruptDisable()      (IEC0bits.INT1IE = 0)
#define EX_INT1_InterruptEnable()       (IEC0bits.INT1IE = 1)
#define EX_INT1_NegativeEdgeSet()       (INTCON2bits.INT1EP = 1)
#define EX_INT1_PositiveEdgeSet()       (INTCON2bits.INT1EP = 0)


void INTERRUPT_Initialize(void);
void EXT_INT_Initialize(void);
void EX_INT0_CallBack(void);
void EX_INT1_CallBack(void);


inline static void INTERRUPT_GlobalEnable(void)
{
    __builtin_enable_interrupts();
}

inline static void INTERRUPT_GlobalDisable(void)
{
    __builtin_disable_interrupts();
}


#endif