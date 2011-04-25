#include "GUIBattle.h"

#include "GUIGameStateWindows.h"
#include "GUITerrainWindows.h"
#include "GUISquadWindows.h"
#include "GUIDeployWindow.h"
#include "GUICommandWindows.h"
#include "GUIMenuWindow.h"

#include "Terrain.h"

GUIBattle::GUIBattle(int Width,int Height):GUIScene("Battle.layout",Width,Height)
{
	MyGUI::Window* window;

	assignWidget(window,"Menu");
	mSubWindows.push_back(new GUIMenuWindow(window,Width,Height));
	assignWidget(window,"Command");
	mSubWindows.push_back(new GUICommandWindows(window,Width,Height));
	assignWidget(window,"Terrain");
	mSubWindows.push_back(new GUITerrainWindows(window,Width,Height));
	assignWidget(window,"Squad");
	mSubWindows.push_back(new GUISquadWindows(window,Width,Height));
	assignWidget(window,"GameState");
	mSubWindows.push_back(new GUIGameStateWindows(window,Width,Height));
	assignWidget(window,"DeployWindow");
	mSubWindows.push_back(new GUIDeployWindows(window,Width,Height));
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

}

void GUIBattle::FrameEvent()
{
	
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
		std::cout<<GX<<","<<GY<<std::endl;
	}
}

void GUIBattle::GridInputEvent( int x,int y )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if (!(*it)->GridInputEvent(x,y))
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
