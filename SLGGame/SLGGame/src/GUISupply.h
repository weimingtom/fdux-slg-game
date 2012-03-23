#pragma once

#include "GUIScene.h"

class GUISupply
	:public GUIScene
{
public:
	GUISupply(int width,int height);
	~GUISupply(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return SupplyScene;
	}

private:
	MyGUI::ImageBox* mSupplyBG;
	MyGUI::ListBox* mArmyList;
};

class GUISupplywFactory:
	public GUISceneFactory
{
public:
	GUISupplywFactory(){}

	~GUISupplywFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUISupply(Width, Height);
	}
};