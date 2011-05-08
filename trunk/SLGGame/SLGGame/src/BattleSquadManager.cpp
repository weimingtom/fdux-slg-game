#include "BattleSquadManager.h"

#include "AVGSquadManager.h"
#include "SquadGrapManager.h"
#include "MapDataManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"

BattleSquadManager::BattleSquadManager()
{
	mCurid = 0;
}
BattleSquadManager::~BattleSquadManager()
{

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

int BattleSquadManager::getTeamRelation(int team)
{
	std::string temppath,tempstr;
	temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(team) + std::string("/Relation");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	if(tempstr == "alliance")
		return 0;
	else if(tempstr == "player")
		return 0;
	else if(tempstr == "enemy1")
		return 1;
	else if(tempstr == "enemy2")
		return 2;
	else if(tempstr == "enemy3")
		return 3;
	return 0;
}

BattleSquad* BattleSquadManager::getBattleSquadAt(int x, int y, int team, bool visibleonly)
{
	BattleSquadManager::BattleSquadIte ite;
	int faction = getTeamRelation(team);
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		int xx,yy;
		(*ite)->getCrood(&xx,&yy);
		if(xx ==x && yy == y)
		{
			if(!visibleonly)
				return (*ite);
			if((*ite)->viewbyTeam(faction))
				return (*ite);
			return NULL;
		}
	}
	for(ite = mDeployList.begin(); ite != mDeployList.end(); ite++)
	{
		int xx,yy;
		(*ite)->getCrood(&xx,&yy);
		if(xx ==x && yy == y)
		{
			return (*ite);
		}
	}
	return NULL;
}

void BattleSquadManager::moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	for(stopedpoint = 0; stopedpoint * 2 < pointlist.size();stopedpoint++)
	{
		//移动条件判断
		int x = pointlist[stopedpoint*2];
		int y = pointlist[stopedpoint*2 + 1];
		int xx,yy;
		squad->getCrood(&xx, &yy);
		if( abs(xx -x) + abs(yy -y) != 1)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( !mapdata->getPassable(x,y, squad->getTeam()))
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( getBattleSquadAt(x,y,squad->getTeam(), false) != NULL)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( getBattleSquadAt(x,y,squad->getTeam(), true) != NULL)
		{
			eventtype |= MOVEEVENT_AMBUSH;
			//被埋伏效果
			return;
		}
		float apcost;
		float apleft = squad->getActionPoint();
		std::string horse;
		DataLibrary::getSingleton().getData(squad->getPath() + std::string("/HorseId"),horse);
		if(horse == "none")
			apcost = mapdata->getInfApCost(x,y,0);
		else
			apcost = mapdata->getCavApCost(x,y,0);
		if(apleft<apcost)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		//移动一步
		squad->setCrood(x,y);
		DataLibrary::getSingleton().setData(squad->getPath() + std::string("/ActionPoint"),apleft - apcost);
		if(x < xx)
			squad->setDirection(West);
		else if(x > xx)
			squad->setDirection(East);
		else if( y > yy)
			squad->setDirection(South);
		else
			squad->setDirection(North);
		//重新可视范围等


	}
}