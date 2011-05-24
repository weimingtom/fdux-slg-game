#include "SquadDeadCutScene.h"
#include "SquadGraphics.h"
#include "SquadGrapManager.h"

SquadDeadCutScene::SquadDeadCutScene(unsigned int squadgpid,int deadnum)
{
	mSquad=SquadGrapManager::getSingletonPtr()->getSquad(squadgpid);
	mDeadNum = deadnum;
	mCurNum = -1;
}
SquadDeadCutScene::~SquadDeadCutScene()
{

}
void SquadDeadCutScene::startCutScence()
{

}
bool SquadDeadCutScene::endCutScene()
{
	return mCurNum == mDeadNum;
}
void SquadDeadCutScene::skipCutScene()
{

}
void SquadDeadCutScene::updateCutScene(unsigned int deltaTime)
{
	if(mSquad->isDeathOver())
	{
		mCurNum++;
		if(mCurNum < mDeadNum)
		{
			mSquad->setDeath();
		}
	}
}