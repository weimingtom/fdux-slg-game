#pragma once

#include "GUIScene.h"
#include <list>

class GUISubWindows;

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

	void GridInputEvent(int x,int y);
private:
	std::list<GUISubWindows*> mSubWindows;
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