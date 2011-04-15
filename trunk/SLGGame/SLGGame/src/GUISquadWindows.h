#pragma once

#include "GUISubWindows.h"

class GUISquadWindows:public GUISubWindows
{
public:
	GUISquadWindows(MyGUI::Window* window,int Width,int Height);
	~GUISquadWindows(void);

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
		return "Squad";
	}

private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mSquadNameLabel;
	MyGUI::TextBox* mSquadTypeLabel;
	MyGUI::TextBox* mSquadDescribeLabel;
	MyGUI::ImageBox* mSquadImage;
};
