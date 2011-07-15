#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "LuaSystem.h"
#include "DataLibrary.h"
#include "AudioSystem.h"

static int SetInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	int val = luaL_checknumber(L, 2);
	std::string contextpath = LuaSystem::getSingleton().getContext();
	DataLibrary::getSingleton().setData(contextpath + std::string("/")+ id, val);
	return 0;
}

static int GetInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	int val;
	DataLibrary::getSingleton().getData(contextpath + std::string("/")+ id, val);
	lua_pushnumber(L,val);
	return 1;
}

static int GetString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	std::string val;
	DataLibrary::getSingleton().getData(contextpath + std::string("/")+ id, val);
	lua_pushstring(L,val.c_str());
	return 1;
}

static int SetString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string val(luaL_checkstring(L, 2));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	DataLibrary::getSingleton().setData(contextpath + std::string("/")+ id, val);
	return 0;
}

static int GetSquadCoord(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int x = -1,y = -1;
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad!=NULL)
	{
		battlesquad->getCrood(&x,&y);
	}
	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	return 2;
}

static int PlayMusic(lua_State* L)
{
	std::string music(luaL_checkstring(L, 1));
	DataLibrary::getSingleton().setData("GameData/BattleData/BackGroundMusic/", music);
	AudioSystem::getSingleton().playStream(music,true,5);
	return 0;
}

static const struct luaL_Reg ScriptCommonLib[] =
{
	{"SetInt",SetInt},
	{"GetInt",GetInt},
	{"GetString",GetString},
	{"SetString",SetString},
	{"GetSquadCoord",GetSquadCoord},
	{"PlayMusic",PlayMusic},
	{NULL,NULL}
};