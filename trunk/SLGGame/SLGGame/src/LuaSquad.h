#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include "SquadDefine.h"
#include "StateManager.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "SquadGrapManager.h"

#include "CutSceneBuilder.h"
#include "SquadParticleCutScence.h"

static int GetSquadCoord(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int x = -1,y = -1;
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	if(battlesquad!=NULL)
	{
		x = battlesquad->getGridX();
		y = battlesquad->getGridY();
	}
	lua_pushnumber(L,x);
	lua_pushnumber(L,y);
	return 2;
}

static int AddSquadTrigger(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string trigertype(luaL_checkstring(L, 2));
	std::string trigerfunc(luaL_checkstring(L, 3));
	std::string filename = LuaSystem::getSingleton().getFileName();
	std::string context = LuaSystem::getSingleton().getContext();
	std::string id;
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		id = squad->addTrigger(trigertype, filename, trigerfunc, context);
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveSquadTrigger(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->removeTrigger(id);
	return 0;
}

static int ActiveSquadTrigger(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->activeTrigger(id);
	return 0;
}

static int DisableSquadTrigger(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->disableTrigger(id);
	return 0;
}

static int ApplyEffect(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string effect(luaL_checkstring(L, 2));
	std::string id;
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->applyEffect(effect, id);
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveEffect(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->removeEffect(id);
	return 0;
}

static int GetEffectLevel(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	int lv = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		lv = squad->getEffectLevel(id);
	lua_pushnumber(L,lv);
	return 1;
}

static int ApplyModifier(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	AttrModifier* modifier = new AttrModifier;
	modifier->Type = luaL_checkinteger(L,2);
	modifier->Attack = luaL_checknumber(L,3);
	modifier->RangedAttack = luaL_checknumber(L,4);
	modifier->Defence = luaL_checknumber(L,5);
	modifier->Form = luaL_checknumber(L,6);
	modifier->Initiative = luaL_checknumber(L,7);
	modifier->ActionPoint = luaL_checknumber(L,8);
	modifier->Detection = luaL_checknumber(L,9);
	modifier->Covert = luaL_checknumber(L,10);
	modifier->Toughness = luaL_checknumber(L,11);
	modifier->Conter = luaL_checknumber(L,12);
	std::string id;

	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->applyModifer(modifier, id);
	delete modifier;
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveModifier(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->removeModifier(id);
	return 0;
}

static int GetActionPoint(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	BattleSquad* squad = NULL;
	float ap = 0.0f;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
			ap = squad->getActionPoint();
	}
	lua_pushnumber(L, ap);
	return 1;
}

static int GetFaction(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int faction = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
			faction = squad->getFaction();
	}
	lua_pushnumber(L, faction);
	return 1;
}

static int GetUnitMaxNum(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	BattleSquad* squad = NULL;
	int maxnum = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		maxnum = squad->getUnitMaxNum();
	lua_pushnumber(L, maxnum);
	return 1;
}

static int GetUnitNum(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	Squad* squad = NULL;
	int num = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL; 
	if(squad)
		num = squad->getUnitNum();
	lua_pushnumber(L, num);
	return 1;
}

static int SetUnitNum(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int num = luaL_checkinteger(L, 2);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		BattleSquadManager::getSingleton().setUnitNum(squad, num);
	}
	else
	{
	}
	return 0;
}

static int ChangeFormation(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int formation = luaL_checkinteger(L, 2);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		BattleSquadManager::getSingleton().changeFormation(squad, formation, false);
	}
	else
	{
	}
	return 0;
}

static int AddParticle(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string particlename(luaL_checkstring(L, 2));
	int objecttype = luaL_checkinteger(L, 3);
	std::string particleid;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		squad->addParticle(particlename, objecttype, particleid);
		CutSceneBuilder::getSingleton().addCutScene(new SquadParticleCutScence(squadid, particleid, particlename, objecttype));
	}
	lua_pushstring(L, particleid.c_str());
	return 1;
}

static int DelParticle(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string particleid(luaL_checkstring(L, 2));
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		squad->removeParticle(particleid);
		CutSceneBuilder::getSingleton().addCutScene(new SquadParticleCutScence(squadid, particleid));
	}
	return 0;
}

static int GetEquip(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int equiptype = luaL_checkinteger(L, 2);
	std::string equip("none");
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	}
	else
	{

	}
	if(squad)
	{
		equip = squad->getEquipment(equiptype);
	}
	lua_pushstring(L, equip.c_str());
	return 1;
}

static int AddExp(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int exp = luaL_checkinteger(L, 2);
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	}
	else
	{

	}
	if(squad)
	{
		squad->addExp(exp);
	}
	return 1;
}

static const struct luaL_Reg SquadLib[] =
{
	{"GetSquadCoord",GetSquadCoord},
	{"AddSquadTrigger",AddSquadTrigger},
	{"RemoveSquadTrigger",RemoveSquadTrigger},
	{"ActiveSquadTrigger",ActiveSquadTrigger},
	{"DisableSquadTrigger",DisableSquadTrigger},
	{"ApplyEffect",ApplyEffect},
	{"RemoveEffect",RemoveEffect},
	{"GetEffectLevel",GetEffectLevel},
	{"ApplyModifier",ApplyModifier},
	{"RemoveModifier",RemoveModifier},
	{"GetActionPoint",GetActionPoint},
	{"GetFaction",GetFaction},
	{"GetUnitMaxNum",GetUnitMaxNum},
	{"GetUnitNum",GetUnitNum},
	{"SetUnitNum",SetUnitNum},
	{"ChangeFormation",ChangeFormation},
	{"AddParticle",AddParticle},
	{"DelParticle",DelParticle},
	{"GetEquip",GetEquip},
	{"AddExp",AddExp},
	{NULL,NULL}
};