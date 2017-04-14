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
    //    float voltage[5];
    uint16_t FingerData[5];
private:
    bool running;

    uint16_t getVoltage(uint8_t fingerIndex);


};

#endif
