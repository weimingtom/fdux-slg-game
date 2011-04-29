#pragma once

#include "SubBattleState.h"
#include <string>

class GUIBattle;
class GUIGameStateWindows;

class BattleControlState:public SubBattleState
{
public:
	BattleControlState(bool newgame);
	~BattleControlState();

	virtual void update(unsigned int deltaTime);
private:
	GUIBattle* mGUIBattle;
	GUIGameStateWindows* mGUIState;
};