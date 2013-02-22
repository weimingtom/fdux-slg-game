#include "GUISLWindow.h"

#include "StringTable.h"

#include <windows.h>
#include <fstream>

#include "DataLibrary.h"

#define SAVE_PATHL L"..\\save"
#define SAVE_PATH "..\\save"

#include "GUIStage.h"
#include "StateManager.h"

#include <boost/format.hpp>

#define DialogVisibleTime 500

GUISLWindow::GUISLWindow(int width,int height):GUIScene("SLWindow.layout",width,height),mStartFade(false),mOldText(NULL),isOk(true),mCallScene(NULL)
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
			std::string name;
			DataLibrary::getSingletonPtr()->getData(str(boost::format("SystemConfig/Save/Save%1%")%(i+1)),name);
			mTextBox->setCaption(name);
			mTextBox->setUserString("FileName",Ogre::StringUtil::split(name," ").front());
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
		MyGUI::TextBox* mTextBox;
		assignWidget(mTextBox,"SaveText1");
		mTextBox->setEnabled(false);
		mTextBox->setTextColour(MyGUI::Colour(0.5,0.5,0.5));
		assignWidget(mTextBox,"SaveText2");
		if(mTextBox->getCaption()=="")
		{
			mTextBox->setCaption("BattleAutoSave");
		}
		mTextBox->setEnabled(false);
		mTextBox->setTextColour(MyGUI::Colour(0.5,0.5,0.5));
		isSave=true;
	}
	else
	{
		mCaption->setCaption(StringTable::getSingletonPtr()->getString("LoadCaption"));
		isSave=false;
	}

	mBG->setAlpha(0);
	mBG->setVisible(true);
	FadeIn(DialogVisibleTime,mBG);	

	buttonLock(false);
}

void GUISLWindow::hideScene()
{
	FadeOut(DialogVisibleTime,mBG);
	
	buttonLock(false);
}

void GUISLWindow::onOtherSceneNotify(std::string arg)
{
	if (arg=="FadeInOver")
	{
		buttonLock(true);
	}
	else if (arg=="FadeOutOver")
	{
		mStartFade=false;
		if(!isSave && isOk && mCallScene!=NULL)
		{
			mCallScene->onOtherSceneNotify("LoadComplete");
		}
		else
		{
			if(mCallScene!=NULL)
				mCallScene->onOtherSceneNotify("Return");
		}
		GUISystem::getSingletonPtr()->destoryScene(SLScene);
	}
}

void GUISLWindow::FrameEvent()
{
	
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
			
			//加入时间戳
			SYSTEMTIME systm;
			GetLocalTime(&systm);
			std::string timeString=str(boost::format(" %1%-%2%-%3% %4%:%5%:%6%")%systm.wYear%systm.wMonth%systm.wDay%systm.wHour%systm.wMinute%systm.wSecond);

			DataLibrary::getSingletonPtr()->setData(str(boost::format("SystemConfig/Save/Save%1%")%mOldText->getUserString("Num")),fileName+timeString);
			DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string(SAVE_PATH)+std::string("\\Config.xml"));
			StateManager::getSingletonPtr()->saveState(std::string(SAVE_PATH)+std::string("\\save")+mOldText->getUserString("Num")+".xml");
		}
		else
		{
			StateManager::getSingletonPtr()->loadState(std::string(SAVE_PATH)+std::string("\\save")+mOldText->getUserString("Num")+".xml");
			if (mCallScene!=NULL)
			{
				mCallScene->onOtherSceneNotify("LoadSelect");
			}
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
		text->setTextColour(MyGUI::Colour::Red);
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
