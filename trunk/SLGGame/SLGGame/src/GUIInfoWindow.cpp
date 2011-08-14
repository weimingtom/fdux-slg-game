#include "GUIInfoWindow.h"

#define FADETIME 500
#define WAITTIME 1000

#include "Framerate.h"

GUIInfoWindow::GUIInfoWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height)
{
	mWindow=window;
	assignWidget(mCaption,"Caption");
}

GUIInfoWindow::~GUIInfoWindow(void)
{
}

void GUIInfoWindow::showScene( std::string arg )
{
	mWindow->setAlpha(0);
	mWindow->setVisible(true);
	isWait=false;
	FadeIn(FADETIME,mWindow);
}

void GUIInfoWindow::hideScene()
{
	mWindow->setVisible(false);
}

void GUIInfoWindow::onOtherSceneNotify(std::string arg)
{
	if (arg=="FadeInOver")
	{
		isWait=true;
		mTimer.reset();
	}
	else if(arg=="FadeOutOver")
	{
		mWindow->setVisible(false);
	}
}

void GUIInfoWindow::FrameEvent()
{
	if (isWait)
	{
		if (mTimer.getMilliseconds()>=WAITTIME)
		{
			isWait=false;
			FadeOut(FADETIME,mWindow);
		}
	}
}

bool GUIInfoWindow::GridInputEvent( int x,int y )
{
	return true;
}

void GUIInfoWindow::setCaption( std::string text,MyGUI::Colour c )
{
	mCaption->setCaption(text);
	mCaption->setTextColour(c);
}
