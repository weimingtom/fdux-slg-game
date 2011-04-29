#include "GUIGameStateWindows.h"

#include "DataLibrary.h"

GUIGameStateWindows::GUIGameStateWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mTurnLabel,"TurnLabel");
	assignWidget(mPlayerLabel,"PlayerLabel");
	window->setPosition(0,0);
}

GUIGameStateWindows::~GUIGameStateWindows(void)
{
}

void GUIGameStateWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUIGameStateWindows::hideScene()
{
	mWindow->setVisible(false);
}

void GUIGameStateWindows::FrameEvent()
{

}

bool GUIGameStateWindows::GridInputEvent( int x,int y )
{
	return true;
}


void GUIGameStateWindows::update()
{
	unsigned int value;
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",value);
	mTurnLabel->setCaption(Ogre::StringConverter::toString(value));
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",value);
	mPlayerLabel->setCaption(Ogre::StringConverter::toString(value));
}
