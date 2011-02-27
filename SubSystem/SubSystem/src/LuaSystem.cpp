#include "LuaSystem.h"

#include <Ogre.h>

#include "LuaFun.cpp"

extern "C"
{

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

}

LuaSystem::LuaSystem(void)
{
	L=lua_open();
	luaL_openlibs(L);
	LuaBreakupFun=NULL;
	mListener=NULL;
	luaL_register(L, "GUI",GUILib);
}

LuaSystem::~LuaSystem(void)
{
	lua_close(L);
}

std::string LuaSystem::luaCallString(const std::string Szcode)
{
	luaL_loadstring(L,Szcode.c_str());
	int error=lua_pcall(L, 0 , 0, 0);
	if (error)
	{
		const char* error = lua_tostring(L, -1);//打印错误结果
		lua_pop(L, 1);
		return std::string(error);
	}
	return std::string();
}


void LuaSystem::runScript( const std::string script )
{
	mScriptBuffer.clear();

	std::stringstream ss(script);
	std::string sub_str;

	while(std::getline(ss,sub_str,';'))//以分号切分语句
	{
		mScriptBuffer.push_back(sub_str);
	}
}

void LuaSystem::onFrameUpdate()
{
	if (!mScriptBuffer.empty())
	{

		if (LuaBreakupFun==NULL)
		{
			std::string lua=(*mScriptBuffer.begin());
			mScriptBuffer.erase(mScriptBuffer.begin());
			
			std::string ret=luaCallString(lua);
			if (ret!="")//如果发生错误
			{
				if (mListener!=NULL)
				{
					mScriptBuffer.clear();
					LuaBreakupFun=NULL;
					mListener->onError(ret);
				}

				return;
			}

			if (mScriptBuffer.empty())//如果是最后一条语句
			{
				if (mListener!=NULL)
				{
					LuaBreakupFun=NULL;
					mListener->onComplete();
				}
			}
		}
		else//当被阻塞时
		{
			LuaBreakupFun();
		}
	}
}

void LuaSystem::registerListener( LuaSystemListener* listener )
{
	mListener=listener;
}

void LuaSystem::registerCLib( const std::string libName,const luaL_Reg* lib )
{
	luaL_register(L, libName.c_str(),lib);
}


