#include "SquadRecoverCutScene.h"
#include "SquadGraphics.h"
#include "SquadGrapManager.h"

SquadRecoverCutScene::SquadRecoverCutScene(std::string squadgpid,int deadnum)
{
	mSquad=SquadGrapManager::getSingletonPtr()->getSquad(squadgpid);
	mRecoverNum = deadnum;
}
SquadRecoverCutScene::~SquadRecoverCutScene()
{

}
void SquadRecoverCutScene::startCutScence()
{
	mSquad->setRecover(mRecoverNum);
}
bool SquadRecoverCutScene::endCutScene()
{
	return mSquad->isRecoverOver();
}
void SquadRecoverCutScene::skipCutScene()
{
	if (!mStarted)
	{
		mSquad->setRecover(mRecoverNum);
	}

	mSquad->stopTransform();
}
void SquadRecoverCutScene::updateCutScene(unsigned int deltaTime)
{

}