#include "GUISLWindow.h"

#include "StringTable.h"

#include <windows.h>

#include "DataLibrary.h"

#define SAVE_PATHL L"..\\save"
#define SAVE_PATH "..\\save"

#include "GUIStage.h"
#include "StateManager.h"

GUISLWindow::GUISLWindow(int width,int height):GUIScene("SLWindow.layout",width,height),mStartFade(false),mOldText(NULL)
{
	assignWidget(mYesButton,"YesButton");
	assignWidget(mNoButton,"NoButton");
	assignWidget(mCaption,"SLCaption");
	assignWidget(mFileName,"FileNameEdit");
	assignWidget(mBG,"SLBG");
	assignWidget(mWindow,"SLWindow");
	
	mYesButton->setCaption(StringTable::getSingletonPtr()->getString("YesButton"));
	mNoButton->setCaption(StringTable::getSingletonPtr()->getString("NoButton"));
	mBG->setSize(width,height);

	for (int i=0;i<7;i++)
	{
		MyGUI::TextBox* mTextBox;
		assignWidget(mTextBox,std::string("SaveText")+Ogre::StringConverter::toString(i+1));
		mTextBox->setUserString("Num",Ogre::StringConverter::toString(i+1));
		mTextBox->eventMouseButtonClick+=MyGUI::newDelegate(this, &GUISLWindow::onSaveTextClick);
		//检查文件名是否存在
		WIN32_FIND_DATAA fd;

		HANDLE hFind = ::FindFirstFileA((std::string(SAVE_PATH)+std::string("\\save")+Ogre::StringConverter::toString(i+1)+std::string(".xml")).c_str(), &fd);

		if(hFind != INVALID_HANDLE_VALUE)
		{
			DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::SystemConfig,std::string(SAVE_PATH)+std::string("\\save")+Ogre::StringConverter::toString(i+1)+".xml",false);
			std::string name;
			DataLibrary::getSingletonPtr()->getData("SystemConfig/StoryData/FileName",name);
			mTextBox->setCaption(name);
			mTextBox->setUserString("FileName",name);
		}
		else
		{
			mTextBox->setCaption(StringTable::getSingletonPtr()->getString("NoFile"));
			mTextBox->setUserString("FileName","");
		}
	}
	assignWidget(mWindow,"SLWindow");

	mYesButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUISLWindow::onYes);
	mNoButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUISLWindow::onNo);
}

GUISLWindow::~GUISLWindow(void)
{
}

void GUISLWindow::showScene( std::string arg )
{
	if (arg=="save")
	{
		mCaption->setCaption(StringTable::getSingletonPtr()->getString("SaveCaption"));
		isSave=true;
	}
	else
	{
		mCaption->setCaption(StringTable::getSingletonPtr()->getString("LoadCaption"));
		isSave=false;
	}

	mSetp=0;
	mSetpDirection=true;

	mBG->setAlpha(mSetp);
	mBG->setVisible(true);
	mFadeWidget=mBG;
	mStartFade=true;

	mTimerWork=FadeInOutWork;
	mTickTime=DefaultDialogVisibleTime*1000/100;

	buttonLock(false);

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(SLScene);
}

void GUISLWindow::hideScene()
{
	mSetp=1;
	mSetpDirection=false;

	mBG->setAlpha(mSetp);
	mBG->setVisible(true);
	mFadeWidget=mBG;
	mStartFade=true;

	mTimerWork=FadeInOutWork;
	mTickTime=DefaultDialogVisibleTime*1000/100;
	
	buttonLock(false);

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(SLScene);
}

void GUISLWindow::FrameEvent()
{
	if (mTimer.getMilliseconds()>=mTickTime)
	{
		//复位定时器
		mTimer.reset();
		FadeInOut();
	}

	if (mStartFade && mTimerWork==NoneWork)
	{
		if (mSetpDirection==false)
		{
			mStartFade=false;
			if(!isSave && isOk)
			{
				mCallScene->onOtherSceneNotify("LoadComplete");
			}
			else
			{
				mCallScene->onOtherSceneNotify("Return");
			}
			GUISystem::getSingletonPtr()->destoryScene(SLScene);
		}
		else
		{
			buttonLock(true);
		}
	}
	
}

void GUISLWindow::onYes( MyGUI::Widget* _sender )
{
	if(mOldText!=NULL)
	{
		if (isSave)
		{
			std::string fileName;
			if (mFileName->getCaption()=="")
			{
				fileName="NoName";
			}
			else
			{
				fileName=mFileName->getCaption();
			}

			DataLibrary::getSingletonPtr()->setData("GameData/StoryData/FileName",fileName);
			StateManager::getSingletonPtr()->saveState(std::string(SAVE_PATH)+std::string("\\save")+mOldText->getUserString("Num")+".xml");
		}
		else
		{
			StateManager::getSingletonPtr()->loadState(std::string(SAVE_PATH)+std::string("\\save")+mOldText->getUserString("Num")+".xml");
			mCallScene->onOtherSceneNotify("LoadSelect");
		}
		
		isOk=true;
		hideScene();
	}
}

void GUISLWindow::onNo( MyGUI::Widget* _sender )
{
	isOk=false;
	hideScene();
}

void GUISLWindow::onSaveTextClick( MyGUI::Widget* _sender )
{
	MyGUI::TextBox* text=(MyGUI::TextBox*)_sender;
	if (mOldText!=text)
	{
		text->setTextColour(MyGUI::Colour::Blue);
		mFileName->setCaption(text->getUserString("FileName"));
		if (mOldText!=NULL)
		{
			mOldText->setTextColour(MyGUI::Colour::White);
		}
		mOldText=text;
	}
}

void GUISLWindow::setCallScene( GUIScene* scene )
{
	mCallScene=scene;
}

void GUISLWindow::buttonLock( bool islock )
{
	mYesButton->setEnabled(islock);
	mNoButton->setEnabled(islock);
}
