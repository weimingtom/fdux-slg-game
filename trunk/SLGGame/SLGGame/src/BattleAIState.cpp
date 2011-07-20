#include "BattleAIState.h"

#include "BattleState.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"

BattleAIState::BattleAIState(int team)
{
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mTeam = team;
}
BattleAIState::~BattleAIState()
{

}

void BattleAIState::update(unsigned int deltaTime)
{
	mMainState->PopState();
}

void BattleAIState::newTurn()
{
	for(int n = 0; n < mSquadManager->mSquadList.size(); n++)
	{
		if(mSquadManager->mSquadList[n]->getTeam() == 1)
			mSquadManager->mSquadList[n]->newTurn();
	}
}