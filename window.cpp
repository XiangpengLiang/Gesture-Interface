#include "window.h"
#include "adcreader.h"


#include <cmath>  // for sine stuff


#include<QDebug>



Window::Window()
{

    knob = new QwtKnob;
    // set up the gain knob
    knob->setValue(5);


    finger1 = new QwtThermo;
    finger2 = new QwtThermo;
    finger3 = new QwtThermo;
    finger4 = new QwtThermo;
    finger5 = new QwtThermo;

    finger1->setFillBrush( QBrush(Qt::blue) );
    finger2->setFillBrush( QBrush(Qt::red) );
    finger3->setFillBrush( QBrush(Qt::green) );
    finger4->setFillBrush( QBrush(Qt::red) );
    finger5->setFillBrush( QBrush(Qt::green) );

    finger1->setRange(2.5, 3.3);
    finger2->setRange(2.5, 3.5);
    finger3->setRange(2.5, 3.5);
    finger4->setRange(2.5, 3.5);
    finger5->setRange(2.5, 3.5);

    //  finger1->setRange(2,200);
    finger1->show();
    finger2->show();
    finger3->show();
    finger4->show();
    finger5->show();

    finger1->setValue(50 );


    quit= new QPushButton("quit", this);
    quit->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(quit, SIGNAL (released()), this, SLOT (handleButton()));




    // set up the layout - knob above thermometer
    vLayout = new QVBoxLayout;
//    vLayout->addWidget(knob);
//    vLayout->addWidget(finger1);
//    vLayout->addWidget(finger2);
//    vLayout->addWidget(finger3);
//    vLayout->addWidget(finger4);
//    vLayout->addWidget(finger5);


    // plot to the left of knob and thermometer
    hLayout1 = new QHBoxLayout;
    hLayout2 = new QHBoxLayout;
    hLayout1->addWidget(knob);
    hLayout2->addWidget(finger1);
    hLayout2->addWidget(finger2);
    hLayout2->addWidget(finger3);
    hLayout2->addWidget(finger4);
    hLayout2->addWidget(finger5);
    hLayout1->addWidget(quit);
    // hLayout->addWidget(plot);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);


    adcreader = new ADCreader();
    adcreader->start();

}



void Window::timerEvent( QTimerEvent * )
{
//    double inVal =(5 * sin( M_PI * count/50.0 )+10)*10;
//    ++count;

    /*
   memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
  yData[plotDataSize-1] = inVal;
  curve->setSamples(xData, yData, plotDataSize);
  plot->replot();

*/
    // set the thermometer value
    //  thermo->setValue(inVal);
    //knob->setValue(inVal);

    //  double xx;
    //       xx = knob->value();

    finger1->setValue(adcreader->voltage1);
    finger2->setValue(adcreader->voltage2);
    finger3->setValue(adcreader->voltage3);
    finger4->setValue(adcreader->voltage4);
    finger5->setValue(adcreader->voltage5);

    qDebug()<<knob->value();
}

void Window::handleButton(){
//    app->exit(0);
//    QApplication::setQuitOnLastWindowClosed(true);
//    QCoreApplication::exit();
        exit(-1);
}


Window::~Window() {
    // tells the thread to no longer run its endless loop
    adcreader->quit();
    // wait until the run method has terminated
    adcreader->wait();
    delete adcreader;
}












