#include "AVGSquadManager.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "LuaSystem.h"
#include "boost/format.hpp"

AVGSquadManager::AVGSquadManager()
{

}
AVGSquadManager::~AVGSquadManager()
{

}
bool AVGSquadManager::addSquad(std::string uid, std::string id, std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> squadlist = datalib->getChildList("StaticData/SquadData");
	std::vector<std::string>::iterator ite = std::find(squadlist.begin(), squadlist.end(),id);
	if(ite == squadlist.end())
		return false;
	std::string datasrcpath = "StaticData/SquadData/" + (*ite);
	std::string datadistpath;
	if(path == "GameData/StoryData/SquadData")
	{
		std::vector<std::string> activesquadlist = datalib->getChildList("GameData/StoryData/SquadData/EnableSquad");
		std::vector<std::string> disactivesquadlist = datalib->getChildList("GameData/StoryData/SquadData/DisableSquad");
		ite = std::find(activesquadlist.begin(), activesquadlist.end(),uid);
		if(ite != activesquadlist.end())
			return false;
		ite = std::find(disactivesquadlist.begin(), disactivesquadlist.end(),uid);
		if(ite != disactivesquadlist.end())
			return false;
		datadistpath = "GameData/StoryData/SquadData/EnableSquad/" + uid;
	}
	else
	{
		std::vector<std::string> distsquadlist = datalib->getChildList(path);
		ite = std::find(distsquadlist.begin(), distsquadlist.end(),uid);
		if(ite != distsquadlist.end())
			return false;
		datadistpath = path + std::string("/")  + uid;
	}

	std::string tempstring;
	int tempint;
	bool re = datalib->getData(datasrcpath + std::string("/Name"),tempstring);
	datalib->setData(datadistpath + std::string("/Name"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/Describe"),tempstring);
	datalib->setData(datadistpath + std::string("/Describe"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/Type"),tempint);
	datalib->setData(datadistpath + std::string("/Type"), tempint, true);

	re = datalib->getData(datasrcpath + std::string("/SquadType"),tempint);
	datalib->setData(datadistpath + std::string("/SquadType"), tempint, true);

	re = datalib->getData(datasrcpath + std::string("/LeaderName"),tempstring);
	tempstring = StringTable::getSingleton().getString(tempstring);
	datalib->setData(datadistpath + std::string("/LeaderName"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/LeaderPicture"),tempstring);
	datalib->setData(datadistpath + std::string("/LeaderPicture"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/LeaderMesh"),tempstring);
	datalib->setData(datadistpath + std::string("/LeaderMesh"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/LeaderMat"),tempstring);
	datalib->setData(datadistpath + std::string("/LeaderMat"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/UnitMesh"),tempstring);
	datalib->setData(datadistpath + std::string("/UnitMesh"), tempstring, true);
	re = datalib->getData(datasrcpath + std::string("/UnitMat"),tempstring);
	datalib->setData(datadistpath + std::string("/UnitMat"), tempstring, true);

	datalib->getData(datasrcpath + std::string("/MoveSound"),tempstring);
	datalib->setData(datadistpath + std::string("/MoveSound"), tempstring, true);

//	re = datalib->getData(datasrcpath + std::string("/UnitEffect"),tempstring);
//	datalib->setData(datadistpath + std::string("/UnitEffect"), tempstring, true);
// 		re = datalib->getData(datasrcpath + std::string("/UnitEffect/EffectName"),tempstring);
// 		datalib->setData(datadistpath + std::string("/UnitEffect/EffectName"), tempstring, true);
// 		Ogre::Vector3 v;
// 		re = datalib->getData(datasrcpath + std::string("/UnitEffect/EffectOffect"),v);
// 		datalib->setData(datadistpath + std::string("/UnitEffect/EffectOffect"), v, true);

	re = datalib->getData(datasrcpath + std::string("/UnitMaxNumber"),tempint);
	datalib->setData(datadistpath + std::string("/UnitMaxNumber"), tempint, true);
	datalib->setData(datadistpath + std::string("/UnitNumber"), tempint, true);

	datalib->setData(datadistpath + std::string("/Morale"), 67, true);
	
	//装备
	re = datalib->getData(datasrcpath + std::string("/SoilderId"),tempstring);
	equipEquipment(datadistpath, EQUIP_SOILDER, tempstring);
	re = datalib->getData(datasrcpath + std::string("/HorseId"),tempstring);
	equipEquipment(datadistpath, EQUIP_HORSE, tempstring);
	re = datalib->getData(datasrcpath + std::string("/PweaponId"),tempstring);
	equipEquipment(datadistpath, EQUIP_PWEAPON, tempstring);
	re = datalib->getData(datasrcpath + std::string("/SweaponId"),tempstring);
	equipEquipment(datadistpath, EQUIP_SWEAPON, tempstring);
	re = datalib->getData(datasrcpath + std::string("/ArmorId"),tempstring);
	equipEquipment(datadistpath, EQUIP_ARMOR, tempstring);
	re = datalib->getData(datasrcpath + std::string("/ShieldId"),tempstring);
	equipEquipment(datadistpath, EQUIP_SHIELD, tempstring);

	//技能
	std::vector<std::string> skilllist = datalib->getChildList(datasrcpath + std::string("/SkillTable"));
	for(ite = skilllist.begin(); ite != skilllist.end(); ite++)
	{
		learnSkill(datadistpath,(*ite));
	}

	return true;
}

void AVGSquadManager::modifyMorale(std::string id, int morale)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	bool all  = false;
	if(id == "none")
		all = true;
	std::vector<std::string> activesquadlist = datalib->getChildList("GameData/StoryData/SquadData/EnableSquad");
	std::vector<std::string>::iterator ite;
	float moralemodi = 1.0f;
	int morale1 = 0;
	std::string path;
	for(ite = activesquadlist.begin(); ite != activesquadlist.end(); ite++)
	{
		if(all || id == (*ite))
		{
			path = str(boost::format("GameData/StoryData/SquadData/EnableSquad/%1%")%(*ite));
			moralemodi = getSquadAttr(path,ATTR_TOUGHNESS,ATTRCALC_FULL,moralemodi);
			path = path + "/Morale";
			datalib->getData(path,morale1);
			morale1 += floor(moralemodi * morale + 0.5f);
			datalib->setData(path,morale1);
		}
	}
}

bool AVGSquadManager::equipEquipment(std::string path, enumtype type, std::string id)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string srcpath;
	std::string distpath;
	switch(type)
	{
	case EQUIP_ARMOR:
		srcpath = "StaticData/ArmorData";
		distpath = path + std::string("/ArmorId");
		break;
	case EQUIP_HORSE:
		srcpath = "StaticData/HorseData";
		distpath = path + std::string("/HorseId");
		break;
	case EQUIP_SOILDER:
		srcpath = "StaticData/SoilderData";
		distpath = path + std::string("/SoilderId");
		break;
	case EQUIP_SHIELD:
		srcpath = "StaticData/ShieldData";
		distpath = path + std::string("/ShieldId");
		break;
	case EQUIP_PWEAPON:
		srcpath = "StaticData/PweaponData";
		distpath = path + std::string("/PweaponId");
		break;
	case EQUIP_SWEAPON:
		srcpath = "StaticData/SweaponData";
		distpath = path + std::string("/SweaponId");
		break;
	}
	if(id == "none")
	{
		datalib->setData(distpath, std::string("none"), true);
		return true;
	}
	std::vector<std::string> srcequiplist = datalib->getChildList(srcpath);
	std::vector<std::string>::iterator ite = std::find(srcequiplist.begin(), srcequiplist.end(),id);
	if(ite == srcequiplist.end())
	{
		datalib->setData(distpath, std::string("none"), true);
		return false;
	}
	
	std::string mid;
	applyModifer(path, srcpath + std::string("/") + id + std::string("/AttrModifer"), mid);

	std::string scrptpath;
	datalib->getData(srcpath + std::string("/") + id + std::string("/Script"),scrptpath);

	//LuaSystem::getSingleton().ExecuteFunction(scrptpath ,"OnEquip",distpath + std::string("/ScriptContext"));
	datalib->setData(distpath, id, true);
	datalib->setData(distpath + std::string("/Modifierid"), mid, true);


	return true;
}
bool AVGSquadManager::learnSkill(std::string path,std::string id)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	enumtype skilltype;
	bool re = datalib->getData(std::string("StaticData/SkillData/")+ id+ std::string("/Type"),skilltype);
	if(!re)
		return false;
	datalib->setData(path + std::string("/SkillTable/")+ id, 0);
	if(skilltype == SKILLTARGETTYPE_PASSIVE)
	{
		std::string skillcontext = path + std::string("/SkillTable/")+ id + std::string("/ScriptContext");
		std::string skillscript;
		datalib->getData(std::string("StaticData/SkillData/")+ id+ std::string("/Script"),skillscript);
		datalib->setData(skillcontext+ std::string("/skillcasterpath"),path);
		LuaSystem::getSingleton().executeFunction(skillscript ,"onlearn",skillcontext);
	}
	return true;
}
bool AVGSquadManager::applyModifer(std::string path, std::string modifierpath, std::string &modifierid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	path = path + std::string("/ModifierList");
	std::vector<std::string> modifierlist = datalib->getChildList(path);
	int x = 0;
	modifierid = std::string("m") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	while(ite != modifierlist.end())
	{
		x = x + 1;
		modifierid = std::string("m") + Ogre::StringConverter::toString(x);
		ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	}
	path = path + std::string("/") + modifierid;
	int tempint;
	float tempfloat;
	bool re = datalib->getData(modifierpath + std::string("/Type"),tempint);
	datalib->setData(path + std::string("/Type"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Attack"),tempfloat);
	datalib->setData(path + std::string("/Attack"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/RangedAttack"),tempfloat);
	datalib->setData(path + std::string("/RangedAttack"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Defence"),tempfloat);
	datalib->setData(path + std::string("/Defence"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Formation"),tempfloat);
	datalib->setData(path + std::string("/Formation"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Initiative"),tempfloat);
	datalib->setData(path + std::string("/Initiative"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/ActionPoint"),tempfloat);
	datalib->setData(path + std::string("/ActionPoint"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Detection"),tempfloat);
	datalib->setData(path + std::string("/Detection"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Covert"),tempfloat);
	datalib->setData(path + std::string("/Covert"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Injury"),tempfloat);
	datalib->setData(path + std::string("/Injury"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Conter"),tempfloat);
	datalib->setData(path + std::string("/Conter"), tempfloat, true);
	return true;
}
bool AVGSquadManager::applyModifer(std::string path, AttrModifier* modifier, std::string &modifierid)
{
	if(modifier == NULL)
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	path = path + std::string("/ModifierList");
	std::vector<std::string> modifierlist = datalib->getChildList(path);
	int x = 0;
	modifierid = std::string("m") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	while(ite != modifierlist.end())
	{
		x = x + 1;
		modifierid = std::string("m") + Ogre::StringConverter::toString(x);
		ite = std::find(modifierlist.begin(), modifierlist.end(),modifierid);
	}
	path = path + std::string("/") + modifierid;
	datalib->setData(path + std::string("/Type"), modifier->Type, true);
	datalib->setData(path + std::string("/Attack"), modifier->Attack, true);
	datalib->setData(path + std::string("/RangedAttack"), modifier->RangedAttack, true);
	datalib->setData(path + std::string("/Defence"), modifier->Defence, true);
	datalib->setData(path + std::string("/Formation"), modifier->Form, true);
	datalib->setData(path + std::string("/Initiative"), modifier->Initiative, true);
	datalib->setData(path + std::string("/ActionPoint"), modifier->ActionPoint, true);
	datalib->setData(path + std::string("/Detection"), modifier->Detection, true);
	datalib->setData(path + std::string("/Covert"), modifier->Covert, true);
	datalib->setData(path + std::string("/Injury"), modifier->Toughness, true);
	datalib->setData(path + std::string("/Conter"), modifier->Conter, true);
	return true;
}

void AVGSquadManager::removeModifier(std::string path,std::string modifierid)
{
	std::string particlepath = path + std::string("/ModifierList/") + modifierid;
	DataLibrary::getSingleton().delNode(particlepath);
}

bool AVGSquadManager::applyEffect(std::string path, std::string id, std::string &effectid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	//判断是否存在该效果
	std::string effectsrcpath = std::string("StaticData/EffectData/") + id;
	int test;
	if(!datalib->getData(effectsrcpath + std::string("/Type"),test,true))
		return false;
	datalib->getData(effectsrcpath + std::string("/Script"),effectsrcpath);
	//生成效果路径
	std::string effectpath = path + std::string("/EffectList");
	std::vector<std::string> effectlist = datalib->getChildList(effectpath);
	std::vector<std::string>::iterator ite;
	std::string oldeffectid;
	for(ite = effectlist.begin(); ite != effectlist.end(); ite++)
	{
		datalib->getData(str(boost::format("%1%/%2%")%effectpath%(*ite)),oldeffectid);
		if(oldeffectid == id)
			removeEffect(path,(*ite));
	}
	int x = 0;
	effectid = std::string("e") + Ogre::StringConverter::toString(x);
	ite = std::find(effectlist.begin(), effectlist.end(),effectid);
	while(ite != effectlist.end())
	{
		x = x + 1;
		effectid = std::string("e") + Ogre::StringConverter::toString(x);
		ite = std::find(effectlist.begin(), effectlist.end(),effectid);
	}
	effectpath = effectpath + std::string("/") + effectid;
	//运行效果脚本
	datalib->setData(effectpath,id);
	std::string contextpath = effectpath + std::string("/ScriptContext");
	datalib->setData(contextpath+ std::string("/affectsquadpath"),path);
	datalib->setData(contextpath+ std::string("/effectid"),effectid);
	LuaSystem::getSingleton().executeFunction(effectsrcpath ,"onaffect",contextpath);
	return true;
}

void AVGSquadManager::removeEffect(std::string path,std::string effectid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string effectpath = path + std::string("/EffectList/") + effectid;
	std::string effect;
	bool re = datalib->getData(effectpath,effect);
	if(!re)
		return;
	std::string effectsrcpath = std::string("StaticData/EffectData/") + effect;
	datalib->getData(effectsrcpath + std::string("/Script"),effectsrcpath);
	std::string contextpath = effectpath + std::string("/ScriptContext");
	LuaSystem::getSingleton().executeFunction(effectsrcpath ,"onremove",contextpath);
	datalib->delNode(effectpath);
}


bool AVGSquadManager::getSquadAttr(std::string path, enumtype attrtype, enumtype calctype, float &val)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> modifierlist = datalib->getChildList(path + std::string("/ModifierList"));
	if(modifierlist.size() == 0)
		return false;
	if(attrtype == ATTR_RANGEDDEFENCE )
		return false;
	float base = 0.0f;
	float mbouse = 0.0f;
	float mbane = 0.0f;
	float resist = 0.0f;
	float cbouse = 0.0f;
	float cbane = 0.0f;
	std::vector<std::string>::iterator ite;
	for(ite = modifierlist.begin(); ite != modifierlist.end(); ite++)
	{
		AttrModifierType type;
		float attrval;
		std::string datapath = path + std::string("/ModifierList/") + (*ite);
		bool re = datalib->getData(datapath + std::string("/Type"), type);
		switch(attrtype)
		{
		case ATTR_ATTACK:
			re = datalib->getData(datapath + std::string("/Attack"), attrval);
			break;
		case ATTR_RANGEDATTACK:
			re = datalib->getData(datapath + std::string("/RangedAttack"), attrval);
			break;
		case ATTR_DEFENCE:
			re = datalib->getData(datapath + std::string("/Defence"), attrval);
			break;
		case ATTR_FORM:
			re = datalib->getData(datapath + std::string("/Formation"), attrval);
			break;
		case ATTR_INITIATIVE:
			re = datalib->getData(datapath + std::string("/Initiative"), attrval);
			break;
		case ATTR_ACTIONPOINT:
			re = datalib->getData(datapath + std::string("/ActionPoint"), attrval);
			break;
		case ATTR_DETECTION:
			re = datalib->getData(datapath + std::string("/Detection"), attrval);
			break;
		case ATTR_COVERT:
			re = datalib->getData(datapath + std::string("/Covert"), attrval);
			break;
		case ATTR_TOUGHNESS:
			re = datalib->getData(datapath + std::string("/Injury"), attrval);
			break;
		case ATTR_CONTER:
			re = datalib->getData(datapath + std::string("/Conter"), attrval);
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
		val = base + bouse;
		break;
	case ATTRCALC_ONLYBASE:
		val = base;
		break;
	case ATTRCALC_ONLYBONUS:
		val = bouse;
		break;
	case ATTRCALC_RESISTLEFT:
		val = resist - bane;
		break;
	}
	return true;
}

bool AVGSquadManager::applyParticle(std::string path,UnitType unittype, std::string particle, std::string &particleid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string particlepath = path + std::string("/ParticleList");
	std::vector<std::string> particlelist = datalib->getChildList(path);
	int x = 0;
	particleid = std::string("p") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(particlelist.begin(), particlelist.end(),particleid);
	while(ite != particlelist.end())
	{
		x = x + 1;
		particleid = std::string("m") + Ogre::StringConverter::toString(x);
		ite = std::find(particlelist.begin(), particlelist.end(),particleid);
	}
	path = particlepath + std::string("/") + particleid;
	datalib->setData(path + std::string("/UnitType"), unittype, true);
	datalib->setData(path + std::string("/Particle"), particle, true);
	return true;
}
void AVGSquadManager::removeParticle(std::string path,std::string particleid)
{
	std::string particlepath = path + std::string("/ParticleList/") + particleid;
	DataLibrary::getSingleton().delNode(particlepath);
}

bool AVGSquadManager::addTrigger(std::string path,std::string trigertype, std::string file ,std::string func, std::string context, std::string &triggerid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int newid = 0;
	int test;
	while(datalib->getData(str(boost::format("%1%/Trigger/T%2%")%path%newid),test,true))
		newid++;
	datalib->setData(str(boost::format("%1%/Trigger/T%2%")%path%newid),0);
	datalib->setData(str(boost::format("%1%/Trigger/T%2%/type")%path%newid),trigertype);
	datalib->setData(str(boost::format("%1%/Trigger/T%2%/file")%path%newid),file);
	datalib->setData(str(boost::format("%1%/Trigger/T%2%/func")%path%newid),func);
	datalib->setData(str(boost::format("%1%/Trigger/T%2%/context")%path%newid),context);
	triggerid =  std::string("T") + Ogre::StringConverter::toString(newid);
	return true;
}
void AVGSquadManager::removeTrigger(std::string path,std::string triggerid)
{
	std::string particlepath = path + std::string("/Trigger/") + triggerid;
	DataLibrary::getSingleton().delNode(particlepath);
}
void AVGSquadManager::activeTrigger(std::string path,std::string triggerid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int test;
	if(datalib->getData(str(boost::format("%1%/Trigger/%2%")%path%triggerid),test,true))
	{
		datalib->setData(str(boost::format("%1%/Trigger/%2%")%path%triggerid),1);
	}
}
void AVGSquadManager::disableTrigger(std::string path,std::string triggerid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int test;
	if(datalib->getData(str(boost::format("%1%/Trigger/%2%")%path%triggerid),test,true))
	{
		datalib->setData(str(boost::format("%1%/Trigger/%2%")%path%triggerid),0);
	}
}

bool AVGSquadManager::(std::string squadid, std::string suqadtypeid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string srcpath = "StaticData/SquadData";
	std::vector<std::string> squadlist = datalib->getChildList(srcpath);
	std::vector<std::string>::iterator ite = std::find(squadlist.begin(), squadlist.end(),suqadtypeid);
	if(ite == squadlist.end())
		return false;
	srcpath = srcpath + std::string("/") + suqadtypeid;
	std::string path = "GameData/StoryData/SquadData";
	squadlist = datalib->getChildList(path);
	ite = std::find(squadlist.begin(), squadlist.end(),squadid);
	if(ite != squadlist.end())
		return false;
	path = path + std::string("/") + squadid;
	datalib->copyNode(srcpath, path, true);
	return true;
}

void AVGSquadManager::dumpSquad(Squad* squad)
{
	
}