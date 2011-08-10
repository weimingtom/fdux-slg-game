#include <QtGui/QApplication>
#include "IIRoot.h"
#include "mainwindow.h"
#include "QTCodeSet.h"
#include "DataManager.h"
#include "LuaEngine.h"
#include "AreaManager.h"

int main(int argc, char *argv[])
{	
	try
	{
		QTCodeSet qtCodeSet;

		IIRoot* ii_root;
		ii_root=new IIRoot();

		//创建装备管理器
		DataManager *dataManager;
		dataManager = new DataManager(true);

		//脚本引擎
		LuaEngine* luaEngine;
		luaEngine = new LuaEngine();

		AreaManager* areaManager;
		areaManager = new AreaManager;

		QApplication a(argc, argv);

		MainWindow w;
		ii_root->setupLog(static_cast<Ogre::LogListener*>(&w));
		if(!ii_root->setup(w.getGView()))
		{
			return -1;
		}

		w.initValue();
		w.show();
		w.startTimer(10);
		return a.exec();
	}
	catch (Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
	}
}
