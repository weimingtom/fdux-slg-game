#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

class CameraContral;

class GUIBattle;
class GUIDeployWindows;
class GUIMenuWindow;
class BattleSquad;
class BattleSquadManager;
class AreaGrap;
class GUISquadWindows;

class BattleDeployState:public SubBattleState, public InputListener
{
public:
	BattleDeployState();
	~BattleDeployState();

	virtual void update(unsigned int deltaTime);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void deployConfirm();
	void selectIndex(int index);
private:
	CameraContral* mCameraContral;
	GUIBattle* mGUIBattle;
	GUIDeployWindows* mDeployWindow;
	GUISquadWindows* mSquadWindow;
	GUIMenuWindow* mMenuWindow;
	BattleSquad* mSelectSquad;
	int mSelectIndex;
	BattleSquadManager* mSquadManager;
	AreaGrap* mAreaGrap;

	int mMouseX;
	int mMouseY;
};