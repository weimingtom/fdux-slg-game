#include "GUIOptionWindow.h"

#include "DataLibrary.h"
#include "StringTable.h"

#include "AudioSystem.h"

#include "GUIStage.h"

#define DialogVisibleTime 500
#define SAVE_PATH "..\\save"

GUIOptionWindow::GUIOptionWindow(int width,int height):GUIScene("Option.layout",width,height)
{
	assignWidget(mYesButton,"YesButton");
	assignWidget(mNoButton,"NoButton");
	assignWidget(mCaption,"OptionCaption");
	assignWidget(mMusicVolumeCaption,"MusicVolume");
	assignWidget(mSEVolumeCaption,"SEVolume");
	assignWidget(mTextSpeedCaption,"TextSpeed");
	assignWidget(mMusicScrollBar,"MusicScrollBar");
	assignWidget(mSeScrollBar,"SeScrollBar");
	assignWidget(mTextSpeedScrollBar,"TextSpeedScrollBar");
	assignWidget(mBG,"SLBG");
	assignWidget(mWindow,"OptionWindow");

	mYesButton->setCaption(StringTable::getSingletonPtr()->getString("YesButton"));
	mNoButton->setCaption(StringTable::getSingletonPtr()->getString("NoButton"));
	mCaption->setCaption(StringTable::getSingletonPtr()->getString("Opition"));
	mMusicVolumeCaption->setCaption(StringTable::getSingletonPtr()->getString("MusicVolume"));
	mSEVolumeCaption->setCaption(StringTable::getSingletonPtr()->getString("SEVolume"));
	mTextSpeedCaption->setCaption(StringTable::getSingletonPtr()->getString("TextSpeed"));

	mYesButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIOptionWindow::onYes);
	mNoButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIOptionWindow::onNo);
}

GUIOptionWindow::~GUIOptionWindow(void)
{
}

void GUIOptionWindow::showScene( std::string arg )
{
	if(arg=="mainmenu")
	{
		returnToMainMenu=true;
	}
	else
	{
		returnToMainMenu=false;
	}

	mBG->setVisible(true);
	//读取值
	int MusicVolume=0;
	int SEVolume=0;
	int TextSpeed=0;
	DataLibrary::getSingletonPtr()->getData("SystemConfig/MusicVolume",MusicVolume);
	DataLibrary::getSingletonPtr()->getData("SystemConfig/SEVolume",SEVolume);
	DataLibrary::getSingletonPtr()->getData("SystemConfig/TextSpeed",TextSpeed);
	mMusicScrollBar->setScrollPosition(MusicVolume);
	mSeScrollBar->setScrollPosition(SEVolume);
	mTextSpeedScrollBar->setScrollPosition(TextSpeed);
	FadeIn(DialogVisibleTime,mWindow);
}

void GUIOptionWindow::hideScene()
{
	FadeOut(DialogVisibleTime,mWindow);
}

void GUIOptionWindow::FrameEvent()
{

}

void GUIOptionWindow::SaveData()
{
	//写回值
	DataLibrary::getSingletonPtr()->setData("SystemConfig/MusicVolume",mMusicScrollBar->getScrollPosition());
	DataLibrary::getSingletonPtr()->setData("SystemConfig/SEVolume",mSeScrollBar->getScrollPosition());
	DataLibrary::getSingletonPtr()->setData("SystemConfig/TextSpeed",mTextSpeedScrollBar->getScrollPosition());
	DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string(SAVE_PATH)+std::string("\\Config.xml"));

	AudioSystem::getSingletonPtr()->changeVolume();
	GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
	if (stage!=NULL)
	{
		stage->changeShowTextOptionTime();
	}
}

void GUIOptionWindow::onYes( MyGUI::Widget* _sender )
{
	SaveData();
	hideScene();
}

void GUIOptionWindow::onNo( MyGUI::Widget* _sender )
{
	hideScene();
}

void GUIOptionWindow::onOtherSceneNotify(std::string arg)
{
	if (arg=="FadeOutOver")
	{
		mBG->setVisible(false);

		if(returnToMainMenu)
		{
			GUIScene* stage=GUISystem::getSingletonPtr()->getScene(MenuWindowsScene);
			stage->showScene("");
		}
	}
}