#include "cutscene.h"

CutScene::CutScene(unsigned int lasttime)
{
	mLastTime = lasttime;
	mPaused = false;
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
	if(!endCutScene())
		return false;
	if(mNextScene)
		return mNextScene->end();
	else
		return true;
}

void CutScene::update(unsigned int deltaTime)
{
	if(!mPaused)
	{
		if(!endCutScene())
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
				mNextScene->update(deltaTime);
		}
	}
}

void CutScene::setNextScene(CutScene* next)
{
	mNextScene = next;
}