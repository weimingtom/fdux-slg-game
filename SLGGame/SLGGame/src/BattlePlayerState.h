#pragma once

#include "SubBattleState.h"
#include "InputListener.h"
#include <string>

class GUIBattle;
class GUISquadWindows;
class GUIGameStateWindows;
class CameraContral;
class BattleSquadManager;
class BattleSquad;

class BattlePlayerState:public SubBattleState, public InputListener
{
public:
	BattlePlayerState();
	~BattlePlayerState();

	virtual void update(unsigned int deltaTime);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void newTurn();
private:
	GUIBattle* mGUIBattle;
	GUISquadWindows* mSquadWindow;
	GUIGameStateWindows* mGUIState;

	int mMouseX;
	int mMouseY;

	CameraContral* mCameraContral;
	BattleSquadManager* mSquadManager;

	BattleSquad* mSelectSquad;
};