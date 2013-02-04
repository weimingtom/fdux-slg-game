#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

#include <vector>

class CameraContral;

class GUIBattle;
class GUIDeployWindows;
class GUIMenuWindow;
class BattleSquad;
class AreaGrap;
class GUISquadWindows;
class DeployItemBox;

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
	void selectIndex(unsigned int index);
private:
	CameraContral* mCameraContral;
	GUIBattle* mGUIBattle;
	GUIDeployWindows* mDeployWindow;
	GUISquadWindows* mSquadWindow;
	GUIMenuWindow* mMenuWindow;
	std::vector<BattleSquad*> mDeployList;
	BattleSquad* mSelectSquad;
	int mSelectIndex;
	AreaGrap* mAreaGrap;

	int mMouseX;
	int mMouseY;
};