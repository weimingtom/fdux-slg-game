#include "SubBattleState.h"

#include "BattleState.h"

SubBattleState::SubBattleState()
:mMainState(NULL)
{

}

SubBattleState::~SubBattleState()
{

}

void SubBattleState::setMainState(BattleState* mainstate)
{
	mMainState = mainstate;
}