#include "GUISquadWindows.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "boost/format.hpp"

GUISquadWindows::GUISquadWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mSquadNameLabel,"SquadNameLabel");
	assignWidget(mSquadTypeLabel,"SquadTypeLabel");
	assignWidget(mSquadDescribeLabel,"SquadDescribeLabel");
	assignWidget(mSquadImage,"SquadImage");

	window->setPosition(0,Height-window->getHeight());
}

GUISquadWindows::~GUISquadWindows(void)
{
}

void GUISquadWindows::showScene( std::string arg )
{

}

void GUISquadWindows::hideScene()
{

}

void GUISquadWindows::FrameEvent()
{

}

bool GUISquadWindows::GridInputEvent( int x,int y )
{
	std::vector<std::string> squadList=DataLibrary::getSingletonPtr()->getChildList("GameData/BattleData/SquadList");
	
	std::string squadId="";
	bool flag=false;
	for (std::vector<std::string>::iterator it=squadList.begin();it!=squadList.end();it++)
	{
		squadId=str(boost::format("GameData/BattleData/SquadList/%1%/GridX")%(*it));
		int value=0;
		DataLibrary::getSingletonPtr()->getData(squadId,value);
		if (value==x)
		{
			squadId=str(boost::format("GameData/BattleData/SquadList/%1%/GridY")%(*it));
			DataLibrary::getSingletonPtr()->getData(squadId,value);
			if (value==y)
			{
				squadId=str(boost::format("GameData/BattleData/SquadList/%1%/")%(*it));
				flag=true;
				break;
			}
		}
	}
	
	if(flag)
	{
		std::string value="";
		DataLibrary::getSingletonPtr()->getData(squadId+"Name",value);
		mSquadNameLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"Type",value);
		mSquadTypeLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"Describe",value);
		mSquadDescribeLabel->setCaption(value);
		DataLibrary::getSingletonPtr()->getData(squadId+"LeaderPicture",value);
		mSquadImage->setImageTexture(value);
	}
	else
	{
		mSquadNameLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadName"));
		mSquadTypeLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadType"));
		mSquadDescribeLabel->setCaption(StringTable::getSingletonPtr()->getString("GUINoSquadDescribe"));
		mSquadImage->setImageTexture("");
	}

	return true;
}
