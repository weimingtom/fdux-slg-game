#pragma once

#include "GUISubWindows.h"
#include "DeployItemBox.h"
#include "BattleSquad.h"

#include <string>
#include <vector>

class BattleDeployState;

class GUIDeployWindows:public GUISubWindows
{
public:
	GUIDeployWindows(MyGUI::Window* window,int Width,int Height);
	~GUIDeployWindows(void);

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
		return "DeployWindow";
	}

	void initList(std::vector<BattleSquad*>& list);
	void setAllowConfirm(bool allow);
	void setDeployState(BattleDeployState* state);
	void setDeployInfo(int index, std::string info);
private:
	MyGUI::Window* mWindow;
	DeployItemBox* mDeployList;
	MyGUI::Button* mConfirm;

	void onSelect(MyGUI::ItemBox* _sender, size_t _index);
	void onConfirm(MyGUI::Widget* _sender);

	BattleDeployState* mState;
};
