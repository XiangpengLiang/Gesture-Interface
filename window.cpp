#include "window.h"
#include "adcreader.h"
#include <QDebug>

Window::Window()
{
    //    image1.load(":/hand2.png");

    //Set up the display components
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

    finger1->setRange(2.45, 3);
    finger2->setRange(2.45, 3);
    finger3->setRange(2.45, 3);
    finger4->setRange(2.45, 3);
    finger5->setRange(2.45, 3);


    finger1->show();
    finger2->show();
    finger3->show();
    finger4->show();
    finger5->show();


    //Set up the bottons
    quit= new QPushButton("Quit", this);
    connect(quit, SIGNAL (released()), this, SLOT (handleButton()));

    Guessing= new QPushButton("Rock-paper-scissors", this);
    connect(Guessing, SIGNAL (released()), this, SLOT (openGuessing()));
    //   Guessing->setEnable(false);

    Open = new QPushButton("Open Fingers", this);
    connect(Open, SIGNAL (released()), this, SLOT (OpenFingers()));

    Close = new QPushButton("Close Fingers", this);
    connect(Close, SIGNAL (released()), this, SLOT (CloseFingers()));

    //Set up the labels
    label = new QLabel(this);
    label->setText("Please OPEN your fingers and click 'Open finger'");
    label->setWordWrap(true);
    label->adjustSize();

    QFont Ft,Ff;
    Ft.setPointSize(20);
    Ft.setPointSize(15);
    Title = new QLabel(this);
    Title->setText("Gesture Interface Glove");
    Title->setTextFormat(Qt::RichText);
    Title->setAlignment(Qt::AlignCenter);
    Title->setFont(Ft);

    Uniname = new QLabel(this);
    Uniname->setText("University of Glasgow");
    Uniname->setAlignment(Qt::AlignCenter);
    Uniname->setFont(Ft);

    author = new QLabel(this);
    author->setText("Xiangpeng Liang, Zhong Lu, Chenhan Ye");
    author->setAlignment(Qt::AlignCenter);

    Thumb = new QLabel(this);
    Thumb->setText("Thumb");
    Thumb->setAlignment(Qt::AlignBottom);
    Thumb->setFont(Ff);
    Thumb->adjustSize();
    //    Thumb->resize(100,100);

    Forefinger = new QLabel(this);
    Forefinger->setText("Forefinger");
    Forefinger->setAlignment(Qt::AlignBottom);
    Forefinger->setFont(Ff);
    Forefinger->adjustSize();

    Middlefinger = new QLabel(this);
    Middlefinger->setText("Middlefinger");
    Middlefinger->setAlignment(Qt::AlignBottom);
    Middlefinger->setFont(Ff);
    Middlefinger->adjustSize();

    Ringfinger = new QLabel(this);
    Ringfinger->setText("Ringfinger");
    Ringfinger->setAlignment(Qt::AlignBottom);
    Ringfinger->setFont(Ff);
    Ringfinger->adjustSize();

    Littlefinger = new QLabel(this);
    Littlefinger->setText("Littlefinger");
    Littlefinger->setAlignment(Qt::AlignBottom);
    Littlefinger->setFont(Ff);
    Thumb->adjustSize();



    // set up the layout
    vLayout = new QVBoxLayout;
    Buttons = new QVBoxLayout;
    titleLayout = new QVBoxLayout;
    DataDisplay = new QGridLayout;
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

    titleLayout->addWidget(Title);
    titleLayout->addWidget(Uniname);
    titleLayout->addWidget(author);

    DataDisplay->addWidget(Thumb,1,0);
    DataDisplay->addWidget(Forefinger,1,1);
    DataDisplay->addWidget(Middlefinger,1,2);
    DataDisplay->addWidget(Ringfinger,1,3);
    DataDisplay->addWidget(Littlefinger,1,4);

    DataDisplay->addWidget(finger1,0,0);
    DataDisplay->addWidget(finger2,0,1);
    DataDisplay->addWidget(finger3,0,2);
    DataDisplay->addWidget(finger4,0,3);
    DataDisplay->addWidget(finger5,0,4);

    hLayout2->addLayout(DataDisplay,5);
    hLayout2->addLayout(Buttons,1);


    DataDisplay->setSpacing(80);
    hLayout2->setSpacing(100);


    vLayout->addLayout(titleLayout);
    vLayout->addLayout(hLayout2);


    setLayout(vLayout);



    //Run SPI
    adcreader = new ADCreader();
    adcreader->start();
}



void Window::timerEvent( QTimerEvent * )  //Display the value and do compare every 10ms
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

void Window::openGuessing()  //Open the Scissor-Rock-paper window
{
    //    this->Close();
    guessing *guessingWindow = new guessing;
    guessingWindow->showMaximized();
    guessingWindow->show();
    guessingWindow->startTimer(300);
    //    this->show();

}


void Window::OpenFingers()   //Calibration: Collect the single when fingers open
{
    for (int i=0;i<5;i++){
        OpenFingersData[i]=adcreader->FingerData[i];
    }
    label->setText("Please CLOSE your fingers and click 'Close finger'");

}

void Window::CloseFingers()  //Calibration: Collect the single when fingers close
{
    for (int i=0;i<5;i++){
        FingerThreshold[i]=(adcreader->FingerData[i]+OpenFingersData[i])/2;
        printf("CloseFingersData %u = %d  \n", i,adcreader->FingerData[i]);
        printf("OpenFingersData %u = %d  \n", i,OpenFingersData[i]);
        printf("FingerThreshold %u = %d  \n\n", i,FingerThreshold[i]);

    }

    //Make sure the Calbration is correct
    if (adcreader->FingerData[2]>OpenFingersData[2])
    {
        label->setText("Calibration sucessful");
        //       Guessing->setEnable(true);
    }
    else
    {
        label->setText("Calibration unsucessful.　Please try again, OPEN your fingers and click 'Open finger'");
    }
}



Window::~Window()
{
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








