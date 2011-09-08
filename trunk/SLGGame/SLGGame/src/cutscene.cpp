#include "cutscene.h"

#include "Core.h"
#include <boost/format.hpp>

CutScene::CutScene(unsigned int lasttime)
{
	mLastTime = lasttime;
	mStarted = false;
	mEnded = false;
	mNextScene = 0;
	mPassedTime = 0;
}
CutScene::~CutScene()
{
	if(mNextScene)
	{
		delete mNextScene;
		mNextScene = 0;
	}
}

void CutScene::start()
{
	if(mStarted)
		return;
	Ogre::LogManager::getSingletonPtr()->logMessage(std::string("CutScene:Start"),Ogre::LML_NORMAL);
	startCutScence();
	mStarted = true;
}

void CutScene::skip()
{
	if(mEnded == true)
		return;
	skipCutScene();
	mEnded = true;
}

void CutScene::skipall()
{
	skip();
	if(mNextScene)
		mNextScene->skipall();
}

bool CutScene::end()
{
	if(!mStarted)
		return false;
	if(mEnded)
	{
		if(mNextScene)
			return mNextScene->end();
		return true;
	}
	if(!endCutScene())
		return false;
	Ogre::LogManager::getSingletonPtr()->logMessage(std::string("CutScene:End"),Ogre::LML_NORMAL);
	mEnded = true;
	if(mNextScene)
		return mNextScene->end();
	return true;
}
bool CutScene::endthis()
{
	if(mEnded)
		return true;
	if(endCutScene())
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(std::string("CutScene:EndThis"),Ogre::LML_NORMAL);
		return true;
	}
	return false;
}
void CutScene::update(unsigned int deltaTime)
{
	if(!mEnded)
	{
		if(mLastTime > 0)
		{
			mPassedTime += deltaTime;
			if(mPassedTime > mLastTime)
				skip();
			else
				updateCutScene(deltaTime);
		}
		else
			updateCutScene(deltaTime);
	}
	else
	{
		if(mNextScene)
		{
			mNextScene->start();
			mNextScene->update(deltaTime);
		}
	}
}

void CutScene::setNextScene(CutScene* next)
{
	if(mNextScene)
		delete mNextScene;
	mNextScene = next;
}