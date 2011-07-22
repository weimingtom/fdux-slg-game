#pragma once
#include "guisubwindows.h"

class GUIInfoWindow :
	public GUISubWindows
{
public:
	GUIInfoWindow(MyGUI::Window* window,int Width,int Height);
	virtual ~GUIInfoWindow(void);

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
		return "InfoWindow";
	}

	void setCaption(std::string text,MyGUI::Colour c);
private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mCaption;
	bool isStart;
	bool isWait;
};
