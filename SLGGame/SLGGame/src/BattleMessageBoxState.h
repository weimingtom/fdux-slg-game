#pragma once

#include "SubBattleState.h"
#include <string>

class BattlePlayerState;

class BattleMessageBoxState: public SubBattleState
{
public:
	BattleMessageBoxState(BattlePlayerState* playerstate, std::string message);
	~BattleMessageBoxState();

	virtual void update(unsigned int deltaTime);
private:
	BattlePlayerState* mPlayerState;
};