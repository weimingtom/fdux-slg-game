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

void AVGSquadManager::dumpSquad(Squad* squad)
{
	
}