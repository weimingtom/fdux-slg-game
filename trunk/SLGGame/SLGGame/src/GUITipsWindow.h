#pragma once

#include "GUISubWindows.h"
#include "iisingleton.hpp"

using namespace izayoi;

class StringTable;
class GUITipsWindow:public IISingleton<GUITipsWindow>,public GUISubWindows
{
public:
	GUITipsWindow(MyGUI::Window* window,int Width,int Height);
	~GUITipsWindow();

	void eventToolTip(MyGUI::Widget* _sender, const MyGUI::ToolTipInfo& _info); 

	bool GridInputEvent(int x,int y);

	GUISceneType getType()
	{
		return BattleScene;
	}

	std::string getName()
	{
		return "TipsWindow";
	}
	void showScene( std::string arg );
	void hideScene();
	void FrameEvent();
	void setTips(std::string text);
	void setTipsWindowPosition(int left,int top);

	MyGUI::Window* mWindow;
	MyGUI::EditBox* mTipsTextBox;
	
	StringTable* mStringTable;
};