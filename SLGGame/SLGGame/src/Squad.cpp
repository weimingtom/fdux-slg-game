#include "Squad.h"

#include <boost/format.hpp>

#include "LuaSystem.h"
#include <OgreLogManager.h>

#define RETURNONERR(a) if(!a) {Ogre::LogManager::getSingletonPtr()->stream()<<__FILE__<<","<<__LINE__<<":RETURNONERR!"; return;}
#define RETURNFALSEONERR(a) if(!a) {Ogre::LogManager::getSingletonPtr()->stream()<<__FILE__<<","<<__LINE__<<":RETURNFALSEONERR!"; return false;}

Squad::Squad(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	mPath = path;
	std::string::size_type i = path.rfind('/');
	mSquadId = path.substr(i + 1,path.size() - i -1);
}

Squad::~Squad()
{
	DataLibrary::getSingleton().delNode(mPath);
}

bool Squad::init(std::string srcpath)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/Name"), mPath + std::string("/Name"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/Describe"), mPath + std::string("/Describe"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/Type"), mPath + std::string("/Type"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/SquadType"), mPath + std::string("/SquadType"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/Level"), mPath + std::string("/Level"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/Exp"), mPath + std::string("/Exp"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/SkillPointAction"), mPath + std::string("/SkillPointAction"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/SkillPointPassive"), mPath + std::string("/SkillPointPassive"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/SkillPointEquip"), mPath + std::string("/SkillPointEquip"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/UnitNum"), mPath + std::string("/UnitNum"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/UnitMesh"), mPath + std::string("/UnitMesh"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/UnitMat"), mPath + std::string("/UnitMat"), true));
	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/MoveSound"), mPath + std::string("/MoveSound"), true));

	std::string tempstr;
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/SoilderId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_SOILDER, tempstr));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/HorseId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_HORSE, tempstr));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/PweaponId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_PWEAPON, tempstr));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/SweaponId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_SWEAPON, tempstr));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/ArmorId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_ARMOR, tempstr));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/ShieldId"), tempstr, true));
	RETURNFALSEONERR(equipEquipment(EQUIP_SHIELD, tempstr));

	RETURNFALSEONERR(datalib->copyNode(srcpath + std::string("/LeaderId"), mPath + std::string("/LeaderId"), true));
	RETURNFALSEONERR(datalib->getData(srcpath + std::string("/RetainerId"), tempstr, true));
	RETURNFALSEONERR(hireRetainer(tempstr));

	int squadtype;
	datalib->getData(mPath + std::string("/SquadType"), squadtype);
	std::string defaultskillpath;
	switch(squadtype)
	{
	case SQUADTYPE_INFANTRY:
		defaultskillpath = "StaticData/SkillListData/Infantry/Default";
		break;
	case SQUADTYPE_MISSILEINFANTRY:
		defaultskillpath = "StaticData/SkillListData/MissileInfantry/Default";
		break;
	case SQUADTYPE_SAINT:
		defaultskillpath = "StaticData/SkillListData/Saint/Default";
		break;
	}
	std::vector<std::string> skilltable = datalib->getChildList(defaultskillpath);
	std::vector<std::string>::iterator ite;
	for(ite = skilltable.begin(); ite != skilltable.end(); ite++)
	{	
		//RETURNONERR(datalib->getData(defaultskillpath + std::string("/") + (*ite), tempstr, true));
		RETURNFALSEONERR(addSkill((*ite)));
	}

	skilltable.clear();
	skilltable = datalib->getChildList(srcpath + std::string("/SkillTable"));
	int type = 0;
	for(ite = skilltable.begin(); ite != skilltable.end(); ite++)
	{	
		RETURNFALSEONERR(datalib->getData(srcpath + std::string("/SkillTable/") + (*ite), type, true));
		RETURNFALSEONERR(learnSkill(type, (*ite)));
	}
	return true;
}
bool Squad::init()
{
	return true;
}

