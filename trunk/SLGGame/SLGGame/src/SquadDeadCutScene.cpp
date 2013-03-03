#include "SquadDeadCutScene.h"
#include "SquadGraphics.h"
#include "SquadGrapManager.h"

SquadDeadCutScene::SquadDeadCutScene(std::string squadgpid,int deadnum)
{
	mSquad=SquadGrapManager::getSingletonPtr()->getSquad(squadgpid);
	mDeadNum = deadnum;
}
SquadDeadCutScene::~SquadDeadCutScene()
{

}
void SquadDeadCutScene::startCutScence()
{
	if(mDeadNum!=0)
		mSquad->setDeath(mDeadNum);
}
bool SquadDeadCutScene::endCutScene()
{
	return mSquad->isDeathOver();
}
void SquadDeadCutScene::skipCutScene()
{
	if(!mStarted && mDeadNum!=0)
		mSquad->setDeath(mDeadNum);
	mSquad->stopDeath();
}
void SquadDeadCutScene::updateCutScene(unsigned int deltaTime)
{

}