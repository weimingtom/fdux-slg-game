#include "skilleditor.h"
#include <QtGui/QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include "IIRoot.h"

int main(int argc, char *argv[])
{
	try
	{
		IIRoot* ii_root;
		ii_root=new IIRoot();

		QApplication app(argc, argv);

		QTranslator qtTranslator;
		qtTranslator.load("qt_zh_CN");
		app.installTranslator(&qtTranslator);

		QTranslator myappTranslator;
		myappTranslator.load("skilleditor_" + QLocale::system().name());
		app.installTranslator(&myappTranslator);


		SkillEditor w;
		ii_root->setupLog(static_cast<Ogre::LogListener*>(&w));
		if(!ii_root->setup(w.getGView()))
		{
			return -1;
		}

		w.initValue();
		w.show();
		w.startTimer(10);
		return app.exec();
	}
	catch (Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
	}
}
