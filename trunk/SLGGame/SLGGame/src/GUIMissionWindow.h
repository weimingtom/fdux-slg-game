#pragma once
#include "guisubwindows.h"

enum MissionState
{
	MS_New=0,
	MS_Complete=1,
	MS_Fail=2,
	MS_NULL=3
};

class GUIMissionWindow :
	public GUISubWindows
{
public:
	GUIMissionWindow(MyGUI::Window* window,int Width,int Height);
	~GUIMissionWindow(void);

	void showScene(std::string arg);
	void hideScene();

	GUISceneType getType()
	{
		return BattleScene;
	}

	void FrameEvent(){};

	bool GridInputEvent(int x,int y)
	{
		return false;
	}

	std::string getName()
	{
		return "MissionWindow";
	}

	int addMission(std::string caption,MissionState state,bool addToXml=true);
	void changeMission(int index,MissionState state,std::string caption="");
	void clearMission();

	void onMissionClose(MyGUI::Widget* _sender);

	int mIndex;
	bool mIsShow;
private:
	MyGUI::Window* mWindow;
	MyGUI::Button* mClose;
};
