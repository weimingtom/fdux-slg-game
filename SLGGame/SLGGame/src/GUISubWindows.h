#pragma once

#include <string>

#include "GUIScene.h"

class GUISubWindows:public GUIScene
{
public:
	GUISubWindows(MyGUI::Window* window,int Width,int Height):GUIScene(window,Width,Height)
	{

	};
	virtual ~GUISubWindows(){};

	//格子输入事件,返回值表示是否继续向下传递
	virtual bool GridInputEvent(int x,int y)=0;

	virtual std::string getName()=0;
};