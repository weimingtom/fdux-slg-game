#pragma once

#include "Core.h"
#include "SubBattleState.h"
#include "InputListener.h"

class GUIBattle;
class GUIGameStateWindows;
class GUIMenuWindow;
class GUISquadWindows;
class GUICommandWindows;

class CameraContral;

class BattleSquad;
class AreaGrap;


class BattlePlayerState:public SubBattleState, public InputListener
{
public:
	BattlePlayerState();
	~BattlePlayerState();

	virtual void update(unsigned int deltaTime);

	virtual void reactiveState();

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void createSelectPlane();
	void setSelectPlanePosition(int GX,int GY,float height);
	void setSelectPlanePosition();
	void hideSelectPlane();
	Ogre::SceneNode* planeNode;

	void useSkill(std::string skillid);

	void backFromMenu();
private:
	GUIBattle* mGUIBattle;
	GUIGameStateWindows* mGUIState;
	GUIMenuWindow* mGUIMenu;
	GUISquadWindows* mGUISquad;
	GUICommandWindows* mGUICommand;

	int mMouseX;
	int mMouseY;

	CameraContral* mCameraContral;

	enum PlayerControlState
	{
		PLAYERCONTROL_NONE = 0,
		PLAYERCONTROL_CHOOSESKILL = 1,
		PLAYERCONTROL_CHOOSETARGET = 2,
		PLAYERCONTROL_TURNSQUAD = 3,
		PLAYERCONTROL_MENU = 4
	};
	PlayerControlState mControlState;

	BattleSquad* mSelectSquad;
	std::string mSelectSkillId;

	AreaGrap* mRangeGrap;
	AreaGrap* mTargetAreaGrap;
	int mLastTargetX;
	int mLastTargetY;	
};