#pragma once

#include "GUISubWindows.h"

class GUIGameStateWindows:public GUISubWindows
{
public:
	GUIGameStateWindows(MyGUI::Window* window,int Width,int Height);
	~GUIGameStateWindows(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return BattleScene;
	}

	bool GridInputEvent(int x,int y);

	std::string getName()
	{
		return "GameState";
	}

private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mTurnLabel;
	MyGUI::TextBox* mPlayerLabel;
};
