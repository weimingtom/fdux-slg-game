#include "LuaEngine.h"
#include "ScriptContext.h"
#include "conversion.h"

LuaEngine::LuaEngine()
{
	mL = luaL_newstate();
	luaL_openlibs(mL);
	RegLib("CommonLib",gCommonLib);
}

LuaEngine::~LuaEngine()
{
	lua_close(mL);
}

bool LuaEngine::ExecuteFile(std::wstring filename, ScriptContext *context)
{
	if(context == NULL)
		return false;
	mContext = context;
	std::string tempfilename;
	UnicodeToANSI(filename, tempfilename);
	int result;
	result = luaL_loadfile(mL, tempfilename.c_str());
	if(!result)
		result = lua_pcall(mL,0 ,0, 0);
	mContext = NULL;
	return !result;
}

bool LuaEngine::ExecuteFunction(std::wstring filename, std::wstring funcname, ScriptContext *context)
{
	if(context == NULL)
		return false;
	mContext = context;
	std::string tempfilename;
	UnicodeToANSI(filename, tempfilename);
	int result;
	result = luaL_loadfile(mL, tempfilename.c_str());
	if(!result)
	{
		result = lua_pcall(mL,0 ,0, 0);
		if(!result)
		{
			std::string tempfuncname;
			UnicodeToANSI(funcname, tempfuncname);
			lua_getglobal(mL, tempfuncname.c_str());
			result = lua_pcall(mL,0 ,0, 0);
		}
	}
	mContext = NULL;
	return !result;
}

bool LuaEngine::RegLib(std::string libName, const luaL_Reg *lib)
{
	luaL_register(mL,libName.c_str(),lib);
	return true;
}

//¹²ÓĞº¯Êı¿â------------------------------------------------------
int SetInt(lua_State *L)
{
	if(LuaEngine::getSingleton().mContext!=NULL)
	{
		int i = luaL_checknumber(L,1);
		int n = luaL_checknumber(L,2);
		LuaEngine::getSingleton().mContext->SetInt(i,n);
	}
	return 0;
}
int GetInt(lua_State *L)
{
	int n = 0;
	if(LuaEngine::getSingleton().mContext!=NULL)
	{
		int i = luaL_checknumber(L,1);
		LuaEngine::getSingleton().mContext->GetInt(i,n);
	}
	lua_pushinteger(L,n);
	return 1;
}