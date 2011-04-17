#pragma once

#include "GUISubWindows.h"

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
		return "Command";
	}

private:
	MyGUI::Window* mWindow;
	MyGUI::Button* mMoveButton;
	MyGUI::Button* mAttackButton;
	MyGUI::Button* mFormationButton;
	MyGUI::Button* mSkillButton;

	float mSceneX,mSceneY;

};
