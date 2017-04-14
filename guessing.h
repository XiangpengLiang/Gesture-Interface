#ifndef GUESSING_H
#define GUESSING_H
//#include "window.h"
#include "adcreader.h"

#include <QMainWindow>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

extern bool Compare[5];

class Window;

class guessing : public QWidget
{
    Q_OBJECT

public:

    guessing();

    ~guessing();

    void timerEvent( QTimerEvent * );

private slots:

    void handleButton();

private:

    //   Window *CtrlWindow;
    QPixmap paper, scissor, rock, boom,dog;
    QPushButton *Quit;

    //    QPainter painter(this);
    //    ADCreader *adcreader2;

    //    bool Compare[5];


protected:
    void paintEvent(QPaintEvent *);


};


#endif // GUESSING_H
