#pragma once
#include "GUIScene.h"

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
	enum MenuStateEnum
	{
		NoneState,
		LogoState,
		WaitState,
		MainMenuState,
		SaveMenuState,
		LoadMenuState,
		PauseMenuState,
		OpitonMenusState
	};

	MenuStateEnum mMenuState;

	MyGUI::ImageBox* mLogoImage;
	MyGUI::ImageBox* mMenuImage;
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