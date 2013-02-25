#include "AVGSquadManager.h"

#include "DataLibrary.h"
#include "Squad.h"

#include "boost/format.hpp"

AVGSquadManager::AVGSquadManager()
{

}
AVGSquadManager::~AVGSquadManager()
{

}

bool AVGSquadManager::addNewSquad(std::string squadid, std::string suqadtypeid)
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

void AVGSquadManager::dumpSquad(std::string squadid, Squad* squad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string path = "GameData/StoryData/SquadData";
	std::vector<std::string> squadlist = datalib->getChildList(path);
	std::vector<std::string>::iterator ite = std::find(squadlist.begin(), squadlist.end(),squadid);
	if(ite == squadlist.end())
		return;
	path = str(boost::format("GameData/StoryData/SquadData/%1%/")%squadid);
	datalib->setData(path + "LeaderId", squad->getLeaderId());
	datalib->setData(path + "RetainerId", squad->getRetainerId());
	datalib->setData(path + "SoilderId", squad->getSoilderId());
	datalib->setData(path + "HorseId", squad->getHorseId());
	datalib->setData(path + "PweaponId", squad->getPweaponId());
	datalib->setData(path + "SweaponId", squad->getSweaponId());
	datalib->setData(path + "ShieldId", squad->getShieldId());
	datalib->setData(path + "ArmorId", squad->getArmorId());
	datalib->setData(path + "Level", squad->getLevel());
	datalib->setData(path + "Exp", squad->getExp());
	int unitnum = squad->getUnitNum();
	if(unitnum == 0)
		unitnum = 1;
	datalib->setData(path + "UnitNum", unitnum);
	datalib->setData(path + "SkillPointAction", squad->getSkillPointAction());
	datalib->setData(path + "SkillPointPassive", squad->getSkillPointPassive());
	datalib->setData(path + "SkillPointEquip", squad->getSkillPointEquip());
	
	//复制技能数据
	datalib->delNode(path + "SkillTable");
	std::map<std::string, int> skilltable = squad->getSkillTable();
	std::map<std::string, int>::iterator ite1;
	for(ite1 = skilltable.begin(); ite1 != skilltable.end(); ite1++)
	{
		datalib->setData(path + "SkillTable/" + ite1->first, ite1->second );
	}
}