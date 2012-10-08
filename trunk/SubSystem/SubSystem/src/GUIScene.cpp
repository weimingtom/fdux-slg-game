#include "GUIScene.h"

#ifndef SCRIPT_EDITOR
#include "StringTable.h"
#endif

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

void GUIScene::FadeIn(float time,MyGUI::Widget* fadeWidget)//渐变,以毫秒计算
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

void GUIScene::MoveTo(int left,int top,float time,MyGUI::Widget* moveWidget)//渐变,以毫秒计算
{
	MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerPosition::getClassTypeName());
	MyGUI::ControllerPosition* controller = item->castType<MyGUI::ControllerPosition>();

	controller->setPosition(MyGUI::IntPoint(left,top));
	controller->setTime(time/1000.0);
	controller->setAction(MyGUI::newDelegate(MyGUI::action::inertionalMoveFunction));

	controller->eventPostAction+=MyGUI::newDelegate(this, &GUIScene::EventMoveToPostAction);

	MyGUI::ControllerManager::getInstance().addItem(moveWidget,controller); 

}

void GUIScene::EventMoveToPostAction(MyGUI::Widget* _sender)
{
	onOtherSceneNotify("MoveToOver");
}

void GUIScene::StopMoveTo(MyGUI::Widget* moveWidget)
{
	MyGUI::ControllerManager::getInstance().removeItem(moveWidget); 
	onOtherSceneNotify("MoveToOver");
}

void GUIScene::setSceneLanguage()
{
	for (MyGUI::VectorWidgetPtr::iterator iter = mWidgetList.begin(); iter != mWidgetList.end(); ++iter)
	{
		recursionSetSceneLanguage((*iter));
	}
}

void GUIScene::recursionSetSceneLanguage(MyGUI::Widget* widget)
{
#ifndef SCRIPT_EDITOR
	for (int i=0;i<widget->getChildCount();i++)
	{
		MyGUI::Widget* child=widget->getChildAt(i);
		if(child->getChildCount()==0)
		{
			if(child->getName().substr(0,2)=="T_" || child->getName().substr(0,5)=="TEXT_" )
			{
				if(child->getTypeName()=="TextBox")
				{
					MyGUI::TextBox* textBox=child->castType<MyGUI::TextBox>(child);
					textBox->setCaption(StringTable::getSingleton().getString(textBox->getName()));
				}
				else if(child->getTypeName()=="Button")
				{
					MyGUI::Button* button=child->castType<MyGUI::Button>(child);
					button->setCaption(StringTable::getSingleton().getString(button->getName()));					
				}
			}
		}
		else
		{
			recursionSetSceneLanguage(child);
		}
	}
#endif
}
