#include "scripteditor.h"
#include <QtGui/QApplication>

#include "QTCodeSet.h"
#include "OgreCore.h"

#include "LuaSystem.h"

int main(int argc, char *argv[])
{
	try
	{
		QTCodeSet qtCodeSet;
		QApplication a(argc, argv);
		ScriptEditor w;
		OgreCore root;
		if (!root.setup())
		{
			return -1;
		}

		//while(1)
		//{
		//	root.RenderingFrame();
		//}
		root.mLuaSystem->registerListener(&w);
		Ogre::WindowEventUtilities::addWindowEventListener(OgreCore::getSingletonPtr()->mWindow,&w);
		w.show();
		w.startTimer(1);
		return a.exec();
	}
	catch (Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
	}

}
