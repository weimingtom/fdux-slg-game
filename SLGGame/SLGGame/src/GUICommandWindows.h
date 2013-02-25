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
	MyGUI::Button* mSkill[18];
	MyGUI::TextBox* mAPLabel;
	MyGUI::TextBox* mSkillName;

	void onSkillClick(MyGUI::Widget* _sender);
	void onSkillHighlighted(MyGUI::Widget* _sender, MyGUI::Widget* _old);
	void onSkillLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);

	void useSkill(int n);

	std::string mSkillId[9];
	int mSkillPage;

	BattlePlayerState* mPlayerState;
	BattleSquad* mSelectSquad;
};
