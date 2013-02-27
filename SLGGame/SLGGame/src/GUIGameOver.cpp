#include "GUIGameOver.h"

#define FADETIME 500
#define WAITTIME 1000

#include "Framerate.h"
#include "StringTable.h"

#include "BattleOverState.h"

#include "GUIBattle.h"
#include "StateManager.h"

#include "DataLibrary.h"
#include "boost/format.hpp"

GUIGameOver::GUIGameOver(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height)
{
	mWindow=window;
	assignWidget(mCaption,"InfoImage");
	assignWidget(mGold,"GetMoney");
	assignWidget(mSquadWage,"SquadWage");
	assignWidget(mButton,"TEXT_YesButton");

	mButton->setCaption(StringTable::getSingleton().getString("YesButton"));
	mButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIGameOver::onConfirm);
}

GUIGameOver::~GUIGameOver(void)
{
}

void GUIGameOver::showScene( std::string arg )
{
	mBattleState->ChangeState(new BattleOverState(""));

	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));

	guibattle->hideAllWindows();
	if(arg=="win")
	{
		mCaption->setImageTexture("text_succes.png");
		mButton->setCaption(StringTable::getSingleton().getString("YesButton"));
		isWin=true;
	}
	else
	{
		mCaption->setImageTexture("text_fail.png");
		mButton->setCaption(StringTable::getSingleton().getString("ReturnMainWindow"));
		isWin=false;
	}

	int totalWage=0;
	std::vector<std::string> squad=DataLibrary::getSingletonPtr()->getChildList("GameData/StoryData/SquadData");
	for(std::vector<std::string>::iterator it=squad.begin();it!=squad.end();it++)
	{
		std::string retainerId;
		DataLibrary::getSingletonPtr()->getData(str(boost::format("GameData/StoryData/SquadData/%1%/RetainerId")%(*it)),retainerId);
		
		if(retainerId!="none")
		{
			int wage;
			DataLibrary::getSingletonPtr()->getData(str(boost::format("StaticData/RetainerData/%1%/Wage")%retainerId),wage);

			totalWage+=wage;
		}
	}

	int gold=0;
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/Gold",gold);
	if(gold-totalWage<0)
	{
		gold=0;
	}
	else
	{
		gold-=totalWage;
	}

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/Gold",gold);
	mSquadWage->setCaption(Ogre::StringConverter::toString(totalWage));

	mWindow->setAlpha(0);
	mWindow->setVisible(true);
	FadeIn(FADETIME,mWindow);
}

void GUIGameOver::hideScene()
{
	mWindow->setVisible(false);
}

void GUIGameOver::onOtherSceneNotify(std::string arg)
{
	if (arg=="FadeInOver")
	{
		
	}
	else if(arg=="FadeOutOver")
	{
		mWindow->setVisible(false);
	}
}

void GUIGameOver::FrameEvent()
{

}

bool GUIGameOver::GridInputEvent( int x,int y )
{
	return true;
}

void GUIGameOver::setData(int gold)
{
	mGold->setCaption(Ogre::StringConverter::toString(gold));
}

void GUIGameOver::setNext(std::string name)
{
	mNext=name;
}

void GUIGameOver::onConfirm(MyGUI::Widget* _sender)
{
	if(isWin)
	{
		StateManager::getSingleton().changeState(mNext, StateManager::AVG);
	}
	else
	{
		StateManager::getSingleton().changeState("", StateManager::Menu);
	}
}