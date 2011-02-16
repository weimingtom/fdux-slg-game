#pragma once

#include "GUICommon.h"
#include <MyGUI.h>

class GUIScene
{
public:
	GUIScene(){}

	virtual ~GUIScene(void){}

	virtual void showScene()=0;//显示场景
	virtual void hideScene()=0;//隐藏场景

	virtual void FrameEvent()=0;//帧事件

	virtual GUISceneType getType()=0;

	MyGUI::VectorWidgetPtr getWidgetVector()
	{
		return mWidgetVector;
	}

protected:
	MyGUI::VectorWidgetPtr mWidgetVector;
};
