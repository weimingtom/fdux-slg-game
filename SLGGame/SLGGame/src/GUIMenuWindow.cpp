#include "GUIMenuWindow.h"

GUIMenuWindow::GUIMenuWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window),mIsAction(false)
{
	assignWidget(mRestartButton,"MenuRestartButton");
	assignWidget(mSaveButton,"MenuSaveButton");
	assignWidget(mLoadButton,"MenuLoadButton");
	assignWidget(mOptionButton,"MenuOptionButton");
	assignWidget(mExitButton,"MenuExitButton");

	mRestartButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onRestart);
	mExitButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onExit);
}

GUIMenuWindow::~GUIMenuWindow(void)
{
}

void GUIMenuWindow::showScene( std::string arg )
{
	if (!mIsAction)
	{
		mIsAction=true;
		mWindow->setVisible(true);
	}
	else
	{
		mIsAction=false;
		mWindow->setVisible(false);
	}

}

void GUIMenuWindow::hideScene()
{

}

void GUIMenuWindow::FrameEvent()
{

}

bool GUIMenuWindow::GridInputEvent( int x,int y )
{
	return mIsAction;
}

bool GUIMenuWindow::KeyInputEvent( const OIS::KeyEvent &arg )
{
	if (arg.key==OIS::KC_ESCAPE)
	{
		showScene("");
	}
	return false;
}

void GUIMenuWindow::onRestart( MyGUI::Widget* _sender )
{

}

void GUIMenuWindow::onExit( MyGUI::Widget* _sender )
{

}
