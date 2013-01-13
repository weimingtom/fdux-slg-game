#pragma once

#include "GUISubWindows.h"

class BattleSquad;

class GUIEffectWindow;

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
		return "SquadWindow";
	}

	void setSquad(BattleSquad* squad);
	void updateSquad();

private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mSquadLeadName;
	MyGUI::TextBox* mSquadTypeName;
	MyGUI::TextBox* mSquadGridX;
	MyGUI::TextBox* mSquadGridY;
	MyGUI::TextBox* mSquadPWeapon;
	MyGUI::TextBox* mSquadSWeapon;
	MyGUI::TextBox* mSquadShield;
	MyGUI::TextBox* mSquadArmor;
	MyGUI::TextBox* mSquadUnitNum;
	MyGUI::TextBox* mSquadAp;
	MyGUI::TextBox* mSquadAttack;
	MyGUI::TextBox* mSquadDefence;
	MyGUI::TextBox* mSquadDirection;
	MyGUI::TextBox* mSquadFormation;
	MyGUI::ImageBox* mSquadImage;
	MyGUI::ImageBox* mSquadFactionImage;

	BattleSquad* mSelectSquad;
	GUIEffectWindow* mEffectWindow;
};
