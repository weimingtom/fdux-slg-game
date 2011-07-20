#pragma once

#include <Ogre.h>

#include <iisingleton.hpp>

#include <vector>

#include "GUIBillBoard.h"

using namespace izayoi; 

class BillboardManager:public IISingleton<BillboardManager>
{
public:
	BillboardManager(Ogre::Camera* camera);
	~BillboardManager(void);

	void update(unsigned int deltaTime);

	void addBillBoard(GUIBillBoard* billBoard );

	void destroyBillBoard(GUIBillBoard* billBoard);

private:
	std::vector<GUIBillBoard*> mBillBoards;

	Ogre::Camera* mCamera;

	int mWidth;
	int mHeight;

};
