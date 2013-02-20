#pragma once

#include "GUISubWindows.h"

class BattleSquad;

class GUIEffectWindow;

class GUITargetWindows:public GUISubWindows
{
public:
	GUITargetWindows(MyGUI::Window* window,int Width,int Height);
	~GUITargetWindows(void);

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
		return "TargetWindow";
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
	MyGUI::TextBox* mSquadDirection;
	MyGUI::TextBox* mSquadFormation;
	MyGUI::ImageBox* mSquadImage;
	MyGUI::ImageBox* mSquadFactionImage;
	MyGUI::TextBox* mSquadLevel;
	MyGUI::TextBox* mSquadExp;
	MyGUI::TextBox* mSquadAttackFront;
	MyGUI::TextBox* mSquadAttackFlank;
	MyGUI::TextBox* mSquadAttackBack;
	MyGUI::TextBox* mSquadAttackRA;
	MyGUI::TextBox* mSquadDefenceFront;
	MyGUI::TextBox* mSquadDefenceFlank;
	MyGUI::TextBox* mSquadDefenceBack;
	MyGUI::TextBox* mSquadDefenceRA;

	BattleSquad* mSelectSquad;
	GUIEffectWindow* mEffectWindow;

	int mCurX;
	int mCurY;
};
