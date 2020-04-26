
#include "mcc_generated_files/system.h"

#define led_red         LATGbits.LATG7
#define led_green       LATGbits.LATG6
#define led_blue        LATEbits.LATE7
#define on              0
#define off             1

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    //Configurer les IO des leds en output :
    TRISEbits.TRISE7    = 0;//"0" : Output.
    TRISGbits.TRISG6    = 0;
    TRISGbits.TRISG7    = 0;
    //Pour les leds en digital io.    
    ANSEbits.ANSELE7 = 0;
    ANSGbits.ANSELG6 = 0;
    ANSGbits.ANSELG7 = 0;
    
    led_red     = on;
    led_blue    = off;
    led_green   = off;
    
    unsigned short  spi_data_out    = 0;
    unsigned short  spi_data_in     = 0;
    unsigned short  spi_status      = 0;
    unsigned long   time_counter    = 0;
    
   
    spi_data_out = 0xaaaa;

    while (1)
    {
        //74e3 <-> 1s in loop for.
        for(time_counter=0 ; time_counter < 74e3 ; time_counter++){
        Nop();
        }
        led_red = !led_red;
        
        spi_data_in = SPI1_Exchange16bit(spi_data_out);
        //spi_status = SPI1_Exchange16bitBuffer(spi_data_out,2,&spi_data_in);
    }

    return 1;
}
/**
 End of File
*/

