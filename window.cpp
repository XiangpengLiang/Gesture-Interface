#include "window.h"
#include "adcreader.h"

#include <QDebug>

#include <cmath>  // for sine stuff


#include<QDebug>



Window::Window()
{
//    image1.load(":/hand2.png");

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

    finger1->setRange(2.45, 3.2);
    finger2->setRange(2.45, 3.2);
    finger3->setRange(2.45, 3.2);
    finger4->setRange(2.45, 3.2);
    finger5->setRange(2.45, 3.2);


    finger1->show();
    finger2->show();
    finger3->show();
    finger4->show();
    finger5->show();


    quit= new QPushButton("Quit", this);
    connect(quit, SIGNAL (released()), this, SLOT (handleButton()));

    Guessing= new QPushButton("Guessing", this);
    connect(Guessing, SIGNAL (released()), this, SLOT (openGuessing()));

    Open = new QPushButton("Open Fingers", this);
    connect(Open, SIGNAL (released()), this, SLOT (OpenFingers()));

    Close = new QPushButton("Close Fingers", this);
    connect(Close, SIGNAL (released()), this, SLOT (CloseFingers()));

    label = new QLabel(this);
    label->setText("Please open your fingers and click Open");

    // set up the layout
    vLayout = new QVBoxLayout;
    Buttons = new QVBoxLayout;
    hLayout1 = new QHBoxLayout;
    DataDisplay = new QHBoxLayout;
    hLayout2 = new QHBoxLayout;


    Calibration = new QGroupBox(tr("Calibration"));
    CalibrationLayout = new QVBoxLayout;
    CalibrationLayout->addWidget(Open,4);
    CalibrationLayout->addWidget(Close,4);
    CalibrationLayout->addWidget(label,1);
    Calibration->setLayout(CalibrationLayout);

    Buttons->addWidget(Calibration);
    Buttons->addWidget(Guessing);
    Buttons->addWidget(quit);


    hLayout1->addWidget(knob);


    DataDisplay->addWidget(finger1,1);
    DataDisplay->addWidget(finger2,2);
    DataDisplay->addWidget(finger3,3);
    DataDisplay->addWidget(finger4,1);
    DataDisplay->addWidget(finger5,2);


    hLayout2->addLayout(DataDisplay,5);
    hLayout2->addLayout(Buttons,1);

//    hLayout2->setStretchFactor(DataDisplay,3);
//    hLayout2->setStretchFactor(Buttons,1);
    DataDisplay->setSpacing(100);
    hLayout2->setSpacing(150);

//    quit->resize(200,50);
//    Guessing->resize(200,50);

    // hLayout->addWidget(plot);


    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);


    setLayout(vLayout);


    adcreader = new ADCreader();
    adcreader->start();

//    guessingWindow = new guessing;
}



void Window::timerEvent( QTimerEvent * )
{

    finger1->setValue(adcreader->FingerData[0]*3.3/1023);
    finger2->setValue(adcreader->FingerData[1]*3.3/1023);
    finger3->setValue(adcreader->FingerData[2]*3.3/1023);
    finger4->setValue(adcreader->FingerData[3]*3.3/1023);
    finger5->setValue(adcreader->FingerData[4]*3.3/1023);

    for (int i=0;i<5;i++){
    Compare[i]= adcreader->FingerData[i]  >  FingerThreshold[i];

//    printf("FingerData %u = %d  \n", i,adcreader->FingerData[i]);
//    printf("FingerThreshold %u = %d  \n", i,FingerThreshold[i]);
//    printf("Compare %u = %d  \n\n", i,Compare[i]);

    }

}

void Window::handleButton(){

        exit(-1);
}

void Window::openGuessing(){
//    this->Close();
    guessing *guessingWindow = new guessing;
    guessingWindow->showMaximized();
    guessingWindow->show();
    guessingWindow->startTimer(300);
//    guessingWindow.exec();
//    this->show();

}


void Window::OpenFingers(){
    for (int i=0;i<5;i++){
    OpenFingersData[i]=adcreader->FingerData[i];
    }

}

void Window::CloseFingers(){
    for (int i=0;i<5;i++){
    FingerThreshold[i]=(adcreader->FingerData[i]+OpenFingersData[i])/2;
    printf("CloseFingersData %u = %d  \n", i,adcreader->FingerData[i]);
    printf("OpenFingersData %u = %d  \n", i,OpenFingersData[i]);
    printf("FingerThreshold %u = %d  \n\n", i,FingerThreshold[i]);

    }

}



Window::~Window() {
    // tells the thread to no longer run its endless loop
    adcreader->quit();
    // wait until the run method has terminated
    adcreader->wait();
    delete adcreader;
}




/*
void Window::paintEvent(QPaintEvent *)
{
    //void QPainter::drawPixmap(int x, int y, int width, int height, const QPixmap &pixmap)
    QPainter painter(this);
    painter.drawPixmap(10,10,200,200,image1);
}
*/








