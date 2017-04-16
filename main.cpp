// University of Glasgow
// Real Time Embedded Programming
// Raspberry PI Assignment
// Name: Xiangpeng Liang; Zhong Lu; Chenhan Ye
// Data:16/04/2017

/*
Attach the glove to the flex sensor, and drive the sensor
 to deform through the bending of the finger, displaying
the physical input value on the screen. Then, simple gesture
 games can be realized by proofreading operation within
the system.
*/

#include <window.h>
#include <QApplication>

bool Compare[5];

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // create the window
    Window window;
    window.showMaximized();
    window.show();
    // call the window.timerEvent function every 10 ms
    window.startTimer(10);

    // execute the application
    return app.exec();
}
