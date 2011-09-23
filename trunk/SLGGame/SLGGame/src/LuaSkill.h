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
	std::string castparticle(luaL_checkstring(L, 5));
	std::string castaction(luaL_checkstring(L, 6));
	std::string castsound(luaL_checkstring(L, 7));
	int missletype = luaL_checknumber(L, 8);
	std::string missileres(luaL_checkstring(L, 9));
	std::string hitparticle(luaL_checkstring(L, 10));
	std::string hitsound(luaL_checkstring(L, 11));
	BattleSquad* attacker = BattleSquadManager::getSingleton().getBattleSquad(attacksquad);
	BattleSquadManager::getSingleton().rangedAttackCutScene(attacker,x ,y,castunit,castparticle,castaction,castsound,missletype,missileres, hitparticle,hitsound);
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

#include "SquadStateCutScene.h"
static int ApplyParticle(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	UnitType unittype = luaL_checknumber(L,2);
	std::string particleid(luaL_checkstring(L, 3));
	std::string id("");
	AVGSquadManager::getSingleton().applyParticle(squadpath,unittype,particleid,id);
	std::string::size_type i = squadpath.rfind('/');
	std::string squad = squadpath.substr(i + 1,squadpath.size() - i -1);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad)
	{
		BattleSquadManager::getSingleton().setCutScene(new SquadStateCutScene(battlesquad,SQUAD_STATE_PARTICLE,id,4));
	}
	lua_pushstring(L,id.c_str());
	return 1;
}

#include "SquadGrapManager.h"
#include "SquadGraphics.h"
static int RemoveParticle(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	AVGSquadManager::getSingleton().removeParticle(squadpath,id);
	std::string::size_type i = squadpath.rfind('/');
	std::string squad = squadpath.substr(i + 1,squadpath.size() - i -1);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad)
	{
		SquadGraphics* squadgrap = SquadGrapManager::getSingleton().getSquad(battlesquad->getGrapId());
		if(squadgrap)
			squadgrap->delParticle(id);
	}
	return 0;
}

static int ApplyModifier(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	AttrModifier* modifier = new AttrModifier;
	modifier->Type = luaL_checknumber(L,2);
	modifier->Attack = luaL_checknumber(L,3);
	modifier->RangedAttack = luaL_checknumber(L,4);
	modifier->Defence = luaL_checknumber(L,5);
	modifier->Form = luaL_checknumber(L,6);
	modifier->Initiative = luaL_checknumber(L,7);
	modifier->ActionPoint = luaL_checknumber(L,8);
	modifier->Detection = luaL_checknumber(L,9);
	modifier->Covert = luaL_checknumber(L,10);
	modifier->Injury = luaL_checknumber(L,11);
	modifier->Conter = luaL_checknumber(L,12);
	std::string id("");
	AVGSquadManager::getSingleton().applyModifer(squadpath,modifier,id);
	delete modifier;
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveModifier(lua_State* L)
{
	std::string squadpath(luaL_checkstring(L, 1));
	std::string id(luaL_checkstring(L, 2));
	AVGSquadManager::getSingleton().removeModifier(squadpath,id);
	return 0;
}

#include "AnimationCutScene.h"
static int Action(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int castunit = luaL_checknumber(L, 2);
	std::string particle(luaL_checkstring(L, 3));
	std::string action(luaL_checkstring(L, 4));
	std::string sound(luaL_checkstring(L, 5));
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	AnimationCutScene* acs = new AnimationCutScene(battlesquad->getGrapId(),castunit,action,sound,particle,false,true);
	BattleSquadManager::getSingleton().setCutScene(acs);
	return 0;
}

static int GetSquadApLeft(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	float ap = 0.0f;
	if(battlesquad)
	{
		ap = battlesquad->getActionPoint();
	}
	lua_pushnumber(L,ap);
	return 1;
}

static int SetSquadApLeft(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	float ap = luaL_checknumber(L,2);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad)
	{
		DataLibrary::getSingleton().setData(battlesquad->getPath() + "/ActionPoint",ap);
	}
	return 0;
}

/*
static int GetWoundNum(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	int wn = 0;
	if(battlesquad)
	{
		DataLibrary::getSingleton().getData(battlesquad->getPath() + "/WoundNum",wn);
	}
	lua_pushnumber(L,wn);
	return 1;
}


static int SetWoundNum(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int wn = luaL_checknumber(L,2);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad)
	{
		DataLibrary::getSingleton().setData(battlesquad->getPath() + "/WoundNum",wn);
	}
	return 0;
}
*/
static int GetUnitNum(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	int un = 0;
	if(battlesquad)
	{
		un = battlesquad->getUnitRealNum();
	}
	lua_pushnumber(L,un);
	return 1;
}

static int GetUnitMaxNum(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	int un = 0;
	if(battlesquad)
	{
		DataLibrary::getSingleton().getData(battlesquad->getPath() + "/UnitMaxNumber",un);
	}
	lua_pushnumber(L,un);
	return 1;
}

#include "SquadDeadCutScene.h"
#include "SquadRecoverCutScene.h"
static int SetUnitNum(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int num = luaL_checknumber(L,2);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	int unb = 0, una = 0;
	if(battlesquad)
	{
		unb = battlesquad->getUnitGrapNum();
		DataLibrary::getSingleton().setData(battlesquad->getPath() + std::string("/UnitNumber"),num);
		una = battlesquad->getUnitGrapNum();
		if(una < unb)
		{
			BattleSquadManager::getSingleton().setCutScene(new SquadDeadCutScene(battlesquad->getGrapId(), unb - una));
		}
		else if(una > unb)
		{
			BattleSquadManager::getSingleton().setCutScene(new SquadRecoverCutScene(battlesquad->getGrapId(), una - unb));
		}
	}
	return 0;
}

#include "FormationCutScence.h"
static int ChangeFormation(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int f = luaL_checknumber(L,2);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(battlesquad)
	{
		battlesquad->setFormation(f);
		BattleSquadManager::getSingleton().setCutScene(new FormationCutScene(battlesquad->getGrapId(),f));
	}
	return 0;
}

#include "EffectCutScene.h"
static int SquadParticle(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int castunit = luaL_checknumber(L, 2);
	std::string particle(luaL_checkstring(L, 3));
	std::string sound(luaL_checkstring(L, 4));
	int time  = luaL_checknumber(L, 5);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	EffectCutScene* ecs = new EffectCutScene(battlesquad->getGrapId(),castunit,particle,sound,time);
	BattleSquadManager::getSingleton().setCutScene(ecs);
	return 0;
}

static int SetMorale(lua_State* L)
{
	std::string squad(luaL_checkstring(L, 1));
	int morale = luaL_checknumber(L, 2);
	int	spread = luaL_checknumber(L, 3);
	BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquad(squad);
	if(spread == 1)
		battlesquad->modifyMorale(morale);
	else
		BattleSquadManager::getSingleton().spreadModifyMorale(battlesquad,morale);
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
	{"Action",Action},
	{"GetSquadApLeft",GetSquadApLeft},
	{"SetSquadApLeft",SetSquadApLeft},
// 	{"GetWoundNum",	GetWoundNum},
// 	{"SetWoundNum",	SetWoundNum},
	{"GetUnitNum",GetUnitNum},
	{"SetUnitNum",SetUnitNum},
	{"GetUnitMaxNum",GetUnitMaxNum},
	{"ChangeFormation",ChangeFormation},
	{"SquadParticle",SquadParticle},
	{"SetMorale",SetMorale},
	{NULL,NULL}
};