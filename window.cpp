#include "window.h"
#include "adcreader.h"
#include "bcm2835.h"

#include <cmath>  // for sine stuff


#include<QDebug>



Window::Window()
{
// This is a demo for a thread which can be
// used to read from the ADC asynchronously.
// At the moment it doesn't do anything else than
// running in an endless loop and which prints out "tick"
// every second.
// adcreader = new ADCreader();
// adcreader->start();


knob = new QwtKnob;
  // set up the gain knob
  knob->setValue(5);


  thermo = new QwtThermo;
  thermo->setFillBrush( QBrush(Qt::blue) );
  thermo->setRange(0, 200);
//  thermo->setRange(2,200);
  thermo->show();
 thermo->setValue(50 );

 /*

   for( int index=0; index<plotDataSize; ++index )
  {
    xData[index] = index;
    yData[index] = gain * sin( M_PI * index/50 );
  }


  curve = new QwtPlotCurve;
  plot = new QwtPlot;
  // make a plot curve from the data and attach it to the plot
  curve->setSamples(xData, yData, plotDataSize);
  curve->attach(plot);


  plot->replot();
  plot->show();
*/

 // set up the layout - knob above thermometer
 vLayout = new QVBoxLayout;
 vLayout->addWidget(knob);
  vLayout->addWidget(thermo);


    // plot to the left of knob and thermometer
  hLayout = new QHBoxLayout;
  hLayout->addLayout(vLayout);
 // hLayout->addWidget(plot);



  setLayout(hLayout);


    adcreader = new ADCreader();
    adcreader->start();

}



void Window::timerEvent( QTimerEvent * )
{
  double inVal =(5 * sin( M_PI * count/50.0 )+10)*10;
  ++count;

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

  thermo->setValue(voltage);
  qDebug()<<knob->value();
}




Window::~Window() {
// tells the thread to no longer run its endless loop
 adcreader->quit();
// wait until the run method has terminated
 adcreader->wait();
 delete adcreader;
}








 
 
 
 
