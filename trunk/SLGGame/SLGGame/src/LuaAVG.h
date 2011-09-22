#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "AVGSquadManager.h"
#include "DataLibrary.h"

static int AddSquad(lua_State* L)
{
	std::string squaduid(luaL_checkstring(L, 1));
	std::string squadid(luaL_checkstring(L, 2));
	//为玩家添加一队部队
	bool re = AVGSquadManager::getSingleton().addSquad(squaduid,squadid, "GameData/StoryData/SquadData");
	lua_pushboolean(L, re);
	return 1;
}

static int SetPlayerFaction(lua_State* L)
{
	std::string factionid(luaL_checkstring(L, 1));
	DataLibrary::getSingleton().setData(std::string("GameData/StoryData/Faction"),factionid);
	return 0;
}

static int ModifyMorale(lua_State* L)
{
	std::string squaduid(luaL_checkstring(L, 1));
	int morale = luaL_checknumber(L, 2);
	AVGSquadManager::getSingleton().modifyMorale(squaduid,morale);
	return 0;
}

static const struct luaL_Reg AVGLib[] =
{
	{"AddSquad",AddSquad},
	{"SetPlayerFaction",SetPlayerFaction},
	{"ModifyMorale",ModifyMorale},
	{NULL,NULL}
};