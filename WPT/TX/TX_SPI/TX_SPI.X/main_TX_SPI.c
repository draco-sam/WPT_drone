
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
    
    
    //SPI config :
    SPI1BUFHbits.SPI1BUFH = 0;
    SPI1BUFLbits.SPI1BUFL = 0;
    IEC0bits.SPI1RXIE   = 1;
    IFS7bits.SPI1IF     = 1;//General interrupt ???
    SPI1CON1Lbits.SPIEN = 1;//Enable Module.
    SPI1CON1Lbits.MODE32    = 0;//8-bit.
    SPI1CON1Lbits.MODE16    = 0;//8-bit.
    SPI1CON1Lbits.CKE       = 0;//idle to active clock.
    SPI1CON1Lbits.SSEN      = 0;//SSx pin controlled by port IO (not use in SPI).
    SPI1CON1Lbits.CKP       = 0;//Idle clock is a low level.
    SPI1CON1Lbits.MSTEN     = 0;//Slave mode.
    
    SPI1CON1Hbits.FRMEN     = 0;//Framed SPI disabled.
    
    SPI1IMSKLbits.SPIRBFEN  = 1;//SPI receive buffer full generates an interrupt.
             
    
    
    
    
    while (1)
    {
        //18.5e3 <-> 1s in loop for.
        for(time_counter=0 ; time_counter < 18.5e3 ; time_counter++){
        Nop();
        }
        //led_red = !led_red;
        
        //spi_data_in = SPI1_Exchange8bit(spi_data_out);
        
        if(IFS0bits.SPI1RXIF == 1){
            led_red     = off;
            led_blue    = on;
        }
    }
    return 1; 
}
/**
 End of File
*/

