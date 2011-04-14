#include "BattleSquadManager.h"

#include "AVGSquadManager.h"
#include "SquadGrapManager.h"

#include "DataLibrary.h"

BattleSquadManager::BattleSquadManager()
{
	mCurid = 0;
}
BattleSquadManager::~BattleSquadManager()
{

}

void BattleSquadManager::initBattleSquad(bool loadfrommap)
{
	DataLibrary* datalib =DataLibrary::getSingletonPtr();
	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();
	AVGSquadManager* avgsquadmanager = AVGSquadManager::getSingletonPtr();
	if(loadfrommap)
	{
		std::vector<std::string> childlist;
		childlist = datalib->getChildList(std::string("GameData/GameData/StoryData/SquadData/EnableSquad"));
		if(childlist.size()>0)
		{
			std::vector<std::string>::iterator ite;
			for(ite = childlist.begin(); ite != childlist.end(); ite++)
			{
				std::string datapath = std::string("GameData/GameData/BattleData/Team/Team1/SquadList/") + (*ite);
				datalib->copyNode(std::string("GameData/GameData/StoryData/SquadData/EnableSquad/") + (*ite),datapath, true);
				suqadgrapmanager->createSquad((*ite), datapath, mCurid, -1, 0,SquadGrapManager::North,SquadGrapManager::Line);
				datalib->setData(datapath +std::string("/Grapid"),mCurid);
				mCurid ++;
			}
		}
	}
	creatSquadGrapAtPath(std::string("GameData/GameData/BattleData/Team/Team1/TempSquadList"));
	creatSquadGrapAtPath(std::string("GameData/GameData/BattleData/Team/Team2/SquadList"));
	creatSquadGrapAtPath(std::string("GameData/GameData/BattleData/Team/Team3/SquadList"));
	creatSquadGrapAtPath(std::string("GameData/GameData/BattleData/Team/Team4/SquadList"));
}
void BattleSquadManager::creatSquadGrapAtPath(std::string path)
{
	DataLibrary* datalib =DataLibrary::getSingletonPtr();
	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();
	AVGSquadManager* avgsquadmanager = AVGSquadManager::getSingletonPtr();
	std::vector<std::string> childlist;
	childlist = datalib->getChildList(path);
	if(childlist.size()>0)
	{
		std::vector<std::string>::iterator ite;
		for(ite = childlist.begin(); ite != childlist.end(); ite++)
		{
			std::string datapath = path + std::string("/") + (*ite);
			int x,y;
			datalib->getData(datapath + "/GridX",x);
			datalib->getData(datapath + "/GridY",y);
			suqadgrapmanager->createSquad((*ite), datapath, mCurid,x,y,SquadGrapManager::North,SquadGrapManager::Line);
			datalib->setData(datapath +std::string("/Grapid"),mCurid);
			mCurid ++;
		}
	}
}