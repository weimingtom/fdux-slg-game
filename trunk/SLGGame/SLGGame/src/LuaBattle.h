#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include <boost/format.hpp>

#include "SquadDefine.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "BattleSquadManager.h"
#include "AVGSquadManager.h"

#include "CutSceneBuilder.h"
#include "ChangeStateCutScene.h"
#include "StoryCutScene.h"

#include "GUIBattle.h"
#include "GUIGameOver.h"
#include "GUIMissionWindow.h"

static int ChangeState(lua_State* L)
{
	int nextstate = luaL_checkint(L, 1);
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


static int GetSquadAt(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	int visibleonly = luaL_checkint(L, 3);
	int faction = luaL_checkint(L, 4);
	BattleSquad* squad =BattleSquadManager::getSingleton().getBattleSquadAt(x, y, faction, visibleonly);
	if(squad)
	{
		lua_pushstring(L,squad->getSquadId().c_str());
	}
	else
	{
		lua_pushstring(L,"\0");
	}
	return 1;
}

static int Story(lua_State* L)
{
	std::string storyscript(luaL_checkstring(L, 1));

	CutSceneBuilder::getSingleton().addCutScene(new StoryCutScene(storyscript));
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

/*
static int CreateAIGroup(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string groupname(luaL_checkstring(L, 2));
	return 0;
}
*/

static int AssignAIGroup(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string squadid(luaL_checkstring(L, 2));
	std::string groupid(luaL_checkstring(L, 3));
	DataLibrary::getSingleton().setData(
		str(boost::format("GameData/BattleData/AIData/Team%1%/Group/%2%/SquadList/%3%")%team%groupid%squadid), 1);
	return 0;
}

static int CreateAIMission(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string missionname(luaL_checkstring(L, 2));
	int missiontype = luaL_checkint(L, 3);
	std::string areaid(luaL_checkstring(L, 4));
	DataLibrary::getSingleton().setData(
		str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%team%missionname), missiontype);
	DataLibrary::getSingleton().setData(
		str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%/AreaId")%team%missionname), areaid);
	return 0;
}

static int AssignAIMission(lua_State* L)
{
	int team = luaL_checkint(L, 1);
	std::string groupid(luaL_checkstring(L, 2));
	std::string missionname(luaL_checkstring(L, 3));
	DataLibrary::getSingleton().setData(
		str(boost::format("GameData/BattleData/AIData/Team%1%/Group/%2%/Mission")%team%groupid), missionname);
	return 0;
}

static int Win(lua_State* L)
{
	std::string next(luaL_checkstring(L, 1));
	int gold(luaL_checkint(L, 2));

	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIGameOver* GameOver=(GUIGameOver*)guibattle->getSubWindow("GameOverWindow");
	GameOver->setData(gold);
	GameOver->setNext(next);

	GameOver->showScene("win");
	return 0;
}

static int Lost(lua_State* L)
{
	std::string next(luaL_checkstring(L, 1));
	int gold(luaL_checkint(L, 2));

	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIGameOver* GameOver=(GUIGameOver*)guibattle->getSubWindow("GameOverWindow");
	GameOver->setData(gold);
	GameOver->setNext(next);

	GameOver->showScene("lost");
	return 0;
}

static int AddPlayerMission(lua_State* L)
{
	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIMissionWindow* mission=(GUIMissionWindow*)guibattle->getSubWindow("MissionWindow");

	std::string caption(luaL_checkstring(L, 1));
	std::string utf8 = StringTable::getSingleton().getString(caption);
	int state = luaL_checkint(L, 2);
	int index = mission->addMission(utf8,(MissionState)state);

	lua_pushnumber(L, index);

	return 1;
}

static int SetPlayerMission(lua_State* L)
{
	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIMissionWindow* mission=(GUIMissionWindow*)guibattle->getSubWindow("MissionWindow");
	int index=luaL_checkint(L, 1);
	int state = luaL_checkint(L, 2);
	mission->changeMission(index,(MissionState)state);
	return 0;
}

static int AddStorySquad(lua_State* L)
{
	std::string templetid(luaL_checkstring(L, 1));
	std::string squadid(luaL_checkstring(L, 2));
	int x = luaL_checkint(L, 3);
	int y = luaL_checkint(L, 4);
	int create = luaL_checkint(L, 5);
	bool re = BattleSquadManager::getSingleton().createStorySquad(squadid, templetid, x, y,create);
	re?lua_pushnumber(L, 1):lua_pushnumber(L, 0);
	return 1;
}

static int AddBattleSquad(lua_State* L)
{
	std::string templetid(luaL_checkstring(L, 1));
	std::string squadid(luaL_checkstring(L, 2));
	int x = luaL_checkint(L, 3);
	int y = luaL_checkint(L, 4);
	int team = luaL_checkint(L, 5);
	int unitnum = luaL_checkint(L, 6);
	bool re = BattleSquadManager::getSingleton().createNormalSquad(squadid, templetid, x, y, team, unitnum);
	re?lua_pushnumber(L, 1):lua_pushnumber(L, 0);
	return 1;
}

static const struct luaL_Reg BattleLib[] =
{
	{"ChangeState",ChangeState},
	{"DumpSquadData",DumpSquadData},
	{"TeamSquadLeft",TeamSquadLeft},
	{"GetSquadAt",GetSquadAt},
	{"Story",Story},
	{"AddGold",AddGold},
	//{"CreateAIGroup",CreateAIGroup},
	{"AssignAIGroup",AssignAIGroup},
	{"CreateAIMission",CreateAIMission},
	{"AssignAIMission",AssignAIMission},
	{"Win",Win},
	{"Lost",Lost},
	{"AddPlayerMission",AddPlayerMission},
	{"SetPlayerMission",SetPlayerMission},
	{"AddStorySquad", AddStorySquad},
	{"AddBattleSquad", AddBattleSquad},
	{NULL,NULL}
};