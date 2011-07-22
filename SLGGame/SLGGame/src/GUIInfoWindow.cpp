#include "GUIInfoWindow.h"

#define TICKTIME 5
#define WAITTIME 500

GUIInfoWindow::GUIInfoWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height)
{
	mWindow=window;
	assignWidget(mCaption,"Caption");
	isStart=false;
	mSetpDirection=true;
	mTickTime=0;
}

GUIInfoWindow::~GUIInfoWindow(void)
{
}

void GUIInfoWindow::showScene( std::string arg )
{
	mWindow->setAlpha(0);
	mWindow->setVisible(true);
	mSetp=0;
	mSetpDirection=true;
	mTickTime=0;
	isStart=true;
	isWait=false;
}

void GUIInfoWindow::hideScene()
{
	mWindow->setVisible(false);
}

void GUIInfoWindow::FrameEvent()
{
	if (isStart)
	{
		mTickTime+=mTimer.getMilliseconds();
		mTimer.reset();
		if (!isWait)
		{
			if (mTickTime>=TICKTIME)
			{
				mTickTime=0;
				if (mSetpDirection)
				{
					mSetp+=0.05;
					if (mSetp>=1)
					{
						mSetpDirection=false;
						isWait=true;
					}
				}
				else
				{
					mSetp-=0.05;
					if (mSetp<=0)
					{
						mWindow->setVisible(false);
						mSetp=0;
						isStart=false;
					}
				}
				mWindow->setAlpha(mSetp);
			}
		}
		else
		{
			if (mTickTime>=WAITTIME)
			{
				isWait=false;
			}
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
