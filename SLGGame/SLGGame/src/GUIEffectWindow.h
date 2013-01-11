#pragma once

#include "GUISubWindows.h"
#include "iisingleton.hpp"

using namespace izayoi;

class StringTable;
class GUIEffectWindow:public IISingleton<GUIEffectWindow>,public GUISubWindows
{
public:
	GUIEffectWindow(MyGUI::Window* window,int Width,int Height);
	~GUIEffectWindow();

	bool GridInputEvent(int x,int y);

	GUISceneType getType()
	{
		return BattleScene;
	}

	std::string getName()
	{
		return "EffectWindow";
	}
	void showScene( std::string arg );
	void hideScene();
	void FrameEvent();

	MyGUI::Window* mWindow;
	MyGUI::ImageBox* mEffect[12];
	
};