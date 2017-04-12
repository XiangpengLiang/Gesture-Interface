#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>

#include <QPushButton>

#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

#include <QBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

#include "adcreader.h"
#include "guessing.h"

//extern bool Compare[5];


// class definition 'Window'


class Window : public QWidget
{
    // must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
    Q_OBJECT

public:
    Window(); // default constructor - called when a Window is declared without arguments

    ~Window();

    void timerEvent( QTimerEvent * );



    uint16_t FingerThreshold[5];

private slots:

void handleButton();
void openGuessing();
void OpenFingers();
void CloseFingers();

private: 

    QwtThermo    *thermo,*finger1,*finger2,*finger3,*finger4,*finger5;
    QwtKnob *knob;
    QPushButton *quit,*Guessing,*Open,*Close;


    int count;
    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
    QVBoxLayout  *vLayout, *Buttons,*CalibrationLayout;  // vertical layout
    QHBoxLayout  *hLayout1,*DataDisplay,*hLayout2;  // horizontal layout

    QGroupBox *Calibration;
//    QGridLayout  *hLayout2;
    double gain;

    ADCreader *adcreader;

    QPixmap image1;

    QLabel *label ;

    uint16_t OpenFingersData[5];
//    uint16_t CloseFingersData[5];

//    guessing *guessingWindow;

protected:
//        void paintEvent(QPaintEvent *);
};

#endif // WINDOW_H