bool Squad::applyModifer(std::string modifierpath, std::string &modifierid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/ModifierList");
	std::vector<std::string> modifierlist = datalib->getChildList(distpath);
	int x = 0;
	modifierid = std::string("m") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	while(ite != modifierlist.end())
	{
		x = x + 1;
		modifierid = std::string("m") + Ogre::StringConverter::toString(x);
		ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	}
	distpath = distpath + std::string("/") + modifierid;
	if(datalib->copyNode(modifierpath, distpath, true))
		return true;
	return false;
}
bool Squad::applyModifer(AttrModifier* modifier, std::string &modifierid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/ModifierList");
	std::vector<std::string> modifierlist = datalib->getChildList(distpath);
	int x = 0;
	modifierid = std::string("m") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	while(ite != modifierlist.end())
	{
		x = x + 1;
		modifierid = std::string("m") + Ogre::StringConverter::toString(x);
		ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	}
	distpath = distpath + std::string("/") + modifierid;
	datalib->setData(distpath + std::string("/Type"), modifier->Type, true);
	datalib->setData(distpath + std::string("/Attack"), modifier->Attack, true);
	datalib->setData(distpath + std::string("/RangedAttack"), modifier->RangedAttack, true);
	datalib->setData(distpath + std::string("/Defence"), modifier->Defence, true);
	datalib->setData(distpath + std::string("/Formation"), modifier->Form, true);
	datalib->setData(distpath + std::string("/Initiative"), modifier->Initiative, true);
	datalib->setData(distpath + std::string("/ActionPoint"), modifier->ActionPoint, true);
	datalib->setData(distpath + std::string("/Detection"), modifier->Detection, true);
	datalib->setData(distpath + std::string("/Covert"), modifier->Covert, true);
	datalib->setData(distpath + std::string("/Toughness"), modifier->Toughness, true);
	datalib->setData(distpath + std::string("/Conter"), modifier->Conter, true);
	return true;
}
void Squad::removeModifier(std::string modifierid)
{
	std::string particlepath = mPath + std::string("/ModifierList/") + modifierid;
	DataLibrary::getSingleton().delNode(particlepath);
}

bool Squad::equipEquipment(int equiptype, std::string equipid)
{
	unloadEquipment(equiptype);
	if(equipid == "none")
	{
		return true;
	}
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string srcpath;
	std::string distpath;
	switch(equiptype)
	{
	case EQUIP_ARMOR:
		srcpath = "StaticData/ArmorData";
		distpath = mPath + std::string("/ArmorId");
		break;
	case EQUIP_HORSE:
		srcpath = "StaticData/HorseData";
		distpath = mPath + std::string("/HorseId");
		break;
	case EQUIP_SOILDER:
		srcpath = "StaticData/SoilderData";
		distpath = mPath + std::string("/SoilderId");
		break;
	case EQUIP_SHIELD:
		srcpath = "StaticData/ShieldData";
		distpath = mPath + std::string("/ShieldId");
		break;
	case EQUIP_PWEAPON:
		srcpath = "StaticData/PweaponData";
		distpath = mPath + std::string("/PweaponId");
		break;
	case EQUIP_SWEAPON:
		srcpath = "StaticData/SweaponData";
		distpath = mPath + std::string("/SweaponId");
		break;
	}
	std::vector<std::string> srcequiplist = datalib->getChildList(srcpath);
	std::vector<std::string>::iterator ite = std::find(srcequiplist.begin(), srcequiplist.end(), equipid);
	if(ite == srcequiplist.end())
		return false;
	datalib->setData(distpath, (*ite));
	std::string tempstr;
	if(!applyModifer(srcpath + std::string("/") + equipid + std::string("/AttrModifer"), tempstr))
		return false;
	datalib->setData(distpath + std::string("/Modifierid"), tempstr, true);

	//调用装备脚本
	std::string	scriptpath;
	datalib->getData(str(boost::format("%1%/%2%/Script")%srcpath%equipid), scriptpath);
	if(scriptpath != "none")
	{
		std::string contexpath = str(boost::format("%1%/ScriptContext")%distpath);
		LuaTempContext* tempcontext = new LuaTempContext;
		tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
		LuaSystem::getSingleton().executeFunction(scriptpath ,"onequip",contexpath, tempcontext);
		delete tempcontext;
	}

	return true;
}

