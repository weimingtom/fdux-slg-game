#include "Core.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
int main(int argc,char* argv[])
{
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

	return 0;
}

