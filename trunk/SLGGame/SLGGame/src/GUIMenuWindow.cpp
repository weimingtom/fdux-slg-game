#include "GUIMenuWindow.h"

#include "StringTable.h"

GUIMenuWindow::GUIMenuWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{

	assignWidget(mRestartButton,"MenuRestartButton");
	assignWidget(mSaveButton,"MenuSaveButton");
	assignWidget(mLoadButton,"MenuLoadButton");
	assignWidget(mOptionButton,"MenuOptionButton");
	assignWidget(mExitButton,"MenuExitButton");

	mRestartButton->setCaption(StringTable::getSingletonPtr()->getString("Restart"));
	mSaveButton->setCaption(StringTable::getSingletonPtr()->getString("SaveButton"));
	mLoadButton->setCaption(StringTable::getSingletonPtr()->getString("LoadButton"));
	mOptionButton->setCaption(StringTable::getSingletonPtr()->getString("Opition"));
	mExitButton->setCaption(StringTable::getSingletonPtr()->getString("ExitGame"));

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