void Squad::unloadEquipment(int equiptype)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath;
	std::string srcpath;
	switch(equiptype)
	{
	case EQUIP_ARMOR:
		srcpath = "StaticData/ArmorData";
		distpath = mPath + std::string("/ArmorId");
		break;
	case EQUIP_HORSE:
		srcpath = "StaticData/HorseData";
		distpath = mPath + std::string("/HorseId");
		break;
	case EQUIP_SOILDER:
		srcpath = "StaticData/SoilderData";
		distpath = mPath + std::string("/SoilderId");
		break;
	case EQUIP_SHIELD:
		srcpath = "StaticData/ShieldData";
		distpath = mPath + std::string("/ShieldId");
		break;
	case EQUIP_PWEAPON:
		srcpath = "StaticData/PweaponData";
		distpath = mPath + std::string("/PweaponId");
		break;
	case EQUIP_SWEAPON:
		srcpath = "StaticData/SweaponData";
		distpath = mPath + std::string("/SweaponId");
		break;
	}
	
	std::string itemID;
	bool re = datalib->getData(distpath, itemID);
	if(!re)
	{
		datalib->setData(distpath, std::string("none"), true);
		return;
	}
	else if(itemID == "none")
		return;

	std::string tempstr;
	re = datalib->getData(distpath + std::string("/Modifierid"), tempstr);
	if(re)
	{
		removeModifier(tempstr);
	}

	//调用装备脚本
	std::string	scriptpath;
	datalib->getData(str(boost::format("%1%/%2%/Script")%srcpath%itemID), scriptpath);
	if(scriptpath != "none")
	{
		std::string contexpath = str(boost::format("%1%/ScriptContext")%distpath);
		LuaTempContext* tempcontext = new LuaTempContext;
		tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
		LuaSystem::getSingleton().executeFunction(scriptpath ,"onunload",contexpath, tempcontext);
		delete tempcontext;
	}

	datalib->delNode(distpath);
	datalib->setData(distpath, std::string("none"), true);
}

std::string Squad::getEquipment(int equiptype)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string equip("none");
	switch(equiptype)
	{
	case EQUIP_ARMOR:
		datalib->getData(mPath + std::string("/ArmorId"), equip);
		break;
	case EQUIP_HORSE:
		datalib->getData(mPath + std::string("/HorseId"), equip);
		break;
	case EQUIP_SOILDER:
		datalib->getData(mPath + std::string("/SoilderId"), equip);
		break;
	case EQUIP_SHIELD:
		datalib->getData(mPath + std::string("/ShieldId"), equip);
		break;
	case EQUIP_PWEAPON:
		datalib->getData(mPath + std::string("/PweaponId"), equip);
		break;
	case EQUIP_SWEAPON:
		datalib->getData(mPath + std::string("/SweaponId"), equip);
		break;
	}
	return equip;
}

bool Squad::learnSkill(int skilltype, std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int squadtype;
	datalib->getData(mPath + std::string("/SquadType"), squadtype);
	std::string defaultskillpath;
	switch(squadtype)
	{
	case SQUADTYPE_INFANTRY:
		defaultskillpath = "StaticData/SkillListData/Infantry/";
		break;
	case SQUADTYPE_MISSILEINFANTRY:
		defaultskillpath = "StaticData/SkillListData/MissileInfantry/";
		break;
	case SQUADTYPE_SAINT:
		defaultskillpath = "StaticData/SkillListData/Saint/";
		break;
	}
	switch(skilltype)
	{
	case SKILLTYPE_PASSIVE:
		{
			defaultskillpath = defaultskillpath + std::string("Passive");
			std::vector<std::string> skilltable = datalib->getChildList(defaultskillpath);
			std::vector<std::string>::iterator ite;
			ite = std::find(skilltable.begin(), skilltable.end(), skillid);
			//ite = skilltable.find(skillid);
			if(ite != skilltable.end())
			{
				std::string effect;
				datalib->getData(str(boost::format("%1%/%2%/Effect")%defaultskillpath%skillid), effect);
				std::string eid;
				if(applyEffect(effect, eid))
				{
					datalib->setData(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid), skilltype);
					datalib->setData(str(boost::format("%1%/SkillTable/%2%/EffectId")%mPath%skillid), eid);
					return true;
				}
			}
		}
		break;
	case SKILLTYPE_ACTIVE:
		{
			defaultskillpath = defaultskillpath + std::string("Active");
			std::vector<std::string> skilltable = datalib->getChildList(defaultskillpath);
			std::vector<std::string>::iterator ite;
			ite = std::find(skilltable.begin(), skilltable.end(), skillid);
			if(ite != skilltable.end())
			{
				if(addSkill(skillid))
				{
					datalib->setData(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid), skilltype);
					return true;
				}
			}
		}
		datalib->setData(mPath + std::string("/SkillTable/") + skillid, skilltype);
		break;
	case SKILLTYPE_EQUIP:
		{
			defaultskillpath = defaultskillpath + std::string("Equip");
			std::vector<std::string> skilltable = datalib->getChildList(defaultskillpath);
			std::vector<std::string>::iterator ite;
			ite = std::find(skilltable.begin(), skilltable.end(), skillid);
			if(ite != skilltable.end())
			{
				datalib->setData(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid), skilltype);
				return true;
			}
		}
		break;
	}
	return false;
}

void Squad::forgetSkill(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int skilltype;
	datalib->getData(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid), skilltype);
	switch(skilltype)
	{
	case SKILLTYPE_PASSIVE:
		{
			std::string eid;
			datalib->getData(str(boost::format("%1%/SkillTable/%2%/EffectId")%mPath%skillid), eid);
			removeEffect(eid);
			datalib->delNode(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid));
		}
		break;
	case SKILLTYPE_ACTIVE:
		{
			removeSkill(skillid);
			datalib->delNode(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid));
		}
		break;
	case SKILLTYPE_EQUIP:
		datalib->delNode(str(boost::format("%1%/SkillTable/%2%")%mPath%skillid));
		break;
	}
}

void Squad::addExp(int exp)
{
	int squadtype = getType() ;
	int maxlv = (squadtype == SQUAD_NORMAL)?10:8;
	int expperlv = 1000;
	int curlevel = getLevel();
	if(exp < 0 || curlevel == maxlv)
		return;
	int curexp = getExp();
	curexp += exp;
	while(curexp > expperlv)
	{
		curlevel += 1;
		if(curlevel == maxlv)
			curexp = 0;
		else
			curexp -= expperlv;
		int skillpoint = 0;
		if(squadtype == SQUAD_SPECIAL)
		{
			switch(curlevel)
			{
			case 2:
			case 4:
			case 6:
			case 8:
				skillpoint = getSkillPointPassive();
				skillpoint += 1;
				setSkillPointPassive(skillpoint);
				break;
			case 1:
			case 3:
			case 5:
			case 7:
				skillpoint = getSkillPointAction();
				skillpoint += 1;
				setSkillPointAction(skillpoint);
				break;
			}
		}
		else
		{
			switch(curlevel)
			{
			case 2:
			case 5:
			case 8:
			case 10:
				skillpoint = getSkillPointAction();
				skillpoint += 1;
				setSkillPointAction(skillpoint);
				break;
			case 1:
			case 3:
			case 4:
			case 7:
			case 9:
				skillpoint = getSkillPointPassive();
				skillpoint += 1;
				setSkillPointPassive(skillpoint);
				break;
			case 6:
				skillpoint = getSkillPointEquip();
				skillpoint += 1;
				setSkillPointEquip(skillpoint);
				break;
			}
		}
	}
	setExp(curexp);
	setLevel(curlevel);
}

