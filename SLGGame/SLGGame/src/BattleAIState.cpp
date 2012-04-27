#include "BattleAIState.h"

#include "BattleState.h"

BattleAIState::BattleAIState(int team)
{

}
BattleAIState::~BattleAIState()
{

}

void BattleAIState::update(unsigned int deltaTime)
{
	mMainState->PopState();
}