#pragma once

#include <Ogre.h>
#include <MyGUI.h>
#include <iisingleton.hpp>

using namespace izayoi; 

class BillboardManager:public IISingleton<BillboardManager>
{
public:
	BillboardManager(void);
	~BillboardManager(void);

	Ogre::BillboardSet* getBillboardSet();

	MyGUI::ImageBox* BaseWidget;
	int mIndex;
	int mRow;
	int mColumn;
};
