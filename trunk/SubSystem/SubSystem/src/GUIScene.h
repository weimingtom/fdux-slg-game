#pragma once

#include "GUICommon.h"
#include "GUISystem.h"
#include <MyGUI.h>

class GUIScene
{
public:
	GUIScene(std::string layoutFile,int Width,int Height);

	GUIScene(MyGUI::Widget* containerWidget,int Width,int Height);

	virtual ~GUIScene(void);

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

	void FadeIn(float time,MyGUI::Widget* fadeWidget);//渐变,以毫秒计算

	void EventFadeInPostAction(MyGUI::Widget* _sender);

	void StopFadeIn(MyGUI::Widget* fadeWidget);

	void FadeOut(float time,MyGUI::Widget* fadeWidget);

	void EventFadeOutPostAction(MyGUI::Widget* _sender);

	void StopFadeOut(MyGUI::Widget* fadeWidget);

	MyGUI::VectorWidgetPtr mWidgetList;
	MyGUI::Widget* mContainerWidget;
	std::string mLayoutName;

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