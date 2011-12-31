#include "Squad.h"

#include <boost/format.hpp>

#include "DataLibrary.h"
#include "StringTable.h"

#define RETURNONERR(a) if(!a) return;
#define RETURNFALSEONERR(a) if(!a) return false;

Squad::Squad(std::string path, std::string srcpath)
{
	mInit = false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	mPath = path;
	std::string::size_type i = path.rfind('/');
	mSquadId = path.substr(i + 1,path.size() - i -1);
	RETURNONERR(datalib->copyNode(srcpath + std::string("/Name"), mPath + std::string("/Name"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/Describe"), mPath + std::string("/Describe"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/Type"), mPath + std::string("/Type"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/SquadType"), mPath + std::string("/SquadType"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/LeaderId"), mPath + std::string("/LeaderId"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/Level"), mPath + std::string("/Level"), true));
	RETURNONERR(datalib->copyNode(srcpath + std::string("/Exp"), mPath + std::string("/Exp"), true));

	std::string tempstr;
	RETURNONERR(datalib->getData(srcpath + std::string("/SoilderId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_SOILDER, tempstr));
	RETURNONERR(datalib->getData(srcpath + std::string("/HorseId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_HORSE, tempstr));
	RETURNONERR(datalib->getData(srcpath + std::string("/PweaponId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_PWEAPON, tempstr));
	RETURNONERR(datalib->getData(srcpath + std::string("/SweaponId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_SWEAPON, tempstr));
	RETURNONERR(datalib->getData(srcpath + std::string("/ArmorId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_ARMOR, tempstr));
	RETURNONERR(datalib->getData(srcpath + std::string("/ShieldId"), tempstr, true));
	RETURNONERR(equipEquipment(EQUIP_SHIELD, tempstr));

	RETURNONERR(datalib->getData(srcpath + std::string("/RetainerID"), tempstr, true));
	RETURNONERR(hireRetainer(tempstr));

	std::vector<std::string> skilltable = datalib->getChildList(srcpath + std::string("/SkillTable"));
	std::vector<std::string>::iterator ite;
	enumtype type = 0;
	for(ite = skilltable.begin(); ite != skilltable.end(); ite++)
	{	
		RETURNONERR(datalib->getData(srcpath + std::string("/") + (*ite), type, true));
		RETURNONERR(learnSkill(type, (*ite)));
	}

	mInit = true;
}

Squad::Squad(std::string path)
{
	mInit = false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	mPath = path;
	std::string::size_type i = path.rfind('/');
	mSquadId = path.substr(i + 1,path.size() - i -1);
	mInit = true;
}

Squad::~Squad()
{
	DataLibrary::getSingleton().delNode(mPath);
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
	datalib->setData(distpath + std::string("/Injury"), modifier->Morale, true);
	datalib->setData(distpath + std::string("/Conter"), modifier->Conter, true);
	return false;
}
void Squad::removeModifier(std::string modifierid)
{
	std::string particlepath = mPath + std::string("/ModifierList/") + modifierid;
	DataLibrary::getSingleton().delNode(particlepath);
}

bool Squad::equipEquipment(enumtype equiptype, std::string equipid)
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

	return true;
}

void Squad::unloadEquipment(enumtype equiptype)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath;
	switch(equiptype)
	{
	case EQUIP_ARMOR:
		distpath = mPath + std::string("/ArmorId");
		break;
	case EQUIP_HORSE:
		distpath = mPath + std::string("/HorseId");
		break;
	case EQUIP_SOILDER:
		distpath = mPath + std::string("/SoilderId");
		break;
	case EQUIP_SHIELD:
		distpath = mPath + std::string("/ShieldId");
		break;
	case EQUIP_PWEAPON:
		distpath = mPath + std::string("/PweaponId");
		break;
	case EQUIP_SWEAPON:
		distpath = mPath + std::string("/SweaponId");
		break;
	}
	std::string tempstr;
	bool re = datalib->getData(distpath, tempstr);
	if(!re)
	{
		datalib->setData(distpath, std::string("none"), true);
		return;
	}
	else if(tempstr == "none")
		return;

	re = datalib->getData(distpath + std::string("/Modifierid"), tempstr);
	if(re)
	{
		removeModifier(tempstr);
	}

	datalib->delNode(distpath);
	datalib->setData(distpath, std::string("none"), true);
}

bool Squad::learnSkill(enumtype skilltype, std::string skillid)
{
	return false;
}

void Squad::removeSkill(enumtype skilltype, std::string skillid)
{

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
	std::string skillid;
	datalib->getData(srcpath + std::string("/Skill"), skillid);
	enumtype skilltype;
	datalib->getData(srcpath + std::string("/SkillType"), skilltype);
	switch(skilltype)
	{
	case 0:
		{
			std::string eid;
			bool re = applyEffect(skillid, eid);
			if(re)
				datalib->setData(distpath + std::string("/EffectId"), eid);
		}
		break;
	case 1:
		{
			addSkill(skillid);
		}
		break;
	}
	return false;
}
void Squad::fireRetainer()
{

}

bool Squad::addSkill(std::string skillid)
{
	return false;
}
void Squad::removeSkill(std::string skillid)
{
	
}

bool Squad::applyEffect(std::string effectid, std::string &eid)
{
	return false;
}
void Squad::removeEffect(std::string eid)
{

}

float Squad::getAttr(enumtype attrtype , enumtype calctype)
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
		enumtype type = ATTRMODIFIER_BASE;
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
		case ATTR_MORALE:
			datalib->getData(datapath + std::string("/Injury"), attrval);
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