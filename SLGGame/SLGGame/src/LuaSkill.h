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
	int re = 0, atkdie = 0, atkwond = 0, defdie = 0,defwond = 0;
	if(attacker != NULL &&  defender!= NULL)
	{
		re =  BattleSquadManager::getSingleton().meleeAttackSquad(attacker, defender, atkdie, atkwond, defdie, defwond);
	}
	else
		re = 0;
	lua_pushnumber(L,re);
	lua_pushnumber(L,atkdie);
	lua_pushnumber(L,atkwond);
	lua_pushnumber(L,defdie);
	lua_pushnumber(L,defwond);
	return 5;
}

static const struct luaL_Reg SkillLib[] =
{
	{"MeleeCombat",MeleeCombat},
	{NULL,NULL}
};