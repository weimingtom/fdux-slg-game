#include "GUIMenu.h"

#include "DataLibrary.h"

#include "LuaSystem.h"

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
			case MainMenuState:
				{
					FadeInOut();

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
	DataLibrary::getSingletonPtr()->setData("GameData/Test/Test1",-1);
	DataLibrary::getSingletonPtr()->setData("GameData/Test/Test2",1);
	DataLibrary::getSingletonPtr()->setData("GameData/Test/Test3",1.1);
	DataLibrary::getSingletonPtr()->setData("GameData/Test/Test4","aaaa");

	DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::GameData,"test1.xml");

	std::cout<<DataLibrary::getSingletonPtr()->getDataI("GameData/Test/Test1")<<std::endl;
	std::cout<<DataLibrary::getSingletonPtr()->getDataUI("GameData/Test/Test2")<<std::endl;
	std::cout<<DataLibrary::getSingletonPtr()->getDataF("GameData/Test/Test3")<<std::endl;
	std::cout<<DataLibrary::getSingletonPtr()->getDataS("GameData/Test/Test4")<<std::endl;

	LuaSystem::getSingletonPtr()->luaCallString("DataLib.SetData(\"GameData/Test/Test1\",\"I\",3)");
	LuaSystem::getSingletonPtr()->luaCallString("print(DataLib.GetData(\"GameData/Test/Test1\",\"I\"))");
}

