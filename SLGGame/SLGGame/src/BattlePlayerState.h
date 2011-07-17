#pragma once

#include "SubBattleState.h"
#include "InputListener.h"
#include "Core.h"
#include <string>
#include <map>

#include "squaddefine.h"

class GUIBattle;
class GUISquadWindows;
class GUIGameStateWindows;
class GUICommandWindows;
class GUIMenuWindow;

class CameraContral;
class BattleSquadManager;
class BattleSquad;
class AreaGrap;

typedef int PlayerControlState;
const PlayerControlState  PLAYERCONTROL_NONE = 0;
const PlayerControlState  PLAYERCONTROL_CHOOSESKILL = 1;
const PlayerControlState  PLAYERCONTROL_MOVE = 2;
const PlayerControlState  PLAYERCONTROL_SKILL = 3;
const PlayerControlState  PLAYERCONTROL_CUTSCENE = 4;
const PlayerControlState  PLAYERCONTROL_MESSAGEBOX = 5;

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

	virtual void reactiveState();
	
	void moveSquad();
	void changeFormation(Formation f);
	void useSkill(std::string skillid);

	void newTurn();

	void setMessageBoxReturn(bool re) {mMessageBoxReturn = re;}
private:
	GUIBattle* mGUIBattle;
	GUISquadWindows* mSquadWindow;
	GUIGameStateWindows* mGUIState;
	GUICommandWindows* mGUICommand;
	GUIMenuWindow* mGUIMenu;

	void clearPathInfo(bool clearnode);
	void createPath(int x,int y);


	int mMouseX;
	int mMouseY;

	CameraContral* mCameraContral;
	BattleSquadManager* mSquadManager;

	BattleSquad* mSelectSquad;
	PlayerControlState mState;
	AreaGrap* mMoveAreaGrap;
	struct MoveNode
	{
		int x;
		int y;
		Direction mDirectionToPrev;
		float mPrevApLeft;
		float mAPleft;
	};
	std::map<int, MoveNode*> mMoveMap;
	typedef std::map<int, MoveNode*>::value_type MapNodeType;
	typedef std::map<int, MoveNode*>::iterator MapNodeIte;
	bool canPass(int x, int y, float &apcost);

	//ÒÆ¶¯Â·¾¶ÏÔÊ¾
	class MovePath
	{
	public:
		MovePath()
		{
			mPathNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
			mPathEnt = Core::getSingleton().mSceneMgr->createEntity("MoveArrow.mesh");
			mPathNode->attachObject(mPathEnt);
			mPathNode->setVisible(false);
		}
		~MovePath()
		{
			mPathNode->detachObject(mPathEnt);
			Core::getSingleton().mSceneMgr->destroyEntity(mPathEnt);
			Core::getSingleton().mSceneMgr->destroySceneNode(mPathNode);
		}
		void setPosition(int x, int y, Direction d);
		void setVisible(bool visiable) {mPathNode->setVisible(visiable);}
	private:
		Ogre::Entity* mPathEnt;
		Ogre::SceneNode* mPathNode;
	};
	std::vector<MovePath*> mMovePathList;

	void executeMove(int x, int y);
	int mMoveTargetX;
	int mMoveTargetY;

	std::string mSkillid;
	BattleSquad* mTargetSquad;
	SkillType mSkillType;
	int mSkillArea;
	bool mMeleeSkill;
	AreaGrap* mTargetAreaGrap;
	void drawSkillMoveArea(SkillType skilltype, float skillcost);
	void drawSkillArea(SkillType skilltype, int minrange, int maxrange);
	int skillPass(int x, int y, float &apcost, SkillType skilltype, float skillcost);
	void useSkillAt(int x,int y);
	void drawSkillTargetArea(int x,int y);
	void executeSkillAt(int x, int y);
	void executeSkillOn(int x, int y, BattleSquad* squad);

	bool mMessageBoxReturn;
};