#pragma once
#include "GUIScene.h"

class GUISLWindow;
class GUIOptionWindow;

class GUIMenu :
	public GUIScene
{
public:
	GUIMenu(int width,int height);
	~GUIMenu(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return MenuScene;
	}
private:

	void onNewGame(MyGUI::Widget* _sender);
	void onLoad(MyGUI::Widget* _sender);
	void onOpiton(MyGUI::Widget* _sender);
	void onExit(MyGUI::Widget* _sender);

	void setButtonLock(bool isLock);
	void onOtherSceneNotify(std::string arg);
	enum MenuStateEnum
	{
		NoneState,
		LogoState,
		NewState,
		WaitState,
		ExitState,
		MainMenuState,
		SaveMenuState,
		LoadMenuState,
		PauseMenuState,
		OpitonMenusState
	};

	MenuStateEnum mMenuState;

	MyGUI::ImageBox* mLogoImage;
	MyGUI::ImageBox* mMenuImage;

	MyGUI::Button* mNewGame;
	MyGUI::Button* mLoad;
	MyGUI::Button* mOpiton;
	MyGUI::Button* mExit;

	GUISLWindow* SLWindow;
	GUIOptionWindow* mOptionWindow;

	MyGUI::Timer mTimer;//定时器
	float mTickTime;//单次触发时间

};

class GUIMenuFactory:
	public GUISceneFactory
{
public:
	GUIMenuFactory(){}

	~GUIMenuFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIMenu(Width,Height);
	}
};