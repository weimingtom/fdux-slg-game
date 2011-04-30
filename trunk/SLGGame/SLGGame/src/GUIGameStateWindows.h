#pragma once

#include "GUISubWindows.h"

class BattlePlayerState;

class GUIGameStateWindows:public GUISubWindows
{
public:
	GUIGameStateWindows(MyGUI::Window* window,int Width,int Height);
	~GUIGameStateWindows(void);

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
		return "GameState";
	}

	void update();
	void setAllowNextTurn(bool allow) {mNextTurn->setEnabled(allow);}

private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mTurnLabel;
	MyGUI::TextBox* mPlayerLabel;
	MyGUI::Button* mNextTurn;

	void onNextTurn(MyGUI::Widget* _sender);

};
