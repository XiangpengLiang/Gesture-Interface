#include "adcreader.h"
#include <QDebug>
#include "bcm2835.h"


//SPI with MCP3008 to get the data
void ADCreader::run()
{
    running = true;

    bcm2835_init();
    bcm2835_spi_begin();

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096); //4096 = 61.03515625kHz on Rpi2, 97.65625kHz on RPI3
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    while (running) {

        for (int i=0;i<5;i++){
            FingerData[i]=getVoltage(i);  //5 finger data are stored in FingerData[]

        }
        bcm2835_delay(20);  //for measuring sampling rate
    }
    bcm2835_spi_end();
    bcm2835_close();
}

uint16_t ADCreader::getVoltage(uint8_t fingerIndex)
{
    char send_data[3] = {0x01,0x80,0x00};

    const char Address[5] = {0x80,0xA0,0xC0,0xE0,0xF0};  //CH0, CH2, CH4, CH6,CH7

    static char read_data[3];

    uint16_t v;

    if(fingerIndex<6)

        send_data[1] = Address[fingerIndex];

    bcm2835_spi_transfernb(send_data,read_data,3);

    v= (read_data[1]<<8)|read_data[2];  //Calculate the 16 bits voltage data

    //    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.  0x%02X.  0x%02X \n", send_data[0], read_data[0],read_data[1],read_data[2]);
    //   printf("a= 0x%02X. b= 0x%02X.  c= 0x%02X. \n", a,b,c);
    //    printf("FINGER %u = %d V \n", fingerIndex,v);
    //    printf("\n\n");

    return v;

    bcm2835_delayMicroseconds(300);

}

void ADCreader::quit()
{
    running = false;
    exit(0);
}
