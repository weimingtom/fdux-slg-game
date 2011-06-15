#include "BillboardManager.h"

#include "GUIBillBoard.h"

#include "GUISquadBillBoard.h"

#include "Core.h"

#define MARGIN_WIDTH 30
#define MARGIN_HEIGHT 50

BillboardManager::BillboardManager(Ogre::Camera* camera):mCamera(camera)
{
	mWidth=Core::getSingletonPtr()->mWindow->getWidth();
	mHeight=Core::getSingletonPtr()->mWindow->getHeight();
}

BillboardManager::~BillboardManager(void)
{
}

void BillboardManager::update()
{
	Ogre::Matrix4 viewMatrix = mCamera->getViewMatrix();
	Ogre::Matrix4 projectMatrix = mCamera->getProjectionMatrixWithRSDepth();
	Ogre::Matrix4 eyeMatrix = (Ogre::Matrix4(0.5,0,0,0.5, 0,-0.5,0,0.5, 0,0,1,0, 0,0,0,1)*projectMatrix*viewMatrix);


	for (std::vector<GUIBillBoard*>::iterator it=mBillBoards.begin();it!=mBillBoards.end();it++)
	{
		Ogre::Vector4 v4((*it)->getPosition());
		Ogre::Vector4 temp = eyeMatrix*v4;
	
		Ogre::Vector3 ScreenPos = Ogre::Vector3(temp.x/temp.w,temp.y/temp.w,temp.z/temp.w);

		Ogre::Vector2 Pos(ScreenPos.x*mWidth,ScreenPos.y*mHeight);
		
		if(Pos.x<MARGIN_WIDTH || Pos.y<MARGIN_HEIGHT || Pos.x>mWidth-MARGIN_WIDTH || Pos.y>mHeight-MARGIN_HEIGHT)
		{
			if ((*it)->mInScreen)
			{
				(*it)->mInScreen=false;
				(*it)->hideScene();
			}
		}
		else
		{
			if (!(*it)->mInScreen)
			{
				(*it)->mInScreen=true;
				(*it)->showScene("");
			}

			(*it)->update(Pos);
		}
	}
}

void BillboardManager::addBillBoard(GUIBillBoard* billBoard )
{
	mBillBoards.push_back(billBoard);
}

void BillboardManager::destroyBillBoard( GUIBillBoard* billBoard )
{
	for (std::vector<GUIBillBoard*>::iterator it=mBillBoards.begin();it!=mBillBoards.end();it++)
	{
		if ((*it)==billBoard)
		{
			delete (*it);
			mBillBoards.erase(it);
			break;
		}
	}
}


