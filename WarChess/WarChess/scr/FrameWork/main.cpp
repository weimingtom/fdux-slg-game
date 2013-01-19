#include <QtGui/QApplication>
#include "IIRoot.h"
#include "mainwindow.h"
#include "QTCodeSet.h"
#include "DataManager.h"
#include "LuaEngine.h"
#include "AreaManager.h"

#ifdef NDEBUG
#include "CrashRpt.h"
#include <tchar.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

int main(int argc, char *argv[])
{	

#ifdef NDEBUG
	CR_INSTALL_INFO info;
	memset(&info, 0, sizeof(CR_INSTALL_INFO));
	info.cb = sizeof(CR_INSTALL_INFO);             // Size of the structure
	info.pszAppName =  (WCHAR *)(L"地编"); // App name
	info.pszAppVersion =  (WCHAR *)(L"1.0.1");              // App version
	info.pszEmailSubject = (WCHAR *) (L"地编 1.0.1 错误报告"); // Email subject
	info.pszEmailTo =  (WCHAR *)(L"chuangludeng@gmail.com");      // Email recipient address

	// Install crash handlers
	int nInstResult = crInstall(&info);            
	assert(nInstResult==0);

	crAddFile2(L"log.txt",L"log.txt",L"Ogre",CR_AF_TAKE_ORIGINAL_FILE);
	crAddFile2(L"MyGUI.log",L"MyGUI.log",L"Mygui",CR_AF_TAKE_ORIGINAL_FILE);
#endif

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
		//ii_root->setupLog(static_cast<Ogre::LogListener*>(&w));
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

#ifdef NDEBUG
	int nUninstRes = crUninstall(); // Uninstall exception handlers
	assert(nUninstRes==0);
	nUninstRes;
#endif
}
