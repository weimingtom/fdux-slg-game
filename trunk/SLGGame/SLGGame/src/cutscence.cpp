#include "cutscenes.h"

CutScence::CutScence(unsigned int lasttime)
{
	mLastTime = lasttime;
	mPaused = false;
	mNextScence = 0;
	mPassedTime = 0;
}
CutScence::~CutScence()
{
	if(mNextScence)
	{
		delete mNextScence;
		mNextScence = 0;
	}
}

void CutScence::skip()
{
	skipCutScence();
}

void CutScence::skipall()
{
	skipCutScence();
	if(mNextScence)
		mNextScence->skip();
}

bool CutScence::end()
{
	if(!endCutScence())
		return false;
	if(mNextScence)
		return mNextScence->end();
	else
		return true;
}

void CutScence::update(unsigned int deltaTime)
{
	if(!mPaused)
	{
		if(!endCutScence())
		{

			if(mLastTime > 0)
			{
				mPassedTime += deltaTime;
				if(mPassedTime > mLastTime)
					skipCutScence();
				else
					updateCutScence(deltaTime);
			}
			else
				updateCutScence(deltaTime);
		}
		else
		{
			if(mNextScence)
				mNextScence->update(deltaTime);
		}
	}
}

void CutScence::setNextScence(CutScence* next)
{
	mNextScence = next;
}