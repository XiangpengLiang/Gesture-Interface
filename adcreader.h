#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "bcm2835"

class ADCreader : public QThread
{
public:
	ADCreader() {running = 0;};
	void quit();
	void run();
    float voltage;
private:
	bool running;

};

#endif
