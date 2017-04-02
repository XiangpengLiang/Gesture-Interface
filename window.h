#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QPushButton>

#include <QBoxLayout>
#include "adcreader.h"

// class definition 'Window'
class Window : public QWidget
{
    // must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
    Q_OBJECT

public:
    Window(); // default constructor - called when a Window is declared without arguments

    ~Window();

    void timerEvent( QTimerEvent * );

private slots:

void handleButton();

private: 

    QwtThermo    *thermo,*finger1,*finger2,*finger3,*finger4,*finger5;
    QwtKnob *knob;
    QPushButton *quit;
    //  QwtPlot      *plot;
    //  QwtPlotCurve *curve;

    int count;
    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
    QVBoxLayout  *vLayout;  // vertical layout
    QHBoxLayout  *hLayout1,*hLayout2;  // horizontal layout
    //	ADCreader *adcreader;

    /*
  static const int plotDataSize = 100;

  // data arrays for the plot
  double xData[plotDataSize];
  double yData[plotDataSize];
*/
    double gain;

    ADCreader *adcreader;
};

#endif // WINDOW_H
