#include "BattleSquadManager.h"

#include <algorithm>
#include <boost/format.hpp>

#include "MapDataManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"
#include "CommonFunction.h"

#include "LuaSystem.h"
#include "StringTable.h"

#include "Terrain.h"

#include "TriggerManager.h"

BattleSquadManager::BattleSquadManager()
{

}
BattleSquadManager::~BattleSquadManager()
{

}

void BattleSquadManager::clear()
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		delete ite->second;
	}
	mSquadList.clear();
}


bool  BattleSquadManager::allDeployed()
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getGridX() < 0)
			return false;
	}
	return true;
}

BattleSquad* BattleSquadManager::getBattleSquad(std::string id)
{
	BattleSquadIte ite = mSquadList.find(id);
	if(ite == mSquadList.end())
		return NULL;
	return ite->second;
}

BattleSquad* BattleSquadManager::getBattleSquadAt(int x, int y, bool visibleonly)
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getGridX() != x)
			continue;
		if(ite->second->getGridY() != y)
			continue;
		if(visibleonly)
		{
			if(ite->second->getViewbyPlayer())
				return ite->second;
		}
		else
			return ite->second;
	}
	return NULL;
}

void BattleSquadManager::moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype)
{

}

bool BattleSquadManager::useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid)
{
	if(attacksquad == NULL || targetsquad == NULL )
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid)
{
	if(attacksquad == NULL)
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::dealMeleeDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk, int fluctuate)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}