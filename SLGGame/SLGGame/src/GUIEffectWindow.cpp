#include "GUIEffectWindow.h"

#include "boost/format.hpp"

GUIEffectWindow::GUIEffectWindow( MyGUI::Window* window,int Width,int Height ):GUISubWindows(window,Width,Height),mWindow(window)
{
	for(int i=0;i<10;i++)
	{
		assignWidget(mEffect[i],str(boost::format("effect%1%")%(i+1)));
	}
}

GUIEffectWindow::~GUIEffectWindow()
{

}

bool GUIEffectWindow::GridInputEvent( int x,int y )
{
	return false;
}

void GUIEffectWindow::showScene( std::string arg )
{

}

void GUIEffectWindow::hideScene()
{

}

void GUIEffectWindow::FrameEvent()
{

}