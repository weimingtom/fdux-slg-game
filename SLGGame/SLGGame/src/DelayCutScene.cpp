#include "delaycutscene.h"


DelayCutScene::DelayCutScene(unsigned int lasttime, CutScene* next)
:CutScene(lasttime)
{
	setNextScene(next);
}
DelayCutScene::~DelayCutScene()
{

}

bool DelayCutScene::endCutScene()
{
	if(mPassedTime >= mLastTime)
		return true;
	return false;
}
void DelayCutScene::skipCutScene()
{
	mPassedTime = mLastTime;
}
void DelayCutScene::updateCutScene(unsigned int deltaTime)
{
	mPassedTime += 10;
}