bool Squad::hireRetainer(std::string retainerid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	fireRetainer();
	if(retainerid == "none")
		return true;
	std::string distpath = mPath + std::string("/RetainerId");
	std::string srcpath = "StaticData/RetainerData";
	std::vector<std::string> srcequiplist = datalib->getChildList(srcpath);
	std::vector<std::string>::iterator ite = std::find(srcequiplist.begin(), srcequiplist.end(), retainerid);
	if(ite == srcequiplist.end())
		return false;
	datalib->setData(distpath, retainerid);
	srcpath = str(boost::format("%1%/%2%")%srcpath%retainerid);
	std::string skillid;
	datalib->getData(srcpath + std::string("/Skill"), skillid);
	int skilltype;
	datalib->getData(srcpath + std::string("/SkillType"), skilltype);
	switch(skilltype)
	{
	case 0:
		{
			std::string eid;
			if(applyEffect(skillid, eid))
			{
				datalib->setData(distpath + std::string("/EffectId"), eid);
				return true;
			}
		}
		break;
	case 1:
		{
			if(addSkill(skillid))
			{
				datalib->setData(distpath + std::string("/SkillId"), skillid);
				return true;
			}
		}
		break;
	}
	return false;
}
void Squad::fireRetainer()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/RetainerId");
	std::string tempstr;
	datalib->getData(distpath , tempstr);
	if(tempstr == "none")
		return;
	if(datalib->getData(distpath + std::string("/EffectId"), tempstr))
	{
		removeEffect(tempstr);
		datalib->delNode(distpath + std::string("/EffectId"));
	}

	if(datalib->getData(distpath + std::string("/SkillId"), tempstr))
	{
		removeSkill(tempstr);
		datalib->delNode(distpath + std::string("/SkillId"));
	}
}

bool Squad::addSkill(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/Skill/") + skillid;
	int skilllev = 1;
	bool re = datalib->getData(distpath, skilllev ,true);
	if(re)
	{
		skilllev += 1;
		datalib->setData(distpath, skilllev);
		return true;
	}
	std::vector<std::string> skilldata = datalib->getChildList("StaticData/SkillData");
	std::vector<std::string>::iterator ite = std::find(skilldata.begin(), skilldata.end(), skillid);
	if(ite == skilldata.end())
	{
		return false;
	}
	datalib->setData(distpath, skilllev);
	return true;
}
void Squad::removeSkill(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/Skill/") + skillid;
	int skilllev = 0;
	bool re = datalib->getData(distpath, skilllev,true);
	if(re)
	{
		skilllev -= 1;
		if(skilllev == 0)
			datalib->delNode(distpath);
		else
			datalib->setData(distpath, skilllev);
	}
}

bool Squad::applyEffect(std::string effectid, std::string &eid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int effecttype;
	bool re  = datalib->getData(str(boost::format("StaticData/EffectData/%1%/Type")%effectid), effecttype);
	if(re)
	{
		std::string scriptpath;
		datalib->getData(str(boost::format("StaticData/EffectData/%1%/Script")%effectid), scriptpath);
		std::string distpath = mPath + std::string("/Effect");
		std::vector<std::string> effectlist = datalib->getChildList(distpath);
		std::vector<std::string>::iterator ite;
		bool addeffect = true;
		if(effecttype != EFFECTTYPE_UNIQUE )
		{
			std::string tempeffectid;
			for(ite = effectlist.begin(); ite != effectlist.end(); ite++)
			{
				datalib->getData(str(boost::format("%1%/%2%/EffectId")%distpath%(*ite)), tempeffectid);
				if(tempeffectid == effectid)
				{
					if(effecttype == EFFECTTYPE_NORMAL)
					{
						addeffect = false;
						eid = (*ite);
						int effectlevel = 0;
						datalib->getData(str(boost::format("%1%/%2%")%distpath%(*ite)), effectlevel);
						effectlevel += 1;
						datalib->setData(str(boost::format("%1%/%2%")%distpath%(*ite)), effectlevel);
						//调用效果脚本
						std::string contexpath = str(boost::format("%1%/%2%/ScriptContext")%distpath%eid);
						LuaTempContext* tempcontext = new LuaTempContext;
						tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
						tempcontext->strMap.insert(std::make_pair("effectid", eid));
						LuaSystem::getSingleton().executeFunction(scriptpath ,"onaffect",contexpath, tempcontext);
						delete tempcontext;
					}
					else
					{
						removeEffect((*ite));
					}
					break;
				}
			}
		}
		if(addeffect)
		{
			int x = 0;
			eid = std::string("e") + Ogre::StringConverter::toString(x);
			ite = std::find(effectlist.begin(), effectlist.end(),eid);
			while(ite != effectlist.end())
			{
				x = x + 1;
				eid = std::string("e") + Ogre::StringConverter::toString(x);
				ite = std::find(effectlist.begin(), effectlist.end(),eid);
			}
			datalib->setData(str(boost::format("%1%/%2%")%distpath%eid), 1);
			datalib->setData(str(boost::format("%1%/%2%/EffectId")%distpath%eid), effectid);
			//调用效果脚本
			std::string contexpath = str(boost::format("%1%/%2%/ScriptContext")%distpath%eid);
			LuaTempContext* tempcontext = new LuaTempContext;
			tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
			tempcontext->strMap.insert(std::make_pair("effectid", eid));
			LuaSystem::getSingleton().executeFunction(scriptpath ,"onaffect",contexpath, tempcontext);
			delete tempcontext;
		}
		return true;
	}
	return false;
}
void Squad::removeEffect(std::string eid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/Effect/") + eid;
	int effectlevel = 0;
	bool re = datalib->getData(distpath, effectlevel, true);
	if(re)
	{
		std::string effectid;
		datalib->getData(str(boost::format("%1%/EffectId")%distpath), effectid);
		int effecttype;
		bool re  = datalib->getData(str(boost::format("StaticData/EffectData/%1%/Type")%effectid), effecttype);
		std::string scriptpath;
		datalib->getData(str(boost::format("StaticData/EffectData/%1%/Script")%effectid), scriptpath);
		if(effecttype == EFFECTTYPE_NORMAL && effectlevel > 1)
		{
			effectlevel -= 1;
			datalib->setData(distpath, effectlevel);
			//调用效果脚本
			std::string contexpath = str(boost::format("%1%/ScriptContext")%distpath);
			LuaTempContext* tempcontext = new LuaTempContext;
			tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
			tempcontext->strMap.insert(std::make_pair("effectid", eid));
			LuaSystem::getSingleton().executeFunction(scriptpath ,"onaffect",contexpath, tempcontext);
			delete tempcontext;
			return;
		}
		//调用效果脚本
		std::string contexpath = str(boost::format("%1%/ScriptContext")%distpath);
		LuaTempContext* tempcontext = new LuaTempContext;
		tempcontext->strMap.insert(std::make_pair("squadid", mSquadId));
		tempcontext->strMap.insert(std::make_pair("effectid", eid));
		LuaSystem::getSingleton().executeFunction(scriptpath ,"onremove",contexpath, tempcontext);
		delete tempcontext;
		datalib->delNode(distpath);
	}
}

