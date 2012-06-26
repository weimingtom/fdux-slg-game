#include "GUIMenu.h"

#include "DataLibrary.h"
#include "StringTable.h"

#include "Core.h"
#include "LuaSystem.h"
#include "GUISLWindow.h"
#include "GUIOptionWindow.h"

#include "StateManager.h"
#include "AudioSystem.h"

#include <iostream>

#define FadeTime 1500
#define WaitTime 2000

GUIMenu::GUIMenu(int width,int height):GUIScene("MainMenu.layout",width,height),mMenuState(NoneState),SLWindow(NULL),mOptionWindow(NULL)
{
	assignWidget(mLogoImage,"LogoImage");
	assignWidget(mMenuImage,"BackGround");

	assignWidget(mNewGame,"New");
	assignWidget(mLoad,"Load");
	assignWidget(mOpiton,"Opiton");
	assignWidget(mExit,"Exit");
	assignWidget(mSupport,"Support");

	mLogoImage->setSize(width,height);
	mMenuImage->setSize(width,height);

	std::string data;
	mNewGame->setCaption(StringTable::getSingleton().getString("NewGame"));
	mNewGame->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onNewGame);
	mLoad->setCaption(StringTable::getSingleton().getString("LoadGame"));
	mLoad->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onLoad);
	mOpiton->setCaption(StringTable::getSingleton().getString("Opition"));
	mOpiton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onOpiton);
	mExit->setCaption(StringTable::getSingleton().getString("ExitGame"));
	mExit->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onExit);
	mSupport->setCaption(StringTable::getSingleton().getString("Supprot"));
	mSupport->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onSupprot);
	setButtonLock(false);
}

GUIMenu::~GUIMenu(void)
{
	if (SLWindow!=NULL)
	{
		SLWindow->setCallScene(SLWindow);
	}
	AudioSystem::getSingletonPtr()->stopStream(500);
}

void GUIMenu::showScene( std::string arg )
{
	if (arg=="logo")
	{
		mMenuState=LogoState;
		mMenuImage->setVisible(false);
		mLogoImage->setAlpha(0);
		mLogoImage->setVisible(true);
		FadeIn(FadeTime,mLogoImage);
	} 
	else
	{
		mMenuState=MainMenuState;
		mMenuImage->setAlpha(0);
		mMenuImage->setVisible(true);
		mLogoImage->setVisible(false);
		FadeIn(FadeTime,mMenuImage);
		AudioSystem::getSingletonPtr()->playStream("op.mp3",true,0);
	}
	
}

void GUIMenu::hideScene()
{

}

void GUIMenu::onOtherSceneNotify(std::string arg)
{
	if (arg=="FadeInOver")
	{
		switch(mMenuState)
		{
		case LogoState:
			 {
				mMenuState=WaitState;
				mTickTime=WaitTime;
				mTimer.reset();
				GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
				break;
			 }
		case  MainMenuState:
			  {
				  setButtonLock(true);
				  break;
			  }
		}
	}
	else if (arg=="FadeOutOver")
	{
		switch(mMenuState)
		{
		case LogoState:
			 {
				showScene("");
				break;
			 }
		case NewState:
			 {
				 DataLibrary::getSingleton().delNode(std::string("GameData/StoryData"));
				 StateManager::getSingletonPtr()->changeState("Chapter1.lua",StateManager::AVG);
				 break;
			 }
		case SupprotState:
			{
				DataLibrary::getSingleton().delNode(std::string("GameData/StoryData"));
				StateManager::getSingletonPtr()->changeState("",StateManager::Supply);
				break;
			}
		case ExitState:
			  {
				  Core::getSingletonPtr()->stop();
				  break;
			  }
		}
	}
}

void GUIMenu::FrameEvent()
{
	if(mTickTime!=0)
	{
		if (mTimer.getMilliseconds()>=mTickTime)
		{
			//¸´Î»¶¨Ê±Æ÷
			mTimer.reset();

			switch(mMenuState)
			{
			case WaitState:
				{
					mMenuState=LogoState;
					
					FadeOut(FadeTime,mLogoImage);

					GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
					
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
	
	FadeOut(FadeTime,mMenuImage);
}

void GUIMenu::onExit( MyGUI::Widget* _sender )
{
	setButtonLock(false);

	mMenuState=ExitState;

	FadeOut(FadeTime,mMenuImage);
}

void GUIMenu::setButtonLock( bool isLock )
{
	mNewGame->setEnabled(isLock);
	mLoad->setEnabled(isLock);
	mOpiton->setEnabled(isLock);
	mExit->setEnabled(isLock);
}

void GUIMenu::onLoad( MyGUI::Widget* _sender )
{
	SLWindow= (GUISLWindow*)GUISystem::getSingletonPtr()->createScene(SLScene);
	SLWindow->setCallScene(this);
	SLWindow->showScene("load");
}

void GUIMenu::onOpiton( MyGUI::Widget* _sender )
{
	mOptionWindow= (GUIOptionWindow*)GUISystem::getSingletonPtr()->createScene(OptionWindowScene);
	mOptionWindow->showScene("");
}

void GUIMenu::onSupprot(MyGUI::Widget* _sender)
{
	setButtonLock(false);

	mMenuState=SupprotState;

	FadeOut(FadeTime,mMenuImage);
}
