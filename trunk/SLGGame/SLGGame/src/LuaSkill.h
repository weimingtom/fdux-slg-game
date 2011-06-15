#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "BattleSquad.h"
#include "BattleSquadManager.h"

static int MeleeCombat(lua_State* L)
{
	std::string attacksquad(luaL_checkstring(L, 1));
	std::string defendsquad(luaL_checkstring(L, 2));
	BattleSquad* attacker = BattleSquadManager::getSingleton().getBattleSquad(attacksquad);
	BattleSquad* defender = BattleSquadManager::getSingleton().getBattleSquad(defendsquad);
	int re = 0;
	if(attacker != NULL &&  defender!= NULL)
	{
		re =  BattleSquadManager::getSingleton().meleeAttackSquad(attacker, defender);
	}
	else
		re = 0;
	lua_pushnumber(L,re);
	return 1;
}

static const struct luaL_Reg SkillLib[] =
{
	{"MeleeCombat",MeleeCombat},
	{NULL,NULL}
};