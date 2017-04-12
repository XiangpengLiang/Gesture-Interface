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

        for (int i=0;i<5;i++){
        FingerData[i]=getVoltage(i);
//        voltage[i]=getVoltage(i)*3.3/1023;
        }
    }
   bcm2835_spi_end();
   bcm2835_close();


}

uint16_t ADCreader::getVoltage(uint8_t fingerIndex)
{
    char send_data[3] = {0x01,0x80,0x00};
//    char Address[5] = {0xC0,0xC8,0xD0,0xD8,0xE0};
    char Address[5] = {0x80,0xA0,0xC0,0xE0,0xF0};

    static char read_data[3];

    if(fingerIndex<6)
 //   send_data[0] = Address[fingerIndex-1];
    send_data[1] = Address[fingerIndex];

    bcm2835_spi_transfernb(send_data,read_data,3);

//    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.  0x%02X.  0x%02X \n", send_data[0], read_data[0],read_data[1],read_data[2]);


    uint16_t v;


//    vt= (read_data[1]<<8)|read_data[2];


 //   v= ((a<<8)|(b<<1)|c)*3.3/1023;
    v= (read_data[1]<<8)|read_data[2];


 //   printf("a= 0x%02X. b= 0x%02X.  c= 0x%02X. \n", a,b,c);

//    printf("FINGER %u = %d V \n", fingerIndex,v);
//    printf("\n\n");

    return v;

    bcm2835_delay(10);

}

void ADCreader::quit()
{
    running = false;
    exit(0);
}
