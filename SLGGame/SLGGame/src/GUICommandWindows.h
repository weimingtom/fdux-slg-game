#pragma once

#include "GUISubWindows.h"

class BattleState;
class BattleSquad;
class BattlePlayerState;

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
	void setPlayerState(BattlePlayerState* playerstate);
private:
	MyGUI::Window* mWindow;
	MyGUI::Button* mSkill[9];
	MyGUI::TextBox* mAPLabel;

	void onSkill1(MyGUI::Widget* _sender);
	void onSkill2(MyGUI::Widget* _sender);
	void onSkill3(MyGUI::Widget* _sender);
	void onSkill4(MyGUI::Widget* _sender);
	void onSkill5(MyGUI::Widget* _sender);
	void onSkill6(MyGUI::Widget* _sender);
	void onSkill7(MyGUI::Widget* _sender);
	void onSkill8(MyGUI::Widget* _sender);
	void onSkill9(MyGUI::Widget* _sender);

	void useSkill(int n);

	std::string mSkillId[9];

	BattlePlayerState* mPlayerState;
	BattleSquad* mSelectSquad;
};
