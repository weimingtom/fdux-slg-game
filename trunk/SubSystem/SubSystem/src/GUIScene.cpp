#include "GUIScene.h"

GUIScene::GUIScene(std::string layoutFile,int Width,int Height):mContainerWidget(NULL),mLayoutName(layoutFile),mWidth(Width),mHeigth(Height)
{
	mWidgetList=MyGUI::LayoutManager::getInstance().loadLayout(mLayoutName);
}

GUIScene::GUIScene(MyGUI::Widget* containerWidget,int Width,int Height):mContainerWidget(containerWidget),mWidth(Width),mHeigth(Height)
{
}

GUIScene::~GUIScene( void )
{
		if (mContainerWidget==NULL)
		{
			MyGUI::LayoutManager::getInstance().unloadLayout(mWidgetList);
			mWidgetList.clear();
		}
}

void GUIScene::FadeIn(float time,MyGUI::Widget* fadeWidget)//½¥±ä,ÒÔºÁÃë¼ÆËã
{
	MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
	MyGUI::ControllerFadeAlpha* mFadeInController = item->castType<MyGUI::ControllerFadeAlpha>();

	fadeWidget->setAlpha(0);
	fadeWidget->setVisible(true);

	mFadeInController->setAlpha(1);
	mFadeInController->setCoef(1/(time/1000));
	mFadeInController->setEnabled(true);

	mFadeInController->eventPostAction+=MyGUI::newDelegate(this, &GUIScene::EventFadeInPostAction);

	MyGUI::ControllerManager::getInstance().addItem(fadeWidget,mFadeInController); 

}

void GUIScene::EventFadeInPostAction(MyGUI::Widget* _sender)
{
	onOtherSceneNotify("FadeInOver");
}

void GUIScene::StopFadeIn(MyGUI::Widget* fadeWidget)
{
	MyGUI::ControllerManager::getInstance().removeItem(fadeWidget); 
	onOtherSceneNotify("FadeInOver");
}

void GUIScene::FadeOut(float time,MyGUI::Widget* fadeWidget)
{
	MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
	MyGUI::ControllerFadeAlpha* mFadeOutController = item->castType<MyGUI::ControllerFadeAlpha>();

	fadeWidget->setAlpha(1);
	fadeWidget->setVisible(true);

	mFadeOutController->setAlpha(0);
	mFadeOutController->setCoef(1/(time/1000));
	mFadeOutController->setEnabled(true);

	mFadeOutController->eventPostAction+=MyGUI::newDelegate(this, &GUIScene::EventFadeOutPostAction);

	MyGUI::ControllerManager::getInstance().addItem(fadeWidget,mFadeOutController); 
}

void GUIScene::EventFadeOutPostAction(MyGUI::Widget* _sender)
{
	onOtherSceneNotify("FadeOutOver");
}

void GUIScene::StopFadeOut(MyGUI::Widget* fadeWidget)
{
	MyGUI::ControllerManager::getInstance().removeItem(fadeWidget); 
	onOtherSceneNotify("FadeOutOver");
}