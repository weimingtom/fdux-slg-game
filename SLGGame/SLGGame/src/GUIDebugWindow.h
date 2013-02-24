#pragma once
#include "guiscene.h"

class GUIDebugWindow :
	public GUIScene
{
public:
	GUIDebugWindow(int Width,int Height);
	virtual ~GUIDebugWindow(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return DebugWindowsScene;
	}
private:

	void onAddSquad(MyGUI::Widget* _sender);
	void onDeleteSquad(MyGUI::Widget* _sender);
	void onRefreshList(MyGUI::Widget* _sender);
	void onJumpCP(MyGUI::Widget* _sender);
	void onWin(MyGUI::Widget* _sender);

	MyGUI::Window* mWindow;
	MyGUI::Button* mAddSquad;
	MyGUI::Button* mDeleteSquad;
	MyGUI::Button* mRefreshList;
	MyGUI::Button* mJumpCP;
	MyGUI::Button* mWin;
	MyGUI::EditBox* mSquadName;
	MyGUI::EditBox* mSquadLeader;
	MyGUI::EditBox* mJump;
	MyGUI::ListBox* mSquadList;

};

class GUIDebugWindowFactory:
	public GUISceneFactory
{
public:
	GUIDebugWindowFactory(){}

	~GUIDebugWindowFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIDebugWindow(Width, Height);
	}
};