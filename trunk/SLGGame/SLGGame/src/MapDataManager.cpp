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
	if(x < 0 || x >= mMapSize || y < 0 || y >= mMapSize)
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int maxpassable;
	int minpassable;
	int passable;
	int id;
	std::string path = std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	bool re = datalib->getData(path + std::string("/GroundType"), id);
	std::string ground;
	datalib->getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%id),ground);
	re = datalib->getData(str(boost::format("StaticData/GroundData/%1%/GroundModifier/Passable")%ground), passable);
	maxpassable = passable;
	minpassable = passable;
	re = datalib->getData(path + std::string("/TerrainType"), id);
	re = datalib->getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(id) + std::string("/GroundModifier/Passable"), passable);
	maxpassable = (maxpassable > passable)? maxpassable:passable;
	minpassable = (minpassable < passable)? minpassable:passable;
	std::string groundobj;
	re = datalib->getData(path + std::string("/MapObjType"), groundobj,true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/GroundModifier/Passable")%groundobj);
		re = datalib->getData(path, passable);
		maxpassable = (maxpassable > passable)? maxpassable:passable;
		minpassable = (minpassable < passable)? minpassable:passable;
	}

	//额外修正

	//小队阻挡
	/*
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
	*/

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
	std::string ground;
	DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%g),ground);
	bool re = DataLibrary::getSingleton().getData(str(boost::format("StaticData/GroundData/%1%/GroundModifier/InfAp")%ground), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/InfAp"), terraincost);
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string path =  std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	std::string groundobj;
	float groundobjcost = 0.0f;
	re = datalib->getData(path + std::string("/MapObjType"), groundobj, true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/GroundModifier/InfAp")%groundobj);
		re = datalib->getData(path, groundobjcost);
	}
	return groundcost + terraincost + groundobjcost;
}
float MapDataManager::getCavApCost(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	std::string ground;
	DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%g),ground);
	bool re = DataLibrary::getSingleton().getData(str(boost::format("StaticData/GroundData/%1%/GroundModifier/CavAp")%ground), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/CavAp"), terraincost);
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string path =  std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	std::string groundobj;
	float groundobjcost = 0.0f;
	re = datalib->getData(path + std::string("/MapObjType"), groundobj, true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/GroundModifier/CavAp")%groundobj);
		re = datalib->getData(path, groundobjcost);
	}
	return groundcost + terraincost + groundobjcost;
}
float MapDataManager::getDefModify(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	std::string ground;
	DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%g),ground);
	bool re = DataLibrary::getSingleton().getData(str(boost::format("StaticData/GroundData/%1%/GroundModifier/Defence")%ground), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/Defence"), terraincost);
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string path =  std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	std::string groundobj;
	float groundobjcost = 0.0f;
	re = datalib->getData(path + std::string("/MapObjType"), groundobj,true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/GroundModifier/Defence")%groundobj);
		re = datalib->getData(path, groundobjcost);
	}
	return groundcost + terraincost + groundobjcost;
}

float MapDataManager::getCovert(int x, int y, int team)
{
	TerrainType t = getTerrainType(x,y);
	GroundType g = getGroundType(x,y);
	float terraincost;
	float groundcost;
	std::string ground;
	DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%g),ground);
	bool re = DataLibrary::getSingleton().getData(str(boost::format("StaticData/GroundData/%1%/GroundModifier/Covert")%ground), groundcost);
	re = DataLibrary::getSingleton().getData(std::string("StaticData/TerrainData/Terrain") + Ogre::StringConverter::toString(t) + std::string("/GroundModifier/Covert"), terraincost);
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string path =  std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(x + y * mMapSize);
	std::string groundobj;
	float groundobjcost = 0.0f;
	re = datalib->getData(path + std::string("/MapObjType"), groundobj, true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/GroundModifier/Covert")%groundobj);
		re = datalib->getData(path, groundobjcost);
	}
	return groundcost + terraincost + groundobjcost;
}