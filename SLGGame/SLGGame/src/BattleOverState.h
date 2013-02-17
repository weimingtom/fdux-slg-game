#pragma once

#include "SubBattleState.h"
#include "LuaSystem.h"

#include <string>

class BattleOverState:public SubBattleState
{
public:
	BattleOverState(std::string arg);
	~BattleOverState(void);

	void update(unsigned int deltaTime);
};
