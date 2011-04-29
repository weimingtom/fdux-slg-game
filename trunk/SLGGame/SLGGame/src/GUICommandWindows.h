#pragma once

#include "GUISubWindows.h"

class BattleState;
class BattleSquad;

class GUICommandWindows:public GUISubWindows
{
public:
	GUICommandWindows(MyGUI::Window* window,int Width,int Height);
	~GUICommandWindows(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return BattleScene;
	}

	bool SceneInputEvent(float x,float y);

	bool GridInputEvent(int x,int y);

	std::string getName()
	{
		return "CommandWindow";
	}

	void setSquad(BattleSquad* squad);
private:
	MyGUI::Window* mWindow;

	BattleSquad* mSelectSquad;
};
