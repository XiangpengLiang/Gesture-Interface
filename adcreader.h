#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "bcm2835.h"

class ADCreader : public QThread
{
public:
	ADCreader() {running = 0;};
	void quit();
	void run();
    float voltage1,voltage2,voltage3,voltage4,voltage5;
private:
	bool running;

        float getVoltage(uint8_t fingerIndex);

};

#endif
