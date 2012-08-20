#pragma once
#include "guisubwindows.h"

class GUIMissionWindow :
	public GUISubWindows
{
public:
	GUIMissionWindow(MyGUI::Window* window,int Width,int Height);
	~GUIMissionWindow(void);

	void showScene(std::string arg);
	void hideScene();

	GUISceneType getType()
	{
		return BattleScene;
	}

	void FrameEvent(){};

	bool GridInputEvent(int x,int y)
	{
		return false;
	}

	std::string getName()
	{
		return "MissionWindow";
	}
private:
	MyGUI::Window* mWindow;

	MyGUI::ControllerFadeAlpha* mFadeController;
};
