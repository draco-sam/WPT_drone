/*************************************************************************************************** 
 * File             : temp_table.c
 * Date             : 11/04/2020.   
 * Author           : Samuel LORENZINO.
 * Comments         :
 * Revision history : 
 **************************************************************************************************/
#include "temp_table.h"

float get_temperature(unsigned short data_num){
/*
 */
    unsigned short  offset          = 3258;//NTC_RATIO = 3258 <-> 70.01 °C at index table 0.
    float           temp_table[8000]    = {
    
    
    };
    
        
 
    
    return temp_table[data_num - offset];
}
//__________________________________________________________________________________________________
