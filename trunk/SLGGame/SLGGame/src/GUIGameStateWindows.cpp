#include "GUIGameStateWindows.h"

#include "DataLibrary.h"

#include "StringTable.h"

GUIGameStateWindows::GUIGameStateWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mTurnLabel,"TurnLabel");
	assignWidget(mPlayerLabel,"PlayerLabel");
	assignWidget(mNextTurn,"NextTurnButton");
	mNextTurn->setCaption(StringTable::getSingletonPtr()->getString("NextTurn"));

	MyGUI::TextBox* textBox;
	assignWidget(textBox,"GameTurnLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("GameTurn"));
	assignWidget(textBox,"CurTeamLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("CurTeam"));

	mNextTurn->setEnabled(false);
	window->setPosition(0,0);

	mNextTurn->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIGameStateWindows::onNextTurn);
}

GUIGameStateWindows::~GUIGameStateWindows(void)
{
}

void GUIGameStateWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
	update();
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
	int val;
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/Ture",val);
	mTurnLabel->setCaption(Ogre::StringConverter::toString(val));
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/BattleState/CurTeam",val);
	std::string temppath,tempstr;
	temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(val) + std::string("/FactionId");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	temppath = std::string("StaticData/FactionData/") + tempstr + std::string("/Name");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	mPlayerLabel->setCaption(tempstr);
}

void GUIGameStateWindows::onNextTurn(MyGUI::Widget* _sender)
{
	if(mBattleState)
		mBattleState->PopState();
}