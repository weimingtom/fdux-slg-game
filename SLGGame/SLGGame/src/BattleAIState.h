#pragma once

#include "SubBattleState.h"

class BattleAIState:public SubBattleState
{
public:
	BattleAIState(int team);
	~BattleAIState();

	virtual void update(unsigned int deltaTime);
private:
};