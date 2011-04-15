#include "AVGSquadManager.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "LuaSystem.h"

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
	re = datalib->getData(datasrcpath + std::string("/UnitMaxNumber"),tempint);
	datalib->setData(datadistpath + std::string("/UnitMaxNumber"), tempint, true);
	datalib->setData(datadistpath + std::string("/UnitNumber"), tempint, true);
	
	//×°±¸
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

	return true;
}

bool AVGSquadManager::equipEquipment(std::string path, EquipmentType type, std::string id)
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
	applyModifer(path + std::string("/ModifierList"), srcpath + std::string("/") + id + std::string("/AttrModifer"), mid);

	std::string scrptpath;
	datalib->getData(srcpath + std::string("/") + id + std::string("/Script"),scrptpath);

	//LuaSystem::getSingleton().ExecuteFunction(scrptpath ,"OnEquip",distpath + std::string("/ScriptContext"));
	datalib->setData(distpath, id, true);
	datalib->setData(distpath + std::string("/Modifierid"), mid, true);


	return true;
}
bool AVGSquadManager::learnSkill(std::string path,std::string id)
{
	return true;
}
bool AVGSquadManager::applyModifer(std::string path, std::string modifierpath, std::string &modifierid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
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
	re = datalib->getData(modifierpath + std::string("/Attack"),tempint);
	datalib->setData(path + std::string("/Attack"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/RangedAttack"),tempint);
	datalib->setData(path + std::string("/RangedAttack"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Defence"),tempint);
	datalib->setData(path + std::string("/Defence"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Formation"),tempfloat);
	datalib->setData(path + std::string("/Formation"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Initiatice"),tempint);
	datalib->setData(path + std::string("/Initiatice"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/ActionPoint"),tempint);
	datalib->setData(path + std::string("/ActionPoint"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Detection"),tempint);
	datalib->setData(path + std::string("/Detection"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Covert"),tempint);
	datalib->setData(path + std::string("/Covert"), tempint, true);
	re = datalib->getData(modifierpath + std::string("/Injury"),tempfloat);
	datalib->setData(path + std::string("/Injury"), tempfloat, true);
	re = datalib->getData(modifierpath + std::string("/Conter"),tempfloat);
	datalib->setData(path + std::string("/Conter"), tempfloat, true);
	return true;
}
bool AVGSquadManager::applyModifer(std::string path, AttrModifier* modifier, std::string &modifierid)
{
	return true;
}
bool AVGSquadManager::applyEffect(std::string path, std::string id)
{
	return true;
}