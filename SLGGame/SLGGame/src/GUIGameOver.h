#pragma once
#include "guisubwindows.h"

class GUIGameOver :
	public GUISubWindows
{
public:
	GUIGameOver(MyGUI::Window* window,int Width,int Height);
	virtual ~GUIGameOver(void);

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
		return "GameOverWindow";
	}

	void onOtherSceneNotify(std::string arg);

	void setData(int gold);

	void setNext(std::string name);

	void onConfirm(MyGUI::Widget* _sender);
private:
	MyGUI::Window* mWindow;
	MyGUI::ImageBox* mCaption;
	MyGUI::TextBox* mGold;
	MyGUI::TextBox* mSquadWage;
	MyGUI::Button* mButton;
	bool isWin;
	std::string mNext;
};
