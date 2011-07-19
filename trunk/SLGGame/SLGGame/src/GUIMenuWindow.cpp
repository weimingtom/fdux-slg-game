#include "GUIMenuWindow.h"

GUIMenuWindow::GUIMenuWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	mWindow->setPosition(Width/2-mWindow->getWidth(),Height/2-mWindow->getHeight());

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
	mWindow->setVisible(true);
}

void GUIMenuWindow::hideScene()
{
	mWindow->setVisible(false);
}

bool GUIMenuWindow::getVisible()
{
	return mWindow->getVisible();
}

void GUIMenuWindow::FrameEvent()
{

}

bool GUIMenuWindow::GridInputEvent( int x,int y )
{
	return false;
}

bool GUIMenuWindow::KeyInputEvent( const OIS::KeyEvent &arg )
{
	return false;
}

void GUIMenuWindow::onRestart( MyGUI::Widget* _sender )
{
	hideScene();
}

void GUIMenuWindow::onExit( MyGUI::Widget* _sender )
{

}
