#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "BattleSquad.h"
#include "squaddefine.h"
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

static int RangedAttack(lua_State* L)
{
	std::string attacksquad(luaL_checkstring(L, 1));
	std::string defendsquad(luaL_checkstring(L, 2));
	BattleSquad* attacker = BattleSquadManager::getSingleton().getBattleSquad(attacksquad);
	BattleSquad* defender = BattleSquadManager::getSingleton().getBattleSquad(defendsquad);
	int re = 0;
	if(attacker != NULL &&  defender!= NULL)
	{
		re =  BattleSquadManager::getSingleton().dealRangedDamage(attacker, defender);
	}
	else
		re = 0;
	lua_pushnumber(L,re);
	return 1;
}

static int MagicAttack(lua_State* L)
{
	std::string attacksquad(luaL_checkstring(L, 1));
	std::string defendsquad(luaL_checkstring(L, 2));
	int atktime = luaL_checknumber(L, 3);
	float atk = luaL_checknumber(L, 4);
	BattleSquad* attacker = BattleSquadManager::getSingleton().getBattleSquad(attacksquad);
	BattleSquad* defender = BattleSquadManager::getSingleton().getBattleSquad(defendsquad);
	int re = 0;
	if(attacker != NULL &&  defender!= NULL)
	{
		re =  BattleSquadManager::getSingleton().dealMagicDamage(attacker, defender,atktime,atk);
	}
	else
		re = 0;
	lua_pushnumber(L,re);
	return 1;
}

static int Missile(lua_State* L)
{
	std::string attacksquad(luaL_checkstring(L, 1));
	int x = luaL_checknumber(L, 2);
	int y = luaL_checknumber(L, 3);
	int castunit = luaL_checknumber(L, 4);
	std::string casteffect(luaL_checkstring(L, 5));
	std::string castaction(luaL_checkstring(L, 6));
	std::string castsound(luaL_checkstring(L, 7));
	int missletype = luaL_checknumber(L, 8);
	std::string missileres(luaL_checkstring(L, 9));
	std::string hiteffect(luaL_checkstring(L, 10));
	std::string hitsound(luaL_checkstring(L, 11));
	BattleSquad* attacker = BattleSquadManager::getSingleton().getBattleSquad(attacksquad);
	BattleSquadManager::getSingleton().rangedAttackCutScene(attacker,x ,y,castunit,casteffect,castaction,castsound,missletype,missileres, hiteffect,hitsound);
	return 0;
}

static int ApplyEffect(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	std::string effect(luaL_checkstring(L, 2));
	std::string effectid("");
	AVGSquadManager::getSingleton().applyEffect(squadpath,effect,effectid);
	lua_pushstring(L,effectid.c_str());
	return 1;
}

static int RemoveEffect(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	AVGSquadManager::getSingleton().removeEffect(squadpath,id);
	return 0;
}

static int ApplyParticle(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	UnitType unittype = luaL_checknumber(L,2);
	std::string particleid(luaL_checkstring(L, 3));
	std::string effectid("");
	lua_pushstring(L,effectid.c_str());
	return 0;
}

static int RemoveParticle(lua_State* L)
{
	return 0;
}

static int ApplyModifier(lua_State* L)
{
	return 0;
}

static int RemoveModifier(lua_State* L)
{
	return 0;
}


static const struct luaL_Reg SkillLib[] =
{
	{"MeleeCombat",MeleeCombat},
	{"RangedAttack",RangedAttack},
	{"MagicAttack",MagicAttack},
	{"Missile",Missile},
	{"ApplyEffect",ApplyEffect},
	{"RemoveEffect",RemoveEffect},
	{"ApplyParticle",ApplyParticle},
	{"RemoveParticle",RemoveParticle},
	{"ApplyModifier",ApplyModifier},
	{"RemoveModifier",RemoveModifier},
	{NULL,NULL}
};