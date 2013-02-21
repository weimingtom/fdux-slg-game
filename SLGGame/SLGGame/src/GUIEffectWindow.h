#pragma once

#include "GUISubWindows.h"
#include "iisingleton.hpp"

using namespace izayoi;

class StringTable;
class GUIEffectWindow:public GUISubWindows
{
public:
	GUIEffectWindow(MyGUI::Window* window,int Width,int Height,int index);
	~GUIEffectWindow();

	bool GridInputEvent(int x,int y);

	GUISceneType getType()
	{
		return BattleScene;
	}

	std::string getName()
	{
		return std::string("EffectWindow")+Ogre::StringConverter::toString(mIndex);
	}
	void showScene( std::string arg );
	void hideScene();
	void FrameEvent();

	void setEffectList(std::vector<std::string> list,std::vector<int> level);

	int mIndex;
	MyGUI::Window* mWindow;
	MyGUI::Button* mEffect[10];
	
};