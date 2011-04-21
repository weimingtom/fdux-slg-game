#include "GUICommandWindows.h"

#include "DataLibrary.h"
#include "boost\format.hpp"

#include "BattleAvgState.h"

GUICommandWindows::GUICommandWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window),mSceneX(0),mSceneY(0)
{
	assignWidget(mMoveButton,"CmdMoveButton");
	assignWidget(mAttackButton,"CmdAttackButton");
	assignWidget(mFormationButton,"CmdFormationButton");
	assignWidget(mSkillButton,"CmdSkillButton");

	mMoveButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUICommandWindows::onMove);

	window->setVisible(false);
}

GUICommandWindows::~GUICommandWindows(void)
{
}

void GUICommandWindows::showScene( std::string arg )
{

}

void GUICommandWindows::hideScene()
{

}

void GUICommandWindows::FrameEvent()
{

}

void GUICommandWindows::onMove(MyGUI::Widget* _sender)
{
	mBattleState->PushState(new BattleAvgState(mBattleState,"Battle.lua"));
}

bool GUICommandWindows::SceneInputEvent( float x,float y )
{
	mSceneX=x;
	mSceneY=y;
	return true;
}

bool GUICommandWindows::GridInputEvent( int x,int y )
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

	if (flag)
	{
		mWindow->setVisible(true);
		mWindow->setPosition(mSceneX,mSceneY);
	}
	else
	{
		mWindow->setVisible(false);
	}

	return true;
}
