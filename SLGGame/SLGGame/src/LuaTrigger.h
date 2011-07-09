#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "BattleSquad.h"
#include "BattleSquadManager.h"
#include "LuaSystem.h"
#include "DataLibrary.h"
#include "TriggerManager.h"

static int AddTrigger(lua_State* L)
{
	std::string trigertype(luaL_checkstring(L, 1));
	std::string trigerfunc(luaL_checkstring(L, 2));
	std::string filename = LuaSystem::getSingleton().getFileName();
	std::string context = LuaSystem::getSingleton().getContext();
	std::string id = TriggerManager::getSingleton().addTrigger(trigertype,filename,trigerfunc, context);
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	TriggerManager::getSingleton().removeTrigger(id);
	return 0;
}

static int ActiveTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	TriggerManager::getSingleton().activeTrigger(id);
	return 0;
}

static int DisableTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	TriggerManager::getSingleton().disableTrigger(id);
	return 0;
}


static const struct luaL_Reg TriggerLib[] =
{
	{"AddTrigger",AddTrigger},
	{"RemoveTrigger",RemoveTrigger},
	{"ActiveTrigger",ActiveTrigger},
	{"DisableTrigger",DisableTrigger},
	{NULL,NULL}
};