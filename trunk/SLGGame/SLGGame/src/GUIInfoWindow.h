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
	void onOtherSceneNotify(std::string arg);
private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mCaption;
	MyGUI::Timer mTimer;//¶¨Ê±Æ÷
	bool isStart;
	bool isWait;
};
