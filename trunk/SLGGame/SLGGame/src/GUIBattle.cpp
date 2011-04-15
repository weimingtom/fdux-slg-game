#include "GUIBattle.h"

#include "GUIGameStateWindows.h"
#include "GUITerrainWindows.h"
#include "GUISquadWindows.h"

GUIBattle::GUIBattle(int Width,int Height):GUIScene("Battle.layout",Width,Height)
{
	MyGUI::Window* window;
	assignWidget(window,"Terrain");
	mSubWindows.push_back(new GUITerrainWindows(window,Width,Height));
	assignWidget(window,"Squad");
	mSubWindows.push_back(new GUISquadWindows(window,Width,Height));
	assignWidget(window,"GameState");
	mSubWindows.push_back(new GUIGameStateWindows(window,Width,Height));
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
