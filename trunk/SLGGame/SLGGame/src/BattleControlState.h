#pragma once

#include "SubBattleState.h"

class GUIBattle;

class BattleControlState:public SubBattleState
{
public:
	BattleControlState(BattleState* mainState);
	~BattleControlState();

	virtual void update(unsigned int deltaTime);

	void InitBattle();
private:
	GUIBattle* mGUIBattle;
};