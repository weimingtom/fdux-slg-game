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

	virtual void reactiveState();
private:
	GUIBattle* mGUIBattle;
	GUIGameStateWindows* mGUIState;
	enum ControlState
	{
		ControlState_NewGame,
		ControlState_LoadGame,
		ControlState_Normal,
		ControlState_TurnStart,
		ControlState_TurnEnd
	};
	ControlState mCurState;
};