#pragma once

#include "SubBattleState.h"
#include "LuaSystem.h"

#include <string>

class BattleAvgState:public SubBattleState,public LuaSystemListener
{
public:
	BattleAvgState(std::string arg);
	~BattleAvgState(void);

	void update(unsigned int deltaTime);

	void onError(std::string error);
	void onComplete();
};
