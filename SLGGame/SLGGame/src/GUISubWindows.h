#pragma once

#include <string>

#include "GUIScene.h"

#include "BattleState.h"

#include <OIS.h>

class GUISubWindows:public GUIScene
{
public:
	GUISubWindows(MyGUI::Window* window,int Width,int Height):GUIScene(window,Width,Height),mBattleState(NULL)
	{

	};
	virtual ~GUISubWindows(){};

	//格子输入事件,返回值表示是否继续向下传递
	virtual bool GridInputEvent(int x,int y)=0;
	
	//屏幕输入事件,返回值表示是否继续向下传递
	virtual bool SceneInputEvent(float x,float y)
	{
		return true;
	}

	//键盘输入事件,返回值表示是否继续向下传递
	virtual bool KeyInputEvent(const OIS::KeyEvent &arg)
	{
		return true;
	}

	virtual std::string getName()=0;

	void setBattleState(BattleState* state)
	{
		mBattleState=state;
	}
protected:
	BattleState* mBattleState;
};