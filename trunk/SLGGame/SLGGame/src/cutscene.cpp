#include "cutscene.h"

CutScene::CutScene(unsigned int lasttime)
{
	mLastTime = lasttime;
	mStarted = false;
	mEnded = false;;
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
	startCutScence();
	mStarted = true;
}

void CutScene::skip()
{
	skipCutScene();
}

void CutScene::skipall()
{
	skipCutScene();
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
	mEnded = true;
	if(mNextScene)
		return mNextScene->end();
	return true;
}
bool CutScene::endthis()
{
	if(mEnded)
		return true;
	return endCutScene();
}
void CutScene::update(unsigned int deltaTime)
{
	if(!endthis())
	{
		if(mLastTime > 0)
		{
			mPassedTime += deltaTime;
			if(mPassedTime > mLastTime)
				skipCutScene();
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
	mNextScene = next;
}