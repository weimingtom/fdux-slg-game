#include "GUIGameOver.h"

#define FADETIME 500
#define WAITTIME 1000

#include "Framerate.h"
#include "StringTable.h"

#include "BattleOverState.h"

#include "GUIBattle.h"
#include "StateManager.h"

GUIGameOver::GUIGameOver(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height)
{
	mWindow=window;
	assignWidget(mCaption,"InfoImage");
	assignWidget(mGold,"GetMoney");
	assignWidget(mExp,"GetExp");
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

void GUIGameOver::setData(std::string gold,std::string exp)
{
	mGold->setCaption(gold);
	mExp->setCaption(exp);
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