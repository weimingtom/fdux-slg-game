#pragma once

#include "GUIScene.h"

class GUIBattle:
	public GUIScene
{
public:
	GUIBattle();
	virtual ~GUIBattle(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return BattleScene;
	}
private:

};

class GUIBattleFactory:
	public GUISceneFactory
{
public:
	GUIBattleFactory(){}

	~GUIBattleFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIBattle();
	}
};