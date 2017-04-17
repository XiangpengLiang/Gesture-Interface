Gesture Interface Glove<br>
University of Glasgow<br>
Real Time Embedded Programming: Raspberry PI Assignment
=
[Demonstration video](https://youtu.be/rbo2YH-eyuY)
=
Tutor: Bernd Porr<br>
Students: Xiangpeng Liang, Zhong Lu, Chenhan Ye
-

Introduction
-
   This project aims to attach flex sensors to the glove, and drive the sensor to deform through the bending of the finger, displaying the physical input value on the screen. After calibration, simple gesture games can be realized by proofreading operation within the system. <br>
   Sampling rate: 441Hz for five sensors and 2205Hz for one sensor<br>
   Power coumption: 3.3W
 ![](http://a.hiphotos.baidu.com/image/pic/item/ac6eddc451da81cb99b299f85866d016092431aa.jpg)
 
Making it work
-
    Install: Git, xorg
    Library: bcm2835, Qwt, Qt 4.8

To clone the git repository:
-
    git clone https://github.com/pppxp/Gesture-Interface.git

To build:
-
    cd Gesture-Interaface
    qmake
    make

To run (assuming you are logged into the RPi over ssh and no X-server is running):

    startx ./Gesture

=================================

Qt is a cross platform framework for developing graphical applications, for more information please visit the links below:
* [Qt Homepage](http://qt-project.org/)
* [Qt 4.8 Class List](http://qt-project.org/doc/qt-4.8/classes.html)
* [Wikpedia](http://en.wikipedia.org/wiki/Qt_%28framework%29)
* [Signals and Slots](http://qt-project.org/doc/qt-4.8/signalsandslots.html)

Qwt is a technical widget library based on Qt, please see:
* [Qwt Hompage](http://qwt.sourceforge.net/)



