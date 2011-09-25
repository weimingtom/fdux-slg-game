#include "feedback.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Feedback mainWindow;
	mainWindow.show();

	return app.exec();
}
