#include <window.h>


#include <QApplication>

bool Compare[5];

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create the window
	Window window;
        window.showMaximized();
	window.show();
	// call the window.timerEvent function every 40 ms
	window.startTimer(10);





	// execute the application
	return app.exec();
}
