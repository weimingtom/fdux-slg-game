#pragma once
#include "iisingleton.hpp"
using namespace izayoi;
#include "lua.hpp"
#include <string>

class ScriptContext;

class LuaEngine:public IISingleton<LuaEngine>
{
public:
	LuaEngine();
	~LuaEngine();

	bool ExecuteFile(std::wstring filename, ScriptContext* context);
	bool ExecuteFunction(std::wstring filename, std::wstring funcname, ScriptContext* context);

	ScriptContext *mContext;

	bool RegLib(std::string libName, const luaL_Reg *lib);
private:
	lua_State *mL;
};

int SetInt(lua_State *L);
int GetInt(lua_State *L);

static const struct luaL_Reg gCommonLib [] = {
	{"SetInt",SetInt},
	{"GetInt",GetInt},
	{NULL,NULL}
};