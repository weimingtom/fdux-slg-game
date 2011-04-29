#pragma once

#include "GUISubWindows.h"

class GUITerrainWindows:public GUISubWindows
{
public:
	GUITerrainWindows(MyGUI::Window* window,int Width,int Height);
	~GUITerrainWindows(void);

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
		return "Terrain";
	}

private:
	MyGUI::Window* mWindow;
	MyGUI::TextBox* mTerrainTypeLabel;
	MyGUI::TextBox* mGroundTypeLabel;
	MyGUI::TextBox* mGroundObjLabel;
	MyGUI::TextBox* mPassableLabel;
	MyGUI::TextBox* mTerrainCovertLabel;
	MyGUI::TextBox* mTerrainDefenceLabel;
	MyGUI::TextBox* mTerrainCavApLabel;
	MyGUI::TextBox* mTerrainInfApLabel;
	MyGUI::TextBox* mTerrainGridXLabel;
	MyGUI::TextBox* mTerrainGridYLabel;

	int mMapSize;
	int mCurX;
	int mCurY;
};
