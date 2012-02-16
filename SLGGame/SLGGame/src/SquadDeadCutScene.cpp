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
	mSquad->setDeath(mDeadNum);
}
bool SquadDeadCutScene::endCutScene()
{
	return mSquad->isDeathOver();
}
void SquadDeadCutScene::skipCutScene()
{
	if(!mStarted)
		mSquad->setDeath(mDeadNum);
	mSquad->stopDeath();
}
void SquadDeadCutScene::updateCutScene(unsigned int deltaTime)
{

}