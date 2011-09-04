#include "GUIBattle.h"

#include "GUIGameStateWindows.h"
#include "GUITerrainWindows.h"
#include "GUISquadWindows.h"
#include "GUIDeployWindow.h"
#include "GUICommandWindows.h"
#include "GUITargetWindow.h"
#include "GUIInfoWindow.h"
#include "GUITipsWindow.h"

#include "Terrain.h"

#include "CollisionTools.h"
#include "CameraContral.h"

GUIBattle::GUIBattle(int Width,int Height):GUIScene("Battle.layout",Width,Height)
{
	MyGUI::Window* window;

	assignWidget(window,"TipsWindow");
	mSubWindows.push_back(new GUITipsWindow(window,Width,Height));
	assignWidget(window,"Terrain");
	mSubWindows.push_back(new GUITerrainWindows(window,Width,Height));
	assignWidget(window,"TargetWindow");
	mSubWindows.push_back(new GUITargetWindows(window,Width,Height));
	assignWidget(window,"SquadWindow");
	mSubWindows.push_back(new GUISquadWindows(window,Width,Height));
	assignWidget(window,"CommandWindow");
	mSubWindows.push_back(new GUICommandWindows(window,Width,Height));
	assignWidget(window,"GameState");
	mSubWindows.push_back(new GUIGameStateWindows(window,Width,Height));
	assignWidget(window,"DeployWindow");
	mSubWindows.push_back(new GUIDeployWindows(window,Width,Height));
	assignWidget(window,"InfoWindow");
	mSubWindows.push_back(new GUIInfoWindow(window,Width,Height));
	//assignWidget(mButton,"ShadowMapTarget");

}

GUIBattle::~GUIBattle(void)
{
}

void GUIBattle::showScene( std::string arg )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->showScene("");
	}
}

void GUIBattle::hideScene()
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		delete (*it);
	}
}

void GUIBattle::FrameEvent()
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->FrameEvent();
	}


}

void GUIBattle::SceneInputEvent( float x,float y )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if (!(*it)->SceneInputEvent(x,y))
		{
			break;
		}
	}

	int GX,GY;
	if(Terrain::getSingletonPtr()->coordinateToGrid(x,y,GX,GY))
	{
		GridInputEvent(GX,GY);
		//std::cout<<GX<<","<<GY<<std::endl;
	}
}

void GUIBattle::GridInputEvent( int x,int y )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if ((*it)->GridInputEvent(x,y))
		{
			break;
		}
	}
}

GUISubWindows* GUIBattle::getSubWindow(std::string arg)
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if(arg == (*it)->getName())
			return (*it);
	}
	return NULL;
}

void GUIBattle::setBattleState( BattleState* state )
{
	mBattleState=state;

	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->setBattleState(mBattleState);
	}
}

void GUIBattle::KeyInputEvent( const OIS::KeyEvent &arg )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if (!(*it)->KeyInputEvent(arg))
		{
			break;
		}
	}
}
