#include "GUISquadWindows.h"

#include "DataLibrary.h"

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

	return true;
}
