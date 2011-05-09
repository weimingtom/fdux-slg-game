#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "LuaSystem.h"
#include "DataLibrary.h"

static int SetInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	int val = luaL_checknumber(L, 2);
	std::string contextpath = LuaSystem::getSingleton().GetContext();
	DataLibrary::getSingleton().setData(contextpath + std::string("/")+ id, val);
	return 0;
}

static int GetString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string contextpath = LuaSystem::getSingleton().GetContext();
	std::string val;
	DataLibrary::getSingleton().getData(contextpath + std::string("/")+ id, val);
	lua_pushstring(L,val.c_str());
	return 1;
}

static const struct luaL_Reg ScriptCommonLib[] =
{
	{"SetInt",SetInt},
	{"GetString",GetString},
	{NULL,NULL}
};