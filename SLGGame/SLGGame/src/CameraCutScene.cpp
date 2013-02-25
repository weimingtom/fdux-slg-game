#include "CameraCutScene.h"

#include "CameraContral.h"
#include "Terrain.h"

#include "Core.h"

CameraCutScene::CameraCutScene(int gridx,int gridy,bool moveto):mGridX(gridx),mGridY(gridy),mMoveTo(moveto),mNodeAnimation(NULL),mNodeAnimationState(NULL),mNode(NULL)
{
	
}

CameraCutScene::~CameraCutScene( void )
{

}

void CameraCutScene::startCutScence()
{
	float wx;
	float wy;
	Terrain::getSingletonPtr()->getWorldCoords(mGridX,mGridY,wx,wy);
	if(!mMoveTo)
	{
		CameraContral::getSingleton().moveCameraTo(wx,wy);
	}
	else
	{
		mNode=Core::getSingletonPtr()->mSceneMgr->getRootSceneNode()->createChildSceneNode("CameraCutScene");
		float x,y;
		CameraContral::getSingletonPtr()->getCameraXY(x,y);
		mNode->setPosition(Ogre::Vector3(x,0,y));
		mNodeAnimation = Core::getSingletonPtr()->mSceneMgr->createAnimation("CameraCutScene_Ani",2);
		mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
		Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(0,mNode);

		Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
		kf->setTranslate(Ogre::Vector3(x,0,y));

		kf=track->createNodeKeyFrame(2);
		kf->setTranslate(Ogre::Vector3(wx,0,wy));

		mNodeAnimationState = Core::getSingletonPtr()->mSceneMgr->createAnimationState("CameraCutScene_Ani");

		mNodeAnimationState->setLoop(false);
		mNodeAnimationState->setEnabled(true);

		mIsOver=false;
	}
}

bool CameraCutScene::endCutScene()
{
	if(!mMoveTo)
	{
		return true;
	}
	else
	{
		if(mIsOver)
		{
			clear();
			return true;
		}
		else
		{
			return false;
		}

	}
}

void CameraCutScene::skipCutScene()
{
	if (mMoveTo)
	{
		if (mStarted)
		{
			float wx;
			float wy;
			Terrain::getSingletonPtr()->getWorldCoords(mGridX,mGridY,wx,wy);
			CameraContral::getSingleton().moveCameraTo(wx,wy);
			clear();
		}
	}
}

void CameraCutScene::clear()
{
	if (mNodeAnimationState!=NULL)
	{
		Core::getSingletonPtr()->mSceneMgr->destroyAnimationState(mNodeAnimationState->getAnimationName());
		mNodeAnimationState=NULL;

	}

	if (mNodeAnimation!=NULL)
	{
		Core::getSingletonPtr()->mSceneMgr->destroyAnimation(mNodeAnimation->getName());
		mNodeAnimation=NULL;
	}

	mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());

}

void CameraCutScene::updateCutScene( unsigned int deltaTime )
{
	if (mNodeAnimationState!=NULL)
	{
		if (mNodeAnimationState->getTimePosition() >= mNodeAnimationState->getLength())
		{
			mIsOver=true;
		}
		else
		{
			mNodeAnimationState->addTime(deltaTime/1000.0f);

			Ogre::Vector3 p=mNode->getPosition();
			CameraContral::getSingletonPtr()->moveCameraTo(p.x,p.z);
		}
	}
}