int Squad::getEffectLevel(std::string eid)
{
	int lv = 0;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/Effect/") + eid;
	datalib->getData(distpath, lv);
	return lv;
}

float Squad::getAttr(int attrtype , int calctype)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> modifierlist = datalib->getChildList(mPath + std::string("/ModifierList"));
	if(modifierlist.size() == 0)
		return 0.0f;
	if(attrtype == ATTR_RANGEDDEFENCE )
		attrtype = ATTR_DEFENCE;
	float base = 0.0f;
	float mbouse = 0.0f;
	float mbane = 0.0f;
	float resist = 0.0f;
	float cbouse = 0.0f;
	float cbane = 0.0f;
	std::vector<std::string>::iterator ite;
	for(ite = modifierlist.begin(); ite != modifierlist.end(); ite++)
	{
		int type = ATTRMODIFIER_BASE;
		float attrval = 0.0f;
		std::string datapath = mPath + std::string("/ModifierList/") + (*ite);
		datalib->getData(datapath + std::string("/Type"), type);
		switch(attrtype)
		{
		case ATTR_ATTACK:
			datalib->getData(datapath + std::string("/Attack"), attrval);
			break;
		case ATTR_RANGEDATTACK:
			datalib->getData(datapath + std::string("/RangedAttack"), attrval);
			break;
		case ATTR_DEFENCE:
			datalib->getData(datapath + std::string("/Defence"), attrval);
			break;
		case ATTR_FORM:
			datalib->getData(datapath + std::string("/Formation"), attrval);
			break;
		case ATTR_INITIATIVE:
			datalib->getData(datapath + std::string("/Initiative"), attrval);
			break;
		case ATTR_ACTIONPOINT:
			datalib->getData(datapath + std::string("/ActionPoint"), attrval);
			break;
		case ATTR_DETECTION:
			datalib->getData(datapath + std::string("/Detection"), attrval);
			break;
		case ATTR_COVERT:
			datalib->getData(datapath + std::string("/Covert"), attrval);
			break;
		case ATTR_TOUGHNESS:
			datalib->getData(datapath + std::string("/Toughness"), attrval);
			break;
		case ATTR_CONTER:
			datalib->getData(datapath + std::string("/Conter"), attrval);
			break;
		}
		switch(type)
		{
		case ATTRMODIFIER_BASE:
			base += attrval;
			break;
		case ATTRMODIFIER_MAGIC:
			if(attrval > mbouse)
				mbouse = attrval;
			if(attrval < mbane)
				mbane = attrval;
			break;
		case ATTRMODIFIER_COMMAND:
			if(attrval > cbouse)
				cbouse = attrval;
			if(attrval < cbane)
				cbane = attrval;
			break;
		case ATTRMODIFIER_RESISTANCE:
			if(attrval > resist)
				resist = attrval;
			break;
		}
	}
	float bouse = cbouse + mbouse;
	float bane = cbane + mbane;
	if(bane < -resist)
	{
		bane += resist;
		resist = 0.0f;
	}
	else
	{
		bane = 0.0f;
		resist += bane;
	}

	bouse = bouse + bane;
	switch(calctype)
	{
	case ATTRCALC_FULL:
		return base + bouse;
		break;
	case ATTRCALC_ONLYBASE:
		return base;
		break;
	case ATTRCALC_ONLYBONUS:
		return bouse;
		break;
	}
	return 0.0f;
}

std::string Squad::addTrigger(std::string trigertype, std::string file ,std::string func, std::string context)
{
	int newid = 0;
	int test;
	while(DataLibrary::getSingleton().getData(str(boost::format("%1%/Trigger/T%2%")%mPath%newid),test,true))
		newid++;
	DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/T%2%")%mPath%newid),0);
	DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/T%2%/type")%mPath%newid),trigertype);
	DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/T%2%/file")%mPath%newid),file);
	DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/T%2%/func")%mPath%newid),func);
	DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/T%2%/context")%mPath%newid),context);
	return std::string("T") + Ogre::StringConverter::toString(newid);
}
void Squad::removeTrigger(std::string tid)
{
	std::string particlepath = str(boost::format("%1%/Trigger/%2%")%mPath%tid);
	DataLibrary::getSingleton().delNode(particlepath);
}

void Squad::activeTrigger(std::string tid)
{
	int test;
	if(DataLibrary::getSingleton().getData(str(boost::format("%1%/Trigger/%2%")%mPath%tid),test,true))
	{
		DataLibrary::getSingleton().setData(str(boost::format("%1%/Trigger/%2%")%mPath%tid),1);
	}
}

void Squad::disableTrigger(std::string tid)
{
	int test;
	if(DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Trigger/%1%")%tid),test,true))
	{
		DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/%1%")%tid),0);
	}
}

void Squad::Trigger(std::string triggertype, LuaTempContext * tempcontext)
{
	if(tempcontext == NULL)
		return;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> triggerlist;
	triggerlist = datalib->getChildList(mPath + std::string("/Trigger"));
	std::vector<std::string>::iterator ite;
	for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
	{
		std::string datapath = mPath + std::string("/Trigger/") + (*ite);
		int active;
		datalib->getData(datapath,active);
		if(!active)
			continue;
		std::string type;
		datalib->getData(datapath + std::string("/type"),type);
		if(type != triggertype)
			continue;
		std::string context,filename,funcname;
		datalib->getData(datapath + std::string("/file"),filename);
		datalib->getData(datapath + std::string("/func"),funcname);
		datalib->getData(datapath + std::string("/context"),context);
		LuaSystem::getSingleton().executeFunction(filename,funcname,context,tempcontext);
	}
}

std::map<std::string, int> Squad::getSkillTable()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::map<std::string, int> skilllist;
	std::vector<std::string> skilltable = datalib->getChildList(mPath + std::string("/SkillTable"));
	int type = 0;
	std::vector<std::string>::iterator ite;
	for(ite = skilltable.begin(); ite != skilltable.end(); ite++)
	{	
		datalib->getData(mPath + std::string("/SkillTable/") + (*ite), type, true);
		skilllist.insert(std::make_pair((*ite), type));
	}
	return skilllist;
}