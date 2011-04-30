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
				int type;
				Formation f;
				datalib->getData(datapath + std::string("/Type"), type );
				if(type == 1)
					f = Line;
				else
					f = Loose;
				datalib->setData(datapath +std::string("/TeamId"), std::string("Team1"), true );
				datalib->setData(datapath +std::string("/Grapid"),mCurid, true);
				datalib->setData(datapath +std::string("/CreateType"), StroySquad, true );
				datalib->setData(datapath +std::string("/Direction"), North, true );
				datalib->setData(datapath +std::string("/Formation"), f, true );
				datalib->setData(datapath +std::string("/ActionPoint"), 0.0f, true );
				BattleSquad* battlesquad = new BattleSquad((*ite),mCurid,-1,0); 
				suqadgrapmanager->createSquad((*ite), datapath, mCurid, -1, 0,North,Line,battlesquad->getUnitGrapNum());
				mDeployList.push_back(battlesquad);
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
			datalib->getData(datapath + "/GridX",x);
			datalib->getData(datapath + "/GridY",y);
			datalib->getData(datapath + "/Direction",d);
			datalib->getData(datapath + "/Formation",f);
			BattleSquad* battlesquad =  new BattleSquad((*ite),mCurid,x,y); 
			suqadgrapmanager->createSquad((*ite), datapath, mCurid,x,y,d,f, battlesquad->getUnitGrapNum());
			datalib->setData(datapath +std::string("/Grapid"),mCurid);
			mSquadList.push_back(battlesquad);
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