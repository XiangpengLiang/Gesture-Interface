# Qt project file - qmake uses his to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

TARGET = Gesture

LIBS += -lm -lqwt

#INCLUDEPATH += "/usr/qwt-6.1.3/include"
#LIBS += -L"/usr/qwt-6.1.3/lib"
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/=qwt-6.1.3/lib

HEADERS += window.h adcreader.h bcm2835.h

SOURCES += main.cpp window.cpp adcreader.cpp bcm2835.c
