#include "GUIMenu.h"

#include "DataLibrary.h"
#include "StringTable.h"

#include "Core.h"
#include "LuaSystem.h"
#include "GUISLWindow.h"
#include "GUIOptionWindow.h"

#include "StateManager.h"
#include "AudioSystem.h"
#include "UtilsOgreDshow.h"

#include <iostream>
#include <Windows.h>

#define FadeTime 1500
#define WaitTime 2000

BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(lpPath, &fd);
	BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;
	BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
	FindClose(hFind);
	return RetValue;
}

GUIMenu::GUIMenu(int width,int height):GUIScene("MainMenu.layout",width,height),mMenuState(NoneState),SLWindow(NULL),mOptionWindow(NULL)
{
	assignWidget(mLogoImage,"LogoImage");
	assignWidget(mMenuImage,"BackGround");
	assignWidget(mPlaneImage,"Plane");

	assignWidget(mNewGame,"New");
	assignWidget(mLoad,"Load");
	assignWidget(mOpiton,"Opiton");
	assignWidget(mExit,"Exit");

	mLogoImage->setSize(width,height);
	mMenuImage->setSize(width,height);

	std::string data;
	mNewGame->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onNewGame);
	mLoad->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onLoad);
	mOpiton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onOpiton);
	mExit->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenu::onExit);
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
		mPlaneImage->setVisible(false);
		mMenuImage->setVisible(false);
		mLogoImage->setAlpha(0);
		mLogoImage->setVisible(true);
		FadeIn(FadeTime,mLogoImage);
	}
	else if(arg=="avi")
	{
		mMenuState=OPState;
		mIsSkipOP=false;
		if(FindFirstFileExists(L"../Media/movie/op.avi", FALSE))
		{
			OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("videotest","../Media/movie/op.avi",1280,720);
		}
		else
		{
			OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("videotest","../Media/movie/op.wmv",1280,720);
		}
		GUISystem::getSingletonPtr()->setFrameUpdateScene(MenuScene);
	}
	else
	{
		mMenuState=MainMenuState;
		mMenuImage->setAlpha(0);
		mPlaneImage->setVisible(true);
		mMenuImage->setVisible(true);
		mLogoImage->setVisible(false);
		mPlaneImage->setPosition(0,200);
		mNewGame->setAlpha(0);
		mLoad->setAlpha(0);
		mOpiton->setAlpha(0);
		mExit->setAlpha(0);
		FadeIn(FadeTime,mMenuImage);
		AudioSystem::getSingletonPtr()->playStream("op.ogg",true,0);
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
				  MoveTo(0,0,1000,mPlaneImage);
				  setButtonLock(true);
				  break;
			  }
		}
	}
	else if(arg=="MoveToOver")
	{
		FadeIn(1000,mNewGame);
		FadeIn(1000,mLoad);
		FadeIn(1000,mOpiton);
		FadeIn(1000,mExit);
		mMenuState=PlaneState;
	}
	else if (arg=="FadeOutOver")
	{
		switch(mMenuState)
		{
		case LogoState:
			 {
				showScene("avi");
				break;
			 }
		case NewState:
			 {
				 DataLibrary::getSingleton().delNode(std::string("GameData/StoryData"));
				 StateManager::getSingletonPtr()->changeState("cp0.lua",StateManager::AVG);
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

	if ((mMenuState==OPState && OgreUtils::DirectShowManager::getSingleton().isPlayOver()) || (mMenuState==OPState && mIsSkipOP))
	{
		GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
		OgreUtils::DirectShowManager::getSingleton().DestroyAll();
		showScene("");
	}
}

void GUIMenu::keyPressed(const OIS::KeyEvent &arg)
{
	if(arg.key==OIS::KC_ESCAPE && mMenuState==OPState)
	{
		mIsSkipOP=true;
	}
}

void GUIMenu::onNewGame( MyGUI::Widget* _sender )
{
	setButtonLock(false);

	mMenuState=NewState;
	
	FadeOut(FadeTime,mMenuImage);
	FadeOut(FadeTime,mPlaneImage);
}

void GUIMenu::onExit( MyGUI::Widget* _sender )
{
	setButtonLock(false);

	mMenuState=ExitState;

	FadeOut(FadeTime,mMenuImage);
	FadeOut(FadeTime,mPlaneImage);
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
