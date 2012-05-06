#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "SquadDefine.h"
#include "BattleSquadManager.h"

static int MeleeCombat(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string targetsquadid(luaL_checkstring(L, 2));
	int re = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		BattleSquad* targetsquad = BattleSquadManager::getSingleton().getBattleSquad(targetsquadid);
		if(squad &&  targetsquad)
		{
			re = BattleSquadManager::getSingleton().dealMeleeDamage(squad, targetsquad);
		}
	}
	lua_pushnumber(L, re);
	return 1;
}

static const struct luaL_Reg SkillLib[] =
{
	{"MeleeCombat",MeleeCombat},
	{NULL, NULL}
};