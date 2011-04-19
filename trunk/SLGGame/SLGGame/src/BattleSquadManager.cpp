#include "BattleSquadManager.h"

#include "AVGSquadManager.h"
#include "SquadGrapManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"

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
		childlist = datalib->getChildList(std::string("GameData/StoryData/SquadData/EnableSquad"));
		if(childlist.size()>0)
		{
			std::vector<std::string>::iterator ite;
			for(ite = childlist.begin(); ite != childlist.end(); ite++)
			{
				std::string datapath = std::string("GameData/BattleData/SquadList/") + (*ite);
				datalib->copyNode(std::string("GameData/StoryData/SquadData/EnableSquad/") + (*ite),datapath, true);
				datalib->setData(datapath +std::string("/TeamId"), std::string("Team1"), true );
				suqadgrapmanager->createSquad((*ite), datapath, mCurid, -1, 0,North,Line);
				datalib->setData(datapath +std::string("/Grapid"),mCurid, true);
				datalib->setData(datapath +std::string("/CreateType"), StroySquad, true );
				datalib->setData(datapath +std::string("/Direction"), North, true );
				datalib->setData(datapath +std::string("/Formation"), Line, true );
				mDeployList.push_back(new BattleSquad((*ite),mCurid,-1,0));
				mCurid ++;
			}
		}
	}
	creatSquadGrapAtPath(std::string("GameData/BattleData/SquadList"));
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
			Direction d;
			Formation f;
			int unitnum;
			datalib->getData(datapath + "/GridX",x);
			datalib->getData(datapath + "/GridY",y);
			datalib->getData(datapath + "/Direction",d);
			datalib->getData(datapath + "/Formation",f);
			datalib->getData(datapath + "/UnitNumber",unitnum);
			suqadgrapmanager->createSquad((*ite), datapath, mCurid,x,y,d,f);
			datalib->setData(datapath +std::string("/Grapid"),mCurid);
			mSquadList.push_back(new BattleSquad((*ite),mCurid,x,y));
			mCurid ++;
		}
	}
}

void BattleSquadManager::deployConfirm()
{
	while(mDeployList.size() > 0)
	{
		BattleSquad* suqad = mDeployList.back();
		mDeployList.pop_back();
		mSquadList.push_back(suqad);
	}
}

bool  BattleSquadManager::allDeployed()
{
	BattleSquadIte ite;
	for(ite = mDeployList.begin(); ite != mDeployList.end(); ite++)
	{
		int x;
		(*ite)->getCrood(&x, NULL);
		if(x < 0)
			return false;
	}
	return true;
}