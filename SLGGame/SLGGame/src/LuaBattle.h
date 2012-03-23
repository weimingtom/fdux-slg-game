#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include "SquadDefine.h"

static int ChangeState(lua_State* L)
{
	enumtype nextstate = luaL_checkint(L, 1);
	std::string arg(luaL_checkstring(L, 2));
	return 0;
}

static int DumpSquadData(lua_State* L)
{
	return 0;
}

static int TeamSquadLeft(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	int num = 1;
	lua_pushinteger(L, num);
	return 1;
}

static int Story(lua_State* L)
{
	std::string storyscript(luaL_checkstring(L, 1));
	return 0;
}

static const struct luaL_Reg BattleLib[] =
{
	{"ChangeState",ChangeState},
	{"DumpSquadData",DumpSquadData},
	{"TeamSquadLeft",TeamSquadLeft},
	{"Story",Story},
	{NULL,NULL}
};