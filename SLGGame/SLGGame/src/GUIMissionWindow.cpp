#include "GUIMissionWindow.h"

#include "GUIBattle.h"
#include "boost/format.hpp"
#include "DataLibrary.h"

#define MAX_MISSION_NUM 5

GUIMissionWindow::GUIMissionWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mIsShow(false),mIndex(0)
{
	mWindow=window;
	assignWidget(mClose,"TEXT_Close");
	mClose->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMissionWindow::onMissionClose);

	clearMission();

	std::vector<std::string> list=DataLibrary::getSingletonPtr()->getChildList("GameData/BattleData/MissionList");
	for (std::vector<std::string>::iterator it=list.begin();it!=list.end();it++)
	{
		std::string name;
		DataLibrary::getSingletonPtr()->getData(std::string("GameData/BattleData/MissionList/")+(*it)+"/Name",name);
		int state;
		DataLibrary::getSingletonPtr()->getData(std::string("GameData/BattleData/MissionList/")+(*it)+"/State",state);

		addMission(name,(MissionState)state,false);
	}

}

GUIMissionWindow::~GUIMissionWindow(void)
{
	clearMission();
	DataLibrary::getSingletonPtr()->delNode("GameData/BattleData/MissionList");
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

int GUIMissionWindow::addMission( std::string caption,MissionState state,bool addToXml)
{
	if(mIndex<=MAX_MISSION_NUM)
	{
		changeMission(mIndex,state,caption);

		mIndex++;

		if(!mIsShow && addToXml)
		{
			GUIScene* s=GUISystem::getSingletonPtr()->getScene(BattleScene);

			((GUIBattle*)s)->onMissionButton(NULL);
		}

		if(addToXml)
		{
			DataLibrary::getSingletonPtr()->setData(std::string("GameData/BattleData/MissionList/M")+Ogre::StringConverter::toString(mIndex)+"/Name",caption);
			DataLibrary::getSingletonPtr()->setData(std::string("GameData/BattleData/MissionList/M")+Ogre::StringConverter::toString(mIndex)+"/State",(int)state);
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
		assignWidget(text,str(boost::format("Mission%1%Caption")%(index+1)));

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
