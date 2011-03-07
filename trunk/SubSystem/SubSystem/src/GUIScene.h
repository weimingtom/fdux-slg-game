#pragma once

#include "GUICommon.h"
#include "GUISystem.h"
#include <MyGUI.h>

class GUIScene
{
public:
	GUIScene(int Width,int Height,std::string layoutFile):mLayoutName(layoutFile),mWidth(Width),mHeight(Height)
	{
		mWidgetList=MyGUI::LayoutManager::getInstance().loadLayout(mLayoutName);
	}

	virtual ~GUIScene(void)
	{
		MyGUI::LayoutManager::getInstance().unloadLayout(mWidgetList);
		mWidgetList.clear();
	}

	virtual void showScene(std::string arg)=0;//显示场景
	virtual void hideScene()=0;//隐藏场景

	virtual void FrameEvent()=0;//帧事件

	virtual GUISceneType getType()=0;

	//当前定时器的工作
	enum TimerWork
	{
		NoneWork,
		PrinterWork,//打字机效果
		UniversalWork,//过渡效果
		FadeInOutWork,//对话框显隐
		WaitWork,//等待
		RoleNameWork,//名字渐变
		ClearAllRoleWork//清除所有的角色图片
	};
	TimerWork mTimerWork;

protected:
	template <typename T>
	void assignWidget(T * & _widget, const std::string& _name, bool _throw = true)
	{
		_widget = nullptr;
		for (MyGUI::VectorWidgetPtr::iterator iter = mWidgetList.begin(); iter != mWidgetList.end(); ++iter)
		{
			MyGUI::Widget* find = (*iter)->findWidget( _name);
			if (nullptr != find)
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
				return;

			}
		}
		MYGUI_ASSERT( ! _throw, "widget name '" << _name << "' in layout '" << mLayoutName << "' not found.");
	}
	
	MyGUI::VectorWidgetPtr mWidgetList;
	std::string mLayoutName;

	int mWidth,mHeight;

	MyGUI::Timer mTimer;//定时器
	float mTickTime;//单次触发时间
	float mSetp;//渐变步
	bool mSetpDirection;//渐变步的方向,true为正方向
	MyGUI::Widget* mFadeWidget;

	void FadeInOut()//渐变
	{
		if (mSetpDirection)//判定渐变步方向
		{
			if(mSetp+0.01f<=1.0)
			{
				mSetp+=0.01f;

				mFadeWidget->setAlpha(mSetp);
			}
			else
			{
				//停止帧更新
				mTickTime=0;
				mTimerWork=NoneWork;
				GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
			}
		}
		else
		{
			if(mSetp-0.01>=0)
			{
				mSetp-=0.01;

				mFadeWidget->setAlpha(mSetp);
			}
			else
			{

				mFadeWidget->setVisible(false);

				//停止帧更新
				mTickTime=0;
				mTimerWork=NoneWork;
				GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
			}

		}
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