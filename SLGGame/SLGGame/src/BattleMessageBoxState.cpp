#include "BattleMessageBoxState.h"

#include "BattlePlayerState.h"
#include "BattleState.h"

BattleMessageBoxState::BattleMessageBoxState(BattlePlayerState* playerstate, std::string message)
:mPlayerState(playerstate)
{

}
BattleMessageBoxState::~BattleMessageBoxState()
{

}

void BattleMessageBoxState::update(unsigned int deltaTime)
{
	mPlayerState->setMessageBoxReturn(true);
	mMainState->PopState();
}