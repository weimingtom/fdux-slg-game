#include "Core.h"

#ifdef NDEBUG
	#include "CrashRpt.h"
	#include <tchar.h>
	#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
	#define VER_Crash _T("0.1d")
	#define VER_Subject _T("ForgottenBattlefield 0.1d Error Report")
#endif

int main(int argc,char* argv[])
{
	#ifdef NDEBUG
		CR_INSTALL_INFO info;
		memset(&info, 0, sizeof(CR_INSTALL_INFO));
		info.cb = sizeof(CR_INSTALL_INFO);             // Size of the structure
		info.pszAppName = _T("ForgottenBattlefield"); // App name
		info.pszAppVersion = VER_Crash ;              // App version
		info.pszEmailSubject = VER_Subject; // Email subject
		info.pszEmailTo = _T("fduxslggame@163.com");      // Email recipient address
		info.pszSmtpProxy = _T("smtp.163.com:25");
		info.pszSmtpLogin = _T("fduxslggame@163.com");
		info.pszSmtpPassword = _T("680068");

		// Install crash handlers
		int nInstResult = crInstall(&info);            
		assert(nInstResult==0);

		crAddFile2(L"log.txt",L"log.txt",L"Ogre",CR_AF_TAKE_ORIGINAL_FILE);
		crAddFile2(L"MyGUI.log",L"MyGUI.log",L"Mygui",CR_AF_TAKE_ORIGINAL_FILE);
	#endif

	bool isFullScene=false;
	if (argc==1)
	{
		isFullScene=false;
	}
	else if(argc==2)
	{
		if (argv[1]="-FullScene")
		{
			isFullScene=true;
		}
	}

	Core root;
	if (!root.initialize(isFullScene))
	{
		return -1;
	}
	root.run();

	#ifdef NDEBUG
		int nUninstRes = crUninstall(); // Uninstall exception handlers
		assert(nUninstRes==0);
		nUninstRes;
	#endif

	return 0;
}

