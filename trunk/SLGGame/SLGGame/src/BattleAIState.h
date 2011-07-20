#pragma once

#include "SubBattleState.h"

#include "squaddefine.h"

class BattleSquadManager;

class BattleAIState:public SubBattleState
{
public:
	BattleAIState(int team);
	~BattleAIState();

	void newTurn();

	virtual void update(unsigned int deltaTime);
private:
	BattleSquadManager* mSquadManager;
	int mTeam;
};