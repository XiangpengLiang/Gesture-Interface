#include "adcreader.h"
#include <QDebug>

void ADCreader::run()
{
	running = true;
	while (running) {
		qDebug() << "Tick";
        uint8_t send_data[2] = {0xC0,0x00};
        uint8_t read_data[3];

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
    bcm2835_delay(1000);
    }
        bcm2835_spi_end();
        bcm2835_close();
        return 0;

	}
}

void ADCreader::quit()
{
	running = false;
	exit(0);
}
