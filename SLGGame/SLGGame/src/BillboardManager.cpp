#include "BillboardManager.h"

#include "GUIBillBoard.h"

#include "GUISquadBillBoard.h"

#include "Core.h"

#define OFFEST_X 70
#define OFFEST_Y 150

BillboardManager::BillboardManager(Ogre::Camera* camera):mCamera(camera)
{
	mWidth=Core::getSingletonPtr()->mWindow->getWidth();
	mHeight=Core::getSingletonPtr()->mWindow->getHeight();
}

BillboardManager::~BillboardManager(void)
{
}

void BillboardManager::update(unsigned int deltaTime)
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
		
		Pos.x-=OFFEST_X;
		Pos.y-=OFFEST_Y;

		if(Pos.x>0 && Pos.y>0 && Pos.x<mWidth && Pos.y<mHeight)
		{
			(*it)->showScene("");

			(*it)->setMarginalValue(Pos.y,mHeight-Pos.y,Pos.x,mWidth-Pos.x);

			(*it)->update(Pos,deltaTime);
		}
		else
		{
			(*it)->hideScene();
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


