// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
#include <bcm2835.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    
    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent

while(1){
    uint8_t send_data[2] = {0xC0,0x00};
    uint8_t read_data[3];

    bcm2835_spi_transfernb(send_data,read_data,3);

    printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.  0x%02X.  0x%02X \n", send_data[0], read_data[0],read_data[1],read_data[2]);
 
uint8_t a,b,c;
uint16_t v;
float voltage;

a= ((read_data[0]<<1) + (read_data[1]>>7));
b= (((read_data[1]<<1) + (read_data[2]>>7)))&0x7F;
c= read_data[2]>>7;
v= ((a<<8)|(b<<1)|c);
voltage= v*3.3/1023;

printf("a= 0x%02X. b= 0x%02X.  c= 0x%02X. \n", a,b,c);

printf("voltage = %fV \n", voltage);
      printf("\n\n");
bcm2835_delay(1000);
}
    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}