#pragma once

#include "GUISubWindows.h"

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

	void initList(std::vector<std::string> squadlist);
	void setAllowConfirm(bool allow);
	void setDeployState(BattleDeployState* state);
	void setDeployInfo(int index, std::string info);
private:
	MyGUI::Window* mWindow;
	MyGUI::MultiListBox* mDeployList;
	MyGUI::Button* mConfirm;

	void onSelect(MyGUI::MultiListBox* _sender, size_t _index);
	void onConfirm(MyGUI::Widget* _sender);

	BattleDeployState* mState;
};
