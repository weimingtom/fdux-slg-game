#include "Core.h"

int main()
{
	Core root;
	if (!root.initialize())
	{
		return -1;
	}
	root.run();

	return 0;
}

