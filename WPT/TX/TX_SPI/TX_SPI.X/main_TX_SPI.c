
#include "mcc_generated_files/system.h"
#include "p33CK256MP206.h"

#define led_red         LATCbits.LATC14
#define led_green       LATCbits.LATC13
#define led_blue        LATCbits.LATC12
#define on              0
#define off             1

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    TRISCbits.TRISC12   = 0;//Blue LED output.
    TRISCbits.TRISC13   = 0;//Green LED output.
    TRISCbits.TRISC14   = 0;//Red LED output.
    
    led_red     = on;
    led_green   = off;
    led_blue    = off;
    
    unsigned short  spi_data_out    = 0;
    unsigned short  spi_data_in     = 0;
    unsigned short  spi_status      = 0;
    unsigned long   time_counter    = 0;
    
   
    spi_data_out = 0xaa;
    
    while (1)
    {
        //74e3 <-> 1s in loop for.
        for(time_counter=0 ; time_counter < 18.5e3 ; time_counter++){
        Nop();
        }
        led_red = !led_red;
        
        spi_data_in = SPI1_Exchange8bit(spi_data_out);
    }
    return 1; 
}
/**
 End of File
*/

