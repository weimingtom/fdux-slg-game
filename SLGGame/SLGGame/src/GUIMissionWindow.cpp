#include "GUIMissionWindow.h"

GUIMissionWindow::GUIMissionWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height)
{
	mWindow=window;

	MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
	MyGUI::ControllerFadeAlpha* mFadeController = item->castType<MyGUI::ControllerFadeAlpha>();
	MyGUI::ControllerManager::getInstance().addItem(mWindow,mFadeController);
}

GUIMissionWindow::~GUIMissionWindow(void)
{
	MyGUI::ControllerManager::getInstance().removeItem(mWindow); 
}

void GUIMissionWindow::showScene(std::string arg)
{
	mWindow->setAlpha(0);
	mWindow->setVisible(true);

	mFadeController->setAlpha(1);
	mFadeController->setCoef(1/(1.0/1000.0));
	mFadeController->setEnabled(true);
}

void GUIMissionWindow::hideScene()
{
	mWindow->setAlpha(1);
	mWindow->setVisible(true);

	mFadeController->setAlpha(0);
	mFadeController->setCoef(1/(1.0/1000.0));
	mFadeController->setEnabled(true);
}