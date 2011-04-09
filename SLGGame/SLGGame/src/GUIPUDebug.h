#pragma once

#include "GUIScene.h"

class CutSceneDirector;

class GUIPUDebug:
	public GUIScene
{
public:
	GUIPUDebug();
	virtual ~GUIPUDebug(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return PUDebugScene;
	}

	CutSceneDirector* mDirector;
private:
	void onStart(MyGUI::Widget* _sender);
	void onRefresh(MyGUI::Widget* _sender);
	void onMove(MyGUI::Widget* _sender);
	void onDirection(MyGUI::Widget* _sender);
	void onFormation(MyGUI::Widget* _sender);
	void onDeath(MyGUI::Widget* _sender);
	void onRecover(MyGUI::Widget* _sender);

	MyGUI::ListBox* mPUList;
	MyGUI::Button* mStart;
	MyGUI::Button* mRefresh;
	MyGUI::EditBox* mScaleX;
	MyGUI::EditBox* mScaleY;
	MyGUI::EditBox* mScaleZ;
	MyGUI::EditBox* mScaleTime;

	MyGUI::EditBox* mSquadID;
	MyGUI::Button* mMove;

	MyGUI::Button* mDirection;
	MyGUI::ListBox* mDirectionList;

	MyGUI::Button* mFormation;
	MyGUI::ListBox* mFormationList;

	MyGUI::Button* mDeath;
	MyGUI::Button* mRecover;
	MyGUI::EditBox* mRecoverNum;

};

class GUIPUDebugFactory:
	public GUISceneFactory
{
public:
	GUIPUDebugFactory(){}

	~GUIPUDebugFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIPUDebug();
	}
};