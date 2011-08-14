#pragma once

#include "GUICommon.h"
#include "GUISystem.h"
#include <MyGUI.h>

class GUIScene
{
public:
	GUIScene(std::string layoutFile,int Width,int Height):mContainerWidget(NULL),mLayoutName(layoutFile),mWidth(Width),mHeigth(Height)
	{
		mWidgetList=MyGUI::LayoutManager::getInstance().loadLayout(mLayoutName);
	}

	GUIScene(MyGUI::Widget* containerWidget,int Width,int Height):mContainerWidget(containerWidget),mWidth(Width),mHeigth(Height)
	{
	}

	virtual ~GUIScene(void)
	{
		if (mContainerWidget==NULL)
		{
			MyGUI::LayoutManager::getInstance().unloadLayout(mWidgetList);
			mWidgetList.clear();
		}
	}

	virtual void showScene(std::string arg)=0;//显示场景
	virtual void hideScene()=0;//隐藏场景

	//当其他场景需要通知自己时
	virtual void onOtherSceneNotify(std::string arg){};

	virtual void FrameEvent()=0;//帧事件

	virtual GUISceneType getType()=0;

	virtual void keyPressed(const OIS::KeyEvent &arg){};
	virtual void keyReleased(const OIS::KeyEvent &arg){};

	int mWidth;
	int mHeigth;

protected:
	template <typename T>
	void assignWidget(T * & _widget, const std::string& _name, bool _throw = true)
	{
		_widget = nullptr;
		MyGUI::Widget* find=NULL;

		if (mContainerWidget==NULL)
		{
			for (MyGUI::VectorWidgetPtr::iterator iter = mWidgetList.begin(); iter != mWidgetList.end(); ++iter)
			{
				find= (*iter)->findWidget( _name);
				if (nullptr != find)
				{
					break;
				}
			}
		}
		else
		{
			find = mContainerWidget->findWidget( _name);
		}

		if (find!=NULL)
		{
			T* cast = find->castType<T>(false);
			if (nullptr != cast)
			{
				_widget = cast;
			}
			else if (_throw)
			{
				MYGUI_EXCEPT("Error cast : dest type = '" << T::getClassTypeName()
					<< "' source name = '" << find->getName()
					<< "' source type = '" << find->getTypeName() << "' in layout '" << mLayoutName << "'");
			}
		}
		else
		{
			MYGUI_ASSERT( ! _throw, "widget name '" << _name << "' in layout '" << mLayoutName << "' not found.");
		}
	}

	MyGUI::VectorWidgetPtr mWidgetList;
	MyGUI::Widget* mContainerWidget;
	std::string mLayoutName;

	void FadeIn(float time,MyGUI::Widget* fadeWidget)//渐变,以毫秒计算
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

	void EventFadeInPostAction(MyGUI::Widget* _sender)
	{
		onOtherSceneNotify("FadeInOver");
	}

	void FadeOut(float time,MyGUI::Widget* fadeWidget)
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

	void EventFadeOutPostAction(MyGUI::Widget* _sender)
	{
		onOtherSceneNotify("FadeOutOver");
	}

};

class GUISceneFactory
{
public:
	GUISceneFactory()
	{
	}

	virtual ~GUISceneFactory(void)
	{
	}

	virtual GUIScene* CreateScene(int Width,int Height)=0;
};