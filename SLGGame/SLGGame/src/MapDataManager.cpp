#include "MapDataManager.h"

#include "DataLibrary.h"
#include "Terrain.h"
#include "AVGSquadManager.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "boost/format.hpp"
#include <ticpp.h>

MapDataManager::MapDataManager()
{

}

MapDataManager::~MapDataManager()
{

}

GroundType MapDataManager::getGroundType(int x, int y)
{
	x = (x < 0)?0:x;
	x = (x > mMapSize -1)?mMapSize -1:x;
	y = (y < 0)?0:y;
	y = (y > mMapSize -1)?mMapSize -1:y;
	int index = y * mMapSize + x;
	GroundType groundtype;
	char datapathtemp[128];
	sprintf_s(datapathtemp, 128, "GameData/BattleData/MapData/Map/M%d/GroundType", index);
	DataLibrary::getSingleton().getData(datapathtemp,groundtype);
	return groundtype;
}
TerrainType MapDataManager::getTerrainType(int x, int y)
{
	x = (x < 0)?0:x;
	x = (x > mMapSize -1)?mMapSize -1:x;
	y = (y < 0)?0:y;
	y = (y > mMapSize -1)?mMapSize -1:y;
	int index = y * mMapSize + x;
	TerrainType terraintype;
	std::string datapath=str(boost::format("GameData/BattleData/MapData/Map/M%1%/TerrainType")%index);
	DataLibrary::getSingleton().getData(datapath,terraintype);
	return terraintype;
}

bool MapDataManager::getPassable(int x, int y, int team)
{
	if(x < 0 || x > mMapSize || y < 0 || y > mMapSize)
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int maxpassable;
	int minpassable;
	int passable;
	int id;
	std::string path = std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	bool re = datalib->getData(path + std::string("/GroundType"), id);
	re = datalib->getData(std::string("StaticData/GroundData/Ground") + Ogre::StringConverter::toString(id) + std::string("/GroundModifier/Passable"), passable);
	maxpassable = passable;
	minpassable = passable;
	re = datalib->getData(path + std::string("/TerrainType"), id);
	re = datalib->getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(id) + std::string("/GroundModifier/Passable"), passable);
	maxpassable = (maxpassable > passable)? maxpassable:passable;
	minpassable = (minpassable < passable)? minpassable:passable;
	//额外修正

	//小队阻挡
	if(team != 0)
	{
		BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
		BattleSquadManager::BattleSquadIte ite;
		for(ite = battlesquadmanager->mSquadList.begin(); ite != battlesquadmanager->mSquadList.end(); ite++)
		{
			int xx,yy;
			(*ite)->getCrood(&xx,&yy);
			if(xx ==x && yy == y)
				return false;
		}
		for(ite = battlesquadmanager->mDeployList.begin(); ite != battlesquadmanager->mDeployList.end(); ite++)
		{
			int xx,yy;
			(*ite)->getCrood(&xx,&yy);
			if(xx ==x && yy == y)
				return false;
		}
	}

	if(maxpassable == 2)
		return true;
	if(minpassable == 0)
		return false;
	return true;
}
float MapDataManager::getInfApCost(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/GroundData/Ground") + Ogre::StringConverter::toString(g) + std::string("/GroundModifier/InfAp"), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/InfAp"), terraincost);
	return groundcost + terraincost;
}
float MapDataManager::getCavApCost(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/GroundData/Ground") + Ogre::StringConverter::toString(g) + std::string("/GroundModifier/CavAp"), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/CavAp"), terraincost);
	return groundcost + terraincost;
}
float MapDataManager::getDefModify(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/GroundData/Ground") + Ogre::StringConverter::toString(g) + std::string("/GroundModifier/Defence"), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/Defence"), terraincost);
	return groundcost + terraincost;
}

float MapDataManager::getCovert(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/GroundData/Ground") + Ogre::StringConverter::toString(g) + std::string("/GroundModifier/Covert"), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/Covert"), terraincost);
	return groundcost + terraincost;
}