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
	bool re = AVGSquadManager::getSingleton().addNewSquad(squaduid,squadid);
	lua_pushboolean(L, re);
	return 1;
}

static int SetPlayerFaction(lua_State* L)
{
	std::string factionid(luaL_checkstring(L, 1));
	DataLibrary::getSingleton().setData(std::string("GameData/StoryData/Faction"),factionid);
	return 0;
}

static int SetCanSupply(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int canSupply=luaL_checkint(L, 2);
	if(canSupply==0)
	{
		DataLibrary::getSingleton().copyNode(std::string("GameData/StoryData/SquadData/")+squadid,std::string("GameData/StoryData/NoSupplySquadData/")+squadid);
		DataLibrary::getSingleton().delNode(std::string("GameData/StoryData/SquadData/")+squadid);
	}
	else
	{
		DataLibrary::getSingleton().copyNode(std::string("GameData/StoryData/NoSupplySquadData/")+squadid,std::string("GameData/StoryData/SquadData/")+squadid);
		DataLibrary::getSingleton().delNode(std::string("GameData/StoryData/NoSupplySquadData/")+squadid);
	}
	return 0;
}
static int EE(lua_State* L)
{
	DataLibrary::getSingletonPtr()->setData("SystemConfig/AnswerToLifeTheUniverseAndEverything",42);
	DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string("..\\save\\Config.xml"));
	return 0;
}

static const struct luaL_Reg AVGLib[] =
{
	{"AddSquad",AddSquad},
	{"SetPlayerFaction",SetPlayerFaction},
	{"SetCanSupply",SetCanSupply},
	{"EE",EE},
	{NULL,NULL}
};