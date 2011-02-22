#pragma once

#include "GUICommon.h"
#include <MyGUI.h>

class GUIScene
{
public:
	GUIScene(std::string layoutFile):mLayoutName(layoutFile)
	{
		mWidgetList=MyGUI::LayoutManager::getInstance().loadLayout(mLayoutName);
	}

	virtual ~GUIScene(void)
	{
		MyGUI::LayoutManager::getInstance().unloadLayout(mWidgetList);
		mWidgetList.clear();
	}

	virtual void showScene()=0;//显示场景
	virtual void hideScene()=0;//隐藏场景

	virtual void FrameEvent()=0;//帧事件

	virtual GUISceneType getType()=0;

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
};
