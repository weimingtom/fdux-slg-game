#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include "SquadDefine.h"
#include "DataLibrary.h"
#include "BattleSquadManager.h"

#include "CutSceneBuilder.h"
#include "ChangeStateCutScene.h"

static int ChangeState(lua_State* L)
{
	enumtype nextstate = luaL_checkint(L, 1);
	std::string arg(luaL_checkstring(L, 2));
	CutSceneBuilder::getSingleton().addCutScene(new ChangeStateCutScene(nextstate, arg));
	return 0;
}

static int DumpSquadData(lua_State* L)
{
	BattleSquadManager::getSingleton().dumpSquadData();
	return 0;
}

static int TeamSquadLeft(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	int num = BattleSquadManager::getSingleton().getTeamSquadLeft(team);
	lua_pushinteger(L, num);
	return 1;
}

static int Story(lua_State* L)
{
	std::string storyscript(luaL_checkstring(L, 1));
	return 0;
}

static int AddGold(lua_State* L)
{
	int gold = luaL_checkint(L, 1);
	int curgold = 0;
	DataLibrary::getSingleton().getData("GameData/StoryData/Gold", curgold);
	curgold += gold;
	DataLibrary::getSingleton().setData("GameData/StoryData/Gold", curgold);
	return 0;
}

static int CreateAIGroup(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string groupname(luaL_checkstring(L, 2));
	return 0;
}

static int AssignAIGroup(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string squadid(luaL_checkstring(L, 2));
	std::string groupid(luaL_checkstring(L, 3));
	return 0;
}

static int CreateAIMission(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string missionname(luaL_checkstring(L, 2));
	int missiontype = luaL_checkint(L, 3);
	switch(missiontype)
	{
	case 1:
		{
			std::string groupid(luaL_checkstring(L, 4));
		}
		break;
	}
	return 0;
}

static int AssignAIMission(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string groupid(luaL_checkstring(L, 2));
	std::string missionname(luaL_checkstring(L, 3));
	return 0;
}

static const struct luaL_Reg BattleLib[] =
{
	{"ChangeState",ChangeState},
	{"DumpSquadData",DumpSquadData},
	{"TeamSquadLeft",TeamSquadLeft},
	{"Story",Story},
	{"AddGold",AddGold},
	{"CreateAIGroup",CreateAIGroup},
	{"AssignAIGroup",AssignAIGroup},
	{"CreateAIMission",CreateAIMission},
	{"AssignAIMission",AssignAIMission},
	{NULL,NULL}
};