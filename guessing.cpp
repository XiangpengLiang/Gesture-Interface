//#include "window.h"
#include"guessing.h"
#include <QDebug>


guessing::guessing()
{
    paper.load(":/paper.png");
    scissor.load(":/scissor.png");
    rock.load(":/rock.png");
    dog.load(":/dog.png");
    boom.load(":/boom.png");

    Quit= new QPushButton("Quit", this);
    connect(Quit, SIGNAL (released()), this, SLOT (handleButton()));

//    adcreader2 = new ADCreader();
//    adcreader2->start();
//     CtrlWindow = new Window;
}


void guessing::paintEvent(QPaintEvent *)
{

    QPainter painter(this);


    uint8_t result = Compare[0]<<4|Compare[1]<<3|Compare[2]<<2|Compare[3]<<1|Compare[4];

    switch(result)
    {
    case 0:
    {
        painter.drawPixmap(100,100,500,500,scissor);
        qDebug()<<"scissor";
        break;
    }
    case 19:
    {
        painter.drawPixmap(100,100,500,500,rock);
        qDebug()<<"rock";
        break;
    }
    case 27:
    {
        painter.drawPixmap(100,100,500,500,boom);
        qDebug()<<"boom";
        break;
    }
    case 31:
    {
        painter.drawPixmap(100,100,500,500,paper);
        qDebug()<<"rock";
        break;
    }
    default:
    {
        painter.drawPixmap(100,100,500,500,dog);
        qDebug()<<"dog";
    }
    }
}

/*
guessing::~guessing() {

    delete guessing;
}
*/


void guessing::handleButton(){

//       CtrlWindow->guessingWindow.close();
//this->killTimer();
this->close();
}


void guessing::timerEvent( QTimerEvent * )
{

//    CtrlWindow->FingerThreshold[4]=100;
    for (int i=0;i<5;i++)
    printf("Compare %u = %d  \n", i,Compare[i]);

 //   QPainter painter(this);
    static uint8_t result;
    static uint8_t shift;

    result = Compare[0]<<4|Compare[1]<<3|Compare[2]<<2|Compare[3]<<1|Compare[4];

    printf("result = %d  \n\n", result);

    if (result != shift)
    {
        guessing::update();
        shift = result;
        qDebug()<<"Tick";
    }



}

 //   qDebug()<<knob->value();



guessing::~guessing()
{


}
