#include "delaycutscence.h"


DelayCutScence::DelayCutScence(unsigned int lasttime, CutScence* next)
:CutScence(lasttime)
{
	setNextScence(next);
}
DelayCutScence::~DelayCutScence()
{

}

bool DelayCutScence::endCutScence()
{
	if(mPassedTime >= mLastTime)
		return true;
	return false;
}
void DelayCutScence::skipCutScence()
{
	mPassedTime = mLastTime;
}
void DelayCutScence::updateCutScence(unsigned int deltaTime)
{
	mPassedTime += 10;
}