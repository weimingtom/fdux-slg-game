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
#include "StateManager.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "SquadGrapManager.h"

#include "CutSceneBuilder.h"
#include "SquadParticleCutScence.h"
#include "ShowValueCutScene.h"
#include "AnimationCutScene.h"
#include "EffectCutScene.h"

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

static int GetMaxActionPoint(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	BattleSquad* squad = NULL;
	float ap = 0.0f;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
			ap = squad->getAttr(ATTR_ACTIONPOINT, ATTRCALC_FULL);
	}
	lua_pushnumber(L, ap);
	return 1;
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

static int SetActionPoint(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	float ap = luaL_checknumber(L, 2);
	BattleSquad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
			squad->setActionPoint(ap);
	}
	return 0;
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

static int SetUnitMaxNum(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int num = luaL_checkinteger(L, 2);
	BattleSquad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->setUnitMaxNum(num);
	return 0;
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

static int GetSquadLevel(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int level = 0;
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
		level = squad->getLevel();
	}
	lua_pushnumber(L, level);
	return 1;
};

static int ShowValue(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string stringkey(luaL_checkstring(L, 2));
	float colorr = luaL_checknumber(L, 3);
	float colorg = luaL_checknumber(L, 4);
	float colorb = luaL_checknumber(L, 5);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			std::string value = StringTable::getSingleton().getString(stringkey);
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(squadid, value, Ogre::ColourValue(colorr, colorg, colorb)));
		}
	}
	return 0;
};

static int ShowValue1(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string stringkey(luaL_checkstring(L, 2));
	float num = luaL_checknumber(L,3);
	float colorr = luaL_checknumber(L, 4);
	float colorg = luaL_checknumber(L, 5);
	float colorb = luaL_checknumber(L, 6);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			std::string value = StringTable::getSingleton().getString(stringkey);
			value = str(boost::format(value)%num);
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(squadid, value, Ogre::ColourValue(colorr, colorg, colorb)));
		}
	}
	return 0;
};

static int GetSkillLevel(lua_State* L)
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
		lv = squad->getSkillLevel(id);
	lua_pushnumber(L,lv);
	return 1;
}

static int GetEffectLevelByName(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string effectname(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	std::string effectid("");
	int lv = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		lv = squad->getEffectLevelByName(effectname, effectid);	
	lua_pushnumber(L,lv);
	lua_pushstring(L, effectid.c_str());
	return 2;
}

static int GetType(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	Squad* squad = NULL;
	int squantype = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squantype = squad->getType();	
	lua_pushnumber(L,squantype);
	return 1;
}

static int GetSquadType(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	Squad* squad = NULL;
	int squantype = 0;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squantype = squad->getSquadType();	
	lua_pushnumber(L,squantype);
	return 1;
}

static int Animation(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int unittype = luaL_checkinteger(L, 2);
	std::string animationame(luaL_checkstring(L, 3));
	std::string soundname(luaL_checkstring(L, 4));
	std::string particlename(luaL_checkstring(L, 5));
	int loop = luaL_checkinteger(L, 6);
	int backtoidle = luaL_checkinteger(L, 7);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			CutSceneBuilder::getSingleton().addCutScene(
				new AnimationCutScene(squad->getSquadId(), (UnitType)unittype, 
				animationame, soundname, particlename, loop == 1,
				backtoidle == 1));
		}
	}
	return 0;
}
static int AddSkill(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string skillid(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->addSkill(skillid);	
	return 0;
}
static int RemoveSkill(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	std::string skillid(luaL_checkstring(L, 2));
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		squad->removeSkill(skillid);	
	return 0;
}

static int GetSquadAttr(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int attrtype = luaL_checkinteger(L, 2);
	int clactype = luaL_checkinteger(L, 3);
	float attr = 0.0f;
	Squad* squad = NULL;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
		squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
	else
		squad = NULL;
	if(squad)
		attr = squad->getAttr(attrtype, clactype);
	lua_pushnumber(L,attr);
	return 1;
}

static int GetEquipAttr(lua_State* L)
{
	int equiptype = luaL_checkinteger(L, 1);
	std::string equipid(luaL_checkstring(L, 2));
	int attrtype = luaL_checkinteger(L, 3);
	float value = 0.0f;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string srcpath;
	switch(equiptype)
	{
	case EQUIP_ARMOR:
		srcpath = "StaticData/ArmorData";
		break;
	case EQUIP_HORSE:
		srcpath = "StaticData/HorseData";
		break;
	case EQUIP_SOILDER:
		srcpath = "StaticData/SoilderData";
		break;
	case EQUIP_SHIELD:
		srcpath = "StaticData/ShieldData";
		break;
	case EQUIP_PWEAPON:
		srcpath = "StaticData/PweaponData";
		break;
	case EQUIP_SWEAPON:
		srcpath = "StaticData/SweaponData";
		break;
	}
	std::vector<std::string> srcequiplist = datalib->getChildList(srcpath);
	std::vector<std::string>::iterator ite = std::find(srcequiplist.begin(), srcequiplist.end(), equipid);
	if(ite != srcequiplist.end())
	{
		srcpath = srcpath + std::string("/") + equipid + std::string("/AttrModifer");
		switch(attrtype)
		{
		case ATTR_ATTACK:
			datalib->getData(srcpath + std::string("/Attack"), value);
			break;
		case ATTR_RANGEDATTACK:
			datalib->getData(srcpath + std::string("/RangedAttack"), value);
			break;
		case ATTR_DEFENCE:
			datalib->getData(srcpath + std::string("/Defence"), value);
			break;
		case ATTR_FORM:
			datalib->getData(srcpath + std::string("/Formation"), value);
			break;
		case ATTR_INITIATIVE:
			datalib->getData(srcpath + std::string("/Initiative"), value);
			break;
		case ATTR_ACTIONPOINT:
			datalib->getData(srcpath + std::string("/ActionPoint"), value);
			break;
		case ATTR_DETECTION:
			datalib->getData(srcpath + std::string("/Detection"), value);
			break;
		case ATTR_COVERT:
			datalib->getData(srcpath + std::string("/Covert"), value);
			break;
		case ATTR_TOUGHNESS:
			datalib->getData(srcpath + std::string("/Toughness"), value);
			break;
		case ATTR_CONTER:
			datalib->getData(srcpath + std::string("/Conter"), value);
			break;
		}
	}
	lua_pushnumber(L,value);
	return 1;
}

static int PlayParticle(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int unittype = luaL_checkinteger(L, 2);
	std::string particlename(luaL_checkstring(L, 3));
	std::string soundname(luaL_checkstring(L, 4));
	int lasttime = luaL_checkinteger(L, 5);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			CutSceneBuilder::getSingleton().addCutScene(
				new EffectCutScene(squad->getSquadId(), (UnitType)unittype, 
				particlename, soundname, lasttime));
		}
	}
	return 0;
}

