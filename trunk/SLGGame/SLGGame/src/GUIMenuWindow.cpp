#include "GUIMenuWindow.h"

#include "StringTable.h"

#include "StateManager.h"
#include "LuaSystem.h"
#include "GUISLWindow.h"
#include "GUIOptionWindow.h"

GUIMenuWindow::GUIMenuWindow(int Width,int Height):GUIScene("SystemMenu.layout",Width,Height)
{
	assignWidget(mWindow,"BlackGround");
	assignWidget(mRestartButton,"MenuRestartButton");
	assignWidget(mSaveButton,"MenuSaveButton");
	assignWidget(mLoadButton,"MenuLoadButton");
	assignWidget(mOptionButton,"MenuOptionButton");
	assignWidget(mExitButton,"MenuExitButton");

	mRestartButton->setCaption(StringTable::getSingletonPtr()->getString("Restart"));
	mSaveButton->setCaption(StringTable::getSingletonPtr()->getString("SaveButton"));
	mLoadButton->setCaption(StringTable::getSingletonPtr()->getString("LoadButton"));
	mOptionButton->setCaption(StringTable::getSingletonPtr()->getString("OpitionButton"));
	mExitButton->setCaption(StringTable::getSingletonPtr()->getString("ExitGame"));

	mRestartButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onRestart);
	mSaveButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onSave);
	mLoadButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onLoad);
	mOptionButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onOption);
	mExitButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMenuWindow::onExit);
}

GUIMenuWindow::~GUIMenuWindow(void)
{
}

void GUIMenuWindow::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUIMenuWindow::hideScene()
{
	mWindow->setVisible(false);
}

bool GUIMenuWindow::getVisible()
{
	return mWindow->getVisible();
}

void GUIMenuWindow::FrameEvent()
{

}

void GUIMenuWindow::onRestart( MyGUI::Widget* _sender )
{
	hideScene();
}

void GUIMenuWindow::onExit( MyGUI::Widget* _sender )
{
	hideScene();
	GUISystem::getSingletonPtr()->destoryScene(MenuWindowsScene);
	LuaSystem::getSingletonPtr()->clearLuaSystem();
	StateManager::getSingletonPtr()->changeState("",StateManager::Menu);
}

void GUIMenuWindow::onSave( MyGUI::Widget* _sender )
{
	GUISLWindow* SLWindow= (GUISLWindow*)GUISystem::getSingletonPtr()->createScene(SLScene);
	mWindow->setVisible(false);
	SLWindow->setCallScene(this);
	SLWindow->showScene("save");
}

void GUIMenuWindow::onLoad( MyGUI::Widget* _sender )
{
	GUISLWindow* SLWindow= (GUISLWindow*)GUISystem::getSingletonPtr()->createScene(SLScene);
	mWindow->setVisible(false);
	SLWindow->setCallScene(this);
	SLWindow->showScene("load");
}

void GUIMenuWindow::onOption( MyGUI::Widget* _sender )
{
	GUIOptionWindow* OptionWindow= (GUIOptionWindow*)GUISystem::getSingletonPtr()->createScene(OptionWindowScene);
	OptionWindow->showScene("mainmenu");
	mWindow->setVisible(false);
}

void GUIMenuWindow::onOtherSceneNotify(std::string arg)
{
	if (arg=="Return")
	{
		mWindow->setVisible(true);
	}
}