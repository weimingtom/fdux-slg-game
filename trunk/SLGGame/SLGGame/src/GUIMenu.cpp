#include "GUIMenu.h"

#include "DataLibrary.h"

#include "Core.h"
#include "LuaSystem.h"

#include "StateManager.h"

#include <iostream>

GUIMenu::GUIMenu(int width,int height):GUIScene(width,height,"MainMenu.layout"),mMenuState(NoneState)
{
	assignWidget(mLogoImage,"LogoImage");
	assignWidget(mMenuImage,"BackGround");

	assignWidget(mNewGame,"New");
	assignWidget(mExit,"Exit");

	mLogoImage->setSize(width,height);
	mMenuImage->setSize(width,height);

	mNewGame->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onNewGame);
	mExit->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onExit);
	setButtonLock(false);
}

GUIMenu::~GUIMenu(void)
{
}

void GUIMenu::showScene( std::string arg )
{
	if (arg=="logo")
	{
		mMenuState=LogoState;
		mMenuImage->setVisible(false);
		mLogoImage->setAlpha(0);
		mLogoImage->setVisible(true);
		mFadeWidget=mLogoImage;
	} 
	else
	{
		mMenuState=MainMenuState;
		mMenuImage->setAlpha(0);
		mMenuImage->setVisible(true);
		mLogoImage->setVisible(false);
		mFadeWidget=mMenuImage;
	}
	
	mSetp=0;
	mSetpDirection=true;//从无到有方向
	mTimerWork=FadeInOutWork;
	mTickTime=2*1000/100;

	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
}

void GUIMenu::hideScene()
{

}

void GUIMenu::FrameEvent()
{
	if(mTickTime!=0)
	{
		if (mTimer.getMilliseconds()>=mTickTime)
		{
			//复位定时器
			mTimer.reset();

			switch(mMenuState)
			{
			case LogoState:
				{
					FadeInOut();

					if (mTimerWork==NoneWork)
					{
						if (mSetpDirection)
						{
							mMenuState=WaitState;
							mTickTime=3000;
							GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
						}
						else
						{
							showScene("");//开始显示主菜单
						}
					}

					break;
				}
			case NewState:
				{
					FadeInOut();

					if (mTimerWork==NoneWork)
					{
						StateManager::getSingletonPtr()->changeState("Chapter1.lua",StateManager::AVG);
					}

					break;
				}
			case MainMenuState:
				{
					FadeInOut();

					if (mTimerWork==NoneWork)
					{
						setButtonLock(true);
					}

					break;
				}
			case ExitState:
				{
					FadeInOut();

					if (mTimerWork==NoneWork)
					{
						Core::getSingletonPtr()->stop();
					}

					break;
				}
			case WaitState:
				{
					mMenuState=LogoState;
					
					mSetp=1;
					mSetpDirection=false;//从无到有方向
					mTimerWork=FadeInOutWork;
					mTickTime=2*1000/100;

					mTimer.reset();
					GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
					
					break;
				}
			}
		}
	}
}

void GUIMenu::onNewGame( MyGUI::Widget* _sender )
{
	setButtonLock(false);

	mMenuState=NewState;
	mSetp=1;
	mSetpDirection=false;//从无到有方向
	mTimerWork=FadeInOutWork;
	mTickTime=2*1000/100;

	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
}

void GUIMenu::onExit( MyGUI::Widget* _sender )
{
	setButtonLock(false);

	mMenuState=ExitState;
	mSetp=1;
	mSetpDirection=false;//从无到有方向
	mTimerWork=FadeInOutWork;
	mTickTime=2*1000/100;

	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
}

void GUIMenu::setButtonLock( bool isLock )
{
	mNewGame->setEnabled(isLock);
	mExit->setEnabled(isLock);
}