static int MoveSquad(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int x =  luaL_checknumber(L,2);
	int y =  luaL_checknumber(L,3);
	unsigned int eventflag = MOVEEVENT_WRONG;
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			eventflag = 0;
			BattleSquadManager::getSingleton().forceMoveSquad(squad, Crood(x, y), eventflag);
		}
	}
	lua_pushnumber(L, eventflag);
	return 1;
}
static int ChangeDirection(lua_State* L)
{
	std::string squadid(luaL_checkstring(L, 1));
	int dir = luaL_checknumber(L,2);
	if(StateManager::getSingleton().curState() == StateManager::Battle)
	{
		BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquad(squadid);
		if(squad)
		{
			BattleSquadManager::getSingleton().setDirection(squad, dir);
		}
	}
	return 0;
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
	{"GetMaxActionPoint",GetMaxActionPoint},
	{"GetActionPoint",GetActionPoint},
	{"SetActionPoint",SetActionPoint},
	{"GetFaction",GetFaction},
	{"GetUnitMaxNum",GetUnitMaxNum},
	{"SetUnitMaxNum",SetUnitMaxNum},
	{"GetUnitNum",GetUnitNum},
	{"SetUnitNum",SetUnitNum},
	{"ChangeFormation",ChangeFormation},
	{"AddParticle",AddParticle},
	{"DelParticle",DelParticle},
	{"GetEquip",GetEquip},
	{"AddExp",AddExp},
	{"GetSquadLevel",GetSquadLevel},
	{"ShowValue",ShowValue},
	{"ShowValue1",ShowValue1},
	{"GetSkillLevel",GetSkillLevel},
	{"GetEffectLevelByName",GetEffectLevelByName},
	{"GetType",GetType},
	{"GetSquadType",GetSquadType},
	{"Animation",Animation},
	{"AddSkill",AddSkill},
	{"RemoveSkill",RemoveSkill},
	{"GetSquadAttr", GetSquadAttr},
	{"GetEquipAttr", GetEquipAttr},
	{"PlayParticle", PlayParticle},
	{"MoveSquad", MoveSquad},
	{"ChangeDirection", ChangeDirection},
	{NULL,NULL}
};