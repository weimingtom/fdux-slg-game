#pragma once

#include "GUIScene.h"
#include "BattleState.h"
#include <list>

class GUISubWindows;
class BattleState;

class GUIBattle:
	public GUIScene
{
public:
	GUIBattle(int Width,int Height);
	virtual ~GUIBattle(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return BattleScene;
	}

	void KeyInputEvent(const OIS::KeyEvent &arg);

	void SceneInputEvent(float x,float y);

	GUISubWindows* getSubWindow(std::string arg);

	void setBattleState(BattleState* state);
private:
	std::list<GUISubWindows*> mSubWindows;

	void GridInputEvent(int x,int y);
	
	BattleState* mBattleState;
};

class GUIBattleFactory:
	public GUISceneFactory
{
public:
	GUIBattleFactory(){}

	~GUIBattleFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIBattle(Width,Height);
	}
};