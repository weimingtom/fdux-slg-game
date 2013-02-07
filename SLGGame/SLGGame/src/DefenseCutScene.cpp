#include "DefenseCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

DefenseCutScene::DefenseCutScene(std::string attackID, std::string defenseID, unsigned int defenseDeadCount)
{
	mAttackSG=SquadGrapManager::getSingletonPtr()->getSquad(attackID);
	mDefenseSG=SquadGrapManager::getSingletonPtr()->getSquad(defenseID);
	mDeadCount=defenseDeadCount;
}

DefenseCutScene::~DefenseCutScene()
{

}

void DefenseCutScene::startCutScence()
{
	if (mDeadCount!=0)
	{
		mDefenseSG->setDeath(mDeadCount);
	}
	
	mDefenseSG->defenseAction(mAttackSG,true);
}

bool DefenseCutScene::endCutScene()
{
	if (mDeadCount!=0)
	{
		return mDefenseSG->isDeathOver();
	}
	else
	{
		return mDefenseSG->isDefenseActionOver();
	}
}

void DefenseCutScene::skipCutScene()
{
	if(!mStarted && mDeadCount!=0)
		mDefenseSG->setDeath(mDeadCount);
	mDefenseSG->stopDeath();
}

void DefenseCutScene::updateCutScene( unsigned int deltaTime )
{

}
