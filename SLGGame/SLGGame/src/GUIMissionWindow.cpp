#include "GUIMissionWindow.h"

#include "GUIBattle.h"
#include "boost/format.hpp"

#define MAX_MISSION_NUM 5

GUIMissionWindow::GUIMissionWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mIsShow(false),mIndex(0)
{
	mWindow=window;
	assignWidget(mClose,"TEXT_Close");
	mClose->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMissionWindow::onMissionClose);

	clearMission();
}

GUIMissionWindow::~GUIMissionWindow(void)
{
	
}

void GUIMissionWindow::onMissionClose(MyGUI::Widget* _sender)
{
	hideScene();
	GUIScene* s=GUISystem::getSingletonPtr()->getScene(BattleScene);
	
	FadeIn(300,((GUIBattle*)s)->mMissionButton);
	((GUIBattle*)s)->mMissionButton->setEnabled(true);
}

void GUIMissionWindow::showScene(std::string arg)
{
	if(arg!="")
	{
		FadeIn(300,mWindow);
		mWindow->setVisible(true);
		mIsShow=true;
	}

}

void GUIMissionWindow::hideScene()
{
	FadeOut(300,mWindow);
	mWindow->setVisible(false);
	mIsShow=false;
}

int GUIMissionWindow::addMission( std::string caption,MissionState state )
{
	if(mIndex<=MAX_MISSION_NUM)
	{
		changeMission(mIndex,state,caption);

		mIndex++;

		if(!mIsShow)
		{
			GUIScene* s=GUISystem::getSingletonPtr()->getScene(BattleScene);

			((GUIBattle*)s)->onMissionButton(NULL);
		}

		return mIndex-1;
	}
	else
	{
		return -1;
	}

}

void GUIMissionWindow::changeMission( int index,MissionState state,std::string caption)
{
	MyGUI::ImageBox* icon;
	MyGUI::TextBox* text;

	if(caption!="")
	{
		assignWidget(text,str(boost::format("Mission%1%Caption")%(mIndex+1)));

		if(caption!="clear")
		{
			text->setCaption(caption);
		}
		else
		{
			text->setCaption("");
		}
	}

	assignWidget(icon,str(boost::format("Mission%1%Icon")%(index+1)));

	switch (state)
	{
	case MS_New:
		{
			icon->setItemName("New");
			break;
		}
	case MS_Complete:
		{
			icon->setItemName("Complete");
			break;
		}
	case MS_Fail:
		{
			icon->setItemName("Fail");
			break;
		}
	case MS_NULL:
		{
			icon->setItemName("");
			break;
		}
	}
}

void GUIMissionWindow::clearMission()
{
	mIndex=0;
	for (int i=0;i<MAX_MISSION_NUM;i++)
	{
		changeMission(i,MS_NULL,"clear");
	}

}
