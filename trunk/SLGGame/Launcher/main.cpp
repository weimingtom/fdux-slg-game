#include "launcher.h"
#include "update.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	Launcher w;
	update u(NULL,&w);
	u.show();
	return a.exec();
}
