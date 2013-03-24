#pragma once
#include "guisubwindows.h"

#include "BattleSquad.h"

class GUIMapWindow :
	public GUISubWindows
{
public:
	GUIMapWindow(MyGUI::Window* window,int Width,int Height);
	~GUIMapWindow(void);

	void showScene(std::string arg);
	void hideScene();

	GUISceneType getType()
	{
		return BattleScene;
	}

	void FrameEvent(){updatePoint();};

	bool GridInputEvent(int x,int y);

	std::string getName()
	{
		return "MapWindow";
	}

	void addPoint(BattleSquad* squad);
	void updatePoint();
	void updatePointState(BattleSquad* squad,MyGUI::ImageBox* point=NULL);
	void updateInfo( int x,int y );

	void setSelectPoint(BattleSquad* squad);
	void eventUpdateAction(MyGUI::Widget* sender);

private:
	MyGUI::Window* mWindow;
	MyGUI::ImageBox* mMap;
	MyGUI::ImageBox* mSelect;
	std::map<BattleSquad*,MyGUI::ImageBox*> mPoints;
	
	MyGUI::ControllerFadeAlpha* mFadeController;
	MyGUI::ImageBox* mSelectPoint;
	bool mFadeIn;
	bool mIsFadeEnd;

	int mMapSize;

	/*MyGUI::TextBox* mTerrainTypeLabel;
	MyGUI::TextBox* mGroundTypeLabel;
	MyGUI::TextBox* mGroundObjLabel;
	MyGUI::TextBox* mPassableLabel;*/
	MyGUI::TextBox* mTerrainCovertLabel;
	MyGUI::TextBox* mTerrainDefenceLabel;
	MyGUI::TextBox* mTerrainCavApLabel;
	MyGUI::TextBox* mTerrainInfApLabel;
};
