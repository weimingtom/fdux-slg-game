#pragma once

#include "GUISystem.h"
#include "GUIStage.h"
#include "LuaSystem.h"
#include "AudioSystem.h"
#ifndef SCRIPT_EDITOR
#include "StateManager.h"
#endif

#define DefaultShowTextTime 0.1//默认打字效果速度
#define DefaultCursorTime 0.01//默认光标闪烁频率

#include <Windows.h>

#include "UtilsOgreDshow.h"

extern "C"
{

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

	static GUIDialogAttribute mAttribute;//文本显示数据
	static GUIImageAttribute mImageAttribute;//每层位置存放处
	static bool mPrinter=true;//是否打开打字效果
	static bool mIsShowTextOver=false;//是否已经结束显示,等待按下鼠标?
	
	static int SetTextBgRect(lua_State* L)//设定文本背景位置
	{
		mAttribute.TextBgLeft=luaL_checkint(L, 1);
		mAttribute.TextBgTop=luaL_checkint(L,2);
		mAttribute.TextBgWidth=luaL_checkint(L,3);
		mAttribute.TextBgHeight=luaL_checkint(L,4);

		return 1;
	}

	static int SetTextBgImage(lua_State* L)//设定文本背景
	{
		mAttribute.TextBgImage=std::string(luaL_checkstring(L,1));

		return 1;
	}

	static int SetTextRect(lua_State* L)//设定文字位置
	{
		mAttribute.TextLeft=luaL_checkint(L, 1);
		mAttribute.TextTop=luaL_checkint(L,2);
		mAttribute.TextWidth=luaL_checkint(L,3);
		mAttribute.TextHeight=luaL_checkint(L,4);

		return 1;
	}

	static int SetRoleNameRect(lua_State* L)//设定角色名称位置
	{
		mAttribute.RoleNameLeft=luaL_checkint(L, 1);
		mAttribute.RoleNameTop=luaL_checkint(L,2);
		mAttribute.RoleNameWidth=luaL_checkint(L,3);
		mAttribute.RoleNameHeight=luaL_checkint(L,4);

		return 1;
	}

	static int SetUITextColor(lua_State* L)//设置文本颜色
	{
		mAttribute.TextRed=luaL_checknumber(L, 1);
		mAttribute.TextGreen=luaL_checknumber(L,2);
		mAttribute.TextBlue=luaL_checknumber(L,3);

		return 1;
	}

	static int SetRoleNameColor(lua_State* L)//设置角色名称颜色
	{
		mAttribute.RoleNameRed=luaL_checknumber(L, 1);
		mAttribute.RoleNameGreen=luaL_checknumber(L,2);
		mAttribute.RoleNameBlue=luaL_checknumber(L,3);

		return 1;
	}

	static int SetFont(lua_State* L)//设置字体
	{
		mAttribute.TextFont=std::string(luaL_checkstring(L,1));
		mAttribute.RoleFont=std::string(luaL_checkstring(L,2));

		return 1;
	}

	static int SetDialogAttribute(lua_State* L)//提交改变
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage!=NULL)
			stage->setTextDialog(mAttribute);

		return 1;
	}

	static void ShowTextBreakup()//文本直接模式回调
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return ;

		if(stage->CheckMouseState())
		{

			if (stage->mTimerWork==GUIStage::PrinterWork)//还没显示完就按鼠标?
			{
				stage->showOtherText();
				LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
			}
			else if (stage->mTimerWork==GUIStage::NoneWork)
			{
				LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
			}
		}
		else if(stage->mTimerWork==GUIStage::NoneWork)//显示完了
		{
			LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
		}
	}

	static void ShowWaitTextBreakup()//文本等待模式回调
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return ;

		if(stage->CheckMouseState())
		{

			if (stage->mTimerWork==GUIStage::PrinterWork)//还没显示完就按鼠标?
			{
				stage->showOtherText();
				stage->setCheckMouseDown();
			}
			else
			{
				stage->hideTextCursor();
				LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
			}
		}
		else if(stage->mTimerWork==GUIStage::NoneWork && mIsShowTextOver)//显示完了,等待按鼠标
		{
			stage->showTextCursor(true);
			mIsShowTextOver=false;
		}
	}

	static void ShowImageBreakup()//图片回调
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return ;
		if (stage->mTimerWork==GUIStage::NoneWork)
		{
			LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
		}
	}
	
	static void ClearTextBreakup()
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return ;
		if (stage->CheckMouseState() || stage->mIsFastForward)
		{
			stage->hideTextCursor();
			stage->clearText();
			LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
		}
	}

	static int SetDialogVisible(lua_State* L)//设置对话框的显隐,1表示显,0表示隐
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		if (luaL_checkint(L, 1)==1)
		{
			stage->setTextDialogVisible(true);
		}
		else
		{
			stage->setTextDialogVisible(false);
		}

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;//借用图片显隐的回调

		return 1;
	}

	static int ShowImageSetting(lua_State* L)//图片设置位置
	{
		mImageAttribute.LeftLayerX=luaL_checkint(L, 1);
		mImageAttribute.LeftLayerY=luaL_checkint(L, 2);
		mImageAttribute.MidLayerX=luaL_checkint(L, 3);
		mImageAttribute.MidLayerY=luaL_checkint(L, 4);
		mImageAttribute.RightLayerX=luaL_checkint(L, 5);
		mImageAttribute.RightLayerY=luaL_checkint(L, 6);
		mImageAttribute.FadeTime=luaL_checkint(L, 7);

		return 1;
	}

	static int ShowImage (lua_State* L)//显示图片
	{

		const char* imageName = luaL_checkstring(L, 1);
		int imageLayer =luaL_checkint(L, 2);
		float time =(float)luaL_checkint(L, 3);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;

		unsigned int left=0;
		unsigned int top=0;

		switch((GUIImageLayer)imageLayer)
		{
		case LeftLayer:
			{
				left=mImageAttribute.LeftLayerX;
				top=mImageAttribute.LeftLayerY;
				break;
			}
		case MidLayer:
			{
				left=mImageAttribute.MidLayerX;
				top=mImageAttribute.MidLayerY;
				break;
			}
		case RightLayer:
			{
				left=mImageAttribute.RightLayerX;
				top=mImageAttribute.RightLayerY;
				break;
			}
		}

		stage->showImage(imageName,(GUIImageLayer)imageLayer,time,left,top);

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;

		return 1;
	}

	static int ShockImage (lua_State* L)//震动图片
	{
		int imageLayer =luaL_checkint(L,1);
		int durationTime =luaL_checkint(L, 2);
		float amplitudeX =(float)luaL_checknumber(L, 3);
		float amplitudeY =(float)luaL_checknumber(L, 4);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;

		stage->shockImage((GUIImageLayer)imageLayer,durationTime/1000.0,amplitudeX,amplitudeY);

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;

		return 1;
	}

	static int MoveImage (lua_State* L)//移动图片
	{
		int imageLayer =luaL_checkint(L, 1);
		float time =(float)luaL_checkint(L, 2);
		int left =luaL_checkint(L, 3);
		int top =luaL_checkint(L, 4);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;

		stage->moveImage((GUIImageLayer)imageLayer,time,left,top);

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;

		return 1;
	}

	static int ShowRole(lua_State* L)//显示图片
	{
		const char* imageName = luaL_checkstring(L, 1);
		int imageLayer =luaL_checkint(L, 2);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;

		unsigned int left=0;
		unsigned int top=0;

		switch((GUIImageLayer)imageLayer)
		{
		case LeftLayer:
			{
				left=mImageAttribute.LeftLayerX;
				top=mImageAttribute.LeftLayerY;
				break;
			}
		case MidLayer:
			{
				left=mImageAttribute.MidLayerX;
				top=mImageAttribute.MidLayerY;
				break;
			}
		case RightLayer:
			{
				left=mImageAttribute.RightLayerX;
				top=mImageAttribute.RightLayerY;
				break;
			}
		}

		stage->showImage(imageName,(GUIImageLayer)imageLayer,mImageAttribute.FadeTime,left,top);

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;

		return 1;
	}

	static int ShowText (lua_State* L)//显示文本
	{
		const char* text = luaL_checkstring(L, 1);
		int mode=luaL_checkint(L,2);
		
		//单字节转双字节
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, text, -1, NULL, 0);
		wchar_t *pwText;
		pwText = new wchar_t[dwNum];

		MultiByteToWideChar (CP_ACP, 0, text, -1, pwText, dwNum);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		if (mPrinter)
		{
			stage->showText(std::wstring(pwText),DefaultShowTextTime);
		}
		else
		{
			stage->showText(std::wstring(pwText),0);
		}

		delete []pwText;
	
		//mode=1 普通模式,等待打字效果结束后继续执行
		//mode=2 等待模式,等待用户点击鼠标
		
		if(!stage->mIsFastForward)//如果不是快进模式
		{
			stage->setCheckMouseDown();

			if(mode==1)
			{
				LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowTextBreakup;
			}
			else if (mode==2)
			{
				mIsShowTextOver=true;//等待时显示光标
				LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowWaitTextBreakup;
			}

		}
		else
		{
			LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;
		}

		return 1;
	}

	static int ClearText(lua_State* L)//清空文本
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->showTextCursor(false);
		stage->setCheckMouseDown();
		LuaSystem::getSingletonPtr()->LuaBreakupFun=ClearTextBreakup;
		return 1;
	}
	
	static int Wait(lua_State* L)//等待时间
	{
		float time=(float)luaL_checkint(L, 1);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->waitTime(time);
		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;
		return 1;
	}

	static int ShowRoleName(lua_State* L)//设置角色名称
	{

		const char* text = luaL_checkstring(L, 1);

		//单字节转双字节
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, text, -1, NULL, 0);
		wchar_t *pwText;
		pwText = new wchar_t[dwNum];

		MultiByteToWideChar (CP_ACP, 0, text, -1, pwText, dwNum);

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->showRoleName(std::wstring(pwText));

		delete []pwText;

		LuaSystem::getSingletonPtr()->LuaBreakupFun=ShowImageBreakup;

		return 1;
	}

	static int SetText(lua_State* L)//设置文本参数,这个是对前面几个进行一个封装
	{
		mAttribute.TextFont = std::string(luaL_checkstring(L, 1));
		mAttribute.TextLeft=luaL_checkint(L, 2);
		mAttribute.TextTop=luaL_checkint(L,3);
		mAttribute.TextWidth=luaL_checkint(L,4);
		mAttribute.TextHeight=luaL_checkint(L,5);
		bool type=lua_toboolean(L,6);
		if (type)
		{
			mPrinter=true;
		}
		else
		{
			mPrinter=false;
		}

		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->setTextDialog(mAttribute);

		return 1;
	}

	static int Music(lua_State* L)
	{
		std::string name = std::string(luaL_checkstring(L, 1));
		int time=luaL_checkint(L, 2);
		bool ret=AudioSystem::getSingletonPtr()->playStream(name,true,time);

		if (!ret)
		{
			luaL_error(L, "play music fail:%s,error:%s", name.c_str(),AudioSystem::getSingletonPtr()->getError(true).c_str());
		}
		return 1;
	}

	static int SE(lua_State* L)
	{
		std::string name = std::string(luaL_checkstring(L, 1));
		bool ret=AudioSystem::getSingletonPtr()->playSample(name,false);

		if (!ret)
		{
			luaL_error(L, "play se fail:%s,error:%s", name.c_str(),AudioSystem::getSingletonPtr()->getError(false).c_str());
		}
		return 1;
	}

	static int CM(lua_State* L)
	{
		int time=luaL_checkint(L, 1);
		bool ret=AudioSystem::getSingletonPtr()->stopStream(time);
	
		if (!ret)
		{
			luaL_error(L, "No Music Playing!");
		}
		return 1;
	}

	static int NextScene(lua_State* L)
	{
		std::string name = std::string(luaL_checkstring(L, 1));
		
		LuaSystem::getSingletonPtr()->runScriptFromFile(name,0);

		return 1;
	}

	static int AutoSave(lua_State* L)
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->saveData(true);

		return 1;
	}

	static int StoryOver(lua_State* L)
	{
#ifndef SCRIPT_EDITOR
		StateManager::getSingletonPtr()->removeAffixationState();
#endif
		
		return 1;
	}

	static int ButtonLock(lua_State* L)
	{
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		stage->setButtonLock(false);

		return 1;
	}

	static int SetShowSupplyButton(lua_State* L)
	{
		int v=luaL_checkint(L, 1);
		GUIStage* stage=static_cast<GUIStage*>(GUISystem::getSingletonPtr()->getScene(StageScene));
		if(stage==NULL)
			return 0;
		if(v==1)
			stage->setIsShowSupplyButton(true);
		else
			stage->setIsShowSupplyButton(false);

		return 1;
	}

	BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)
	{
		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFile(lpPath, &fd);
		BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;
		BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
		FindClose(hFind);
		return RetValue;
	}

	static void PlayMovieBreakup()
	{
		if (OgreUtils::DirectShowManager::getSingleton().isPlayOver())
		{
			OgreUtils::DirectShowManager::getSingleton().DestroyAll();
			LuaSystem::getSingletonPtr()->LuaBreakupFun=NULL;
		}
	}

	static int PlayMovie(lua_State* L)
	{
		const char* name=luaL_checkstring(L, 1);

		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, name, -1, NULL, 0);
		wchar_t *pwText;
		pwText = new wchar_t[dwNum];

		MultiByteToWideChar (CP_ACP, 0, name, -1, pwText, dwNum);

		if(FindFirstFileExists(pwText, FALSE))
		{
			OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("videotest1",name,1280,720);
		}
		else
		{
			OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("videotest1","../Media/movie/op.wmv",1280,720);
		}

		LuaSystem::getSingletonPtr()->LuaBreakupFun=PlayMovieBreakup;
		return 1;
	}

	static const struct luaL_Reg GUILib[] =
	{
		{"Music",Music},
		{"SE",SE},
		{"CM",CM},

		{"ShowImageSetting",ShowImageSetting},
		{"ShowImage",ShowImage},
		{"ShockImage",ShockImage},
		{"MoveImage",MoveImage},
		{"ShowRole",ShowRole},
		{"ShowText",ShowText},
		{"SetText",SetText},
		{"ShowRoleName",ShowRoleName},
		{"ClearText",ClearText},
		
		{"SetTextBgImage",SetTextBgImage},
		{"SetTextBgRect",SetTextBgRect},
		{"SetTextRect",SetTextRect},
		{"SetRoleNameRect",SetRoleNameRect},
		{"SetUITextColor",SetUITextColor},
		{"SetRoleNameColor",SetRoleNameColor},
		{"SetFont",SetFont},
		{"SetDialogAttribute",SetDialogAttribute},
		{"SetDialogVisible",SetDialogVisible},
		{"Wait",Wait},

		{"NextScene",NextScene},
		{"AutoSave",AutoSave},
		{"ButtonLock",ButtonLock},
		{"StoryOver",StoryOver},
		{"SetShowSupplyButton",SetShowSupplyButton},

		{"PlayMovie",PlayMovie},

		{NULL,NULL}
	};

};