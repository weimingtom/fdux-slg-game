#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

class GUIBattle;
class GUIGameStateWindows;
class GUIMenuWindow;
class GUISquadWindows;

class CameraContral;

class BattleSquad;


class BattlePlayerState:public SubBattleState, public InputListener
{
public:
	BattlePlayerState(bool newturn);
	~BattlePlayerState();

	virtual void update(unsigned int deltaTime);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
private:
	GUIBattle* mGUIBattle;
	GUIGameStateWindows* mGUIState;
	GUIMenuWindow* mGUIMenu;
	GUISquadWindows* mGUISquad;

	int mMouseX;
	int mMouseY;

	CameraContral* mCameraContral;

	enum PlayerControlState
	{
		PLAYERCONTROL_NONE = 0,
		PLAYERCONTROL_CHOOSESKILL = 1,
		PLAYERCONTROL_CHOOSETARGET = 2,
		PLAYERCONTROL_MENU = 3
	};
	PlayerControlState mControlState;

private:
	void newTurn();

	BattleSquad* mSelectSquad;

};