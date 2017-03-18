#include "adcreader.h"
#include <QDebug>
#include "bcm2835.h"

void ADCreader::run()
{
    running = true;

    bcm2835_init();
    bcm2835_spi_begin();

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

   while (running) {
        qDebug() << "Tick";

 //       voltage+=1;


        char send_data[2] = {0xC0,0x00};
        char read_data[3];

       bcm2835_spi_transfernb(send_data,read_data,3);

        printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.  0x%02X.  0x%02X \n", send_data[0], read_data[0],read_data[1],read_data[2]);

        uint8_t a,b,c;
        uint16_t v;


        a= ((read_data[0]<<1) + (read_data[1]>>7));
        b= (((read_data[1]<<1) + (read_data[2]>>7)))&0x7F;
        c= read_data[2]>>7;
        v= ((a<<8)|(b<<1)|c);
        voltage= v*3.3/1023;

        printf("a= 0x%02X. b= 0x%02X.  c= 0x%02X. \n", a,b,c);

        printf("voltage = %fV \n", voltage);
        printf("\n\n");
        bcm2835_delay(20);
    }
   bcm2835_spi_end();
   bcm2835_close();


}


void ADCreader::quit()
{
    running = false;
    exit(0);
}
