#include "MapDataManager.h"

#include "DataLibrary.h"
#include "Terrain.h"
#include "StringTable.h"
#include "AVGSquadManager.h"
#include <ticpp.h>

MapDataManager::MapDataManager()
{

}

MapDataManager::~MapDataManager()
{

}

bool MapDataManager::loadMapFormFile(std::string mapname)
{
	Terrain* terrain = Terrain::getSingletonPtr();
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	std::string path = ".\\..\\Media\\Map\\" + mapname;
	ticpp::Document *doc = new ticpp::Document();
	doc->LoadFile(path,TIXML_ENCODING_UTF8);
	std::string str;
	//载入地图名字
	ticpp::Element *element = doc->FirstChildElement("MapName");
	element->GetText(&str);
	datalibrary->setData("GameData/BattleData/MapData/MapName", StringTable::getSingleton().getString(str));
	//载入地图地形信息
	element = doc->FirstChildElement("MapSize");
	element->GetText(&mMapSize);
	datalibrary->setData("GameData/BattleData/MapData/MapSize", mMapSize);
	element = doc->FirstChildElement("MapData");
	element->GetText(&str);
	for(int y = 0; y < mMapSize; y++)
	{
		for(int x = 0; x < mMapSize; x++)
		{
			int index = (y * mMapSize + x);
			char datapathtemp[64];
			sprintf_s(datapathtemp, 64, "GameData/BattleData/MapData/Map/M%d", index);
			std::string datapath = datapathtemp;
			if(str[index * 2] == 'l')
			{
				bool iscliff = false;
				for(int i = y - 1; i < y + 2; i ++)
				{
					for(int j =  x - 1; j < x + 2; j++)
					{
						int u = (i<0)?0:i;
						u = (u >= mMapSize)?mMapSize-1:u;
						int v = (j<0)?0:j;
						v = (v >= mMapSize)?mMapSize-1:v;
						int tempindex = u * mMapSize + v;
						if(str[tempindex * 2] == 'h' )
						{	
							iscliff = true;
						}
					}
				}
				if(iscliff)
					datalibrary->setData(datapath + "/TerrainType", Cliff);
				else
					datalibrary->setData(datapath + "/TerrainType", LowGround);
			}
			else if(str[index * 2] == 'w')
			{
				datalibrary->setData(datapath + "/TerrainType", Water);
			}
			else if(str[index * 2] == 'h')
			{
				datalibrary->setData(datapath + "/TerrainType", HighGround);
			}
			else if(str[index * 2] == 'r')
			{
				datalibrary->setData(datapath + "/TerrainType", Ramp);
			}

			if(str[index * 2+1] == 'g')
			{
				datalibrary->setData(datapath + "/GroundType", GreenLand);
			}
			else if(str[index * 2+1] == 'd')
			{
				datalibrary->setData(datapath + "/GroundType", Desert);
			}
			else if(str[index * 2+1] == 'w')
			{
				datalibrary->setData(datapath + "/GroundType", Swamp);
			}
			else if(str[index * 2+1] == 's')
			{
				datalibrary->setData(datapath + "/GroundType", Snow);
			}
		}
	}
	element = doc->FirstChildElement("MapObject");
	ticpp::Iterator<ticpp::Element> child;
	for(child = child.begin(element); child != child.end(); child++)
	{
		std::string objname;
		std::string datapath;
		child->GetValue(&objname);
		datapath = std::string("GameData/BattleData/MapData/MapObjModleInfo/") + objname;
		int objx,objy;
		std::string meshname,objtype;
		child->GetAttribute("GridX",&objx);
		child->GetAttribute("GridY",&objy);
		child->GetAttribute("Mesh",&meshname);
		child->GetAttribute("Type",&objtype);
		datalibrary->setData(datapath + "/GridX", objx);
		datalibrary->setData(datapath + "/GridY", objy);
		datalibrary->setData(datapath + "/Mesh", meshname);
		//物品类型脚本
		datapath = std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(objy * mMapSize + objx) + std::string("/MapObjType");
		datalibrary->setData(datapath, objtype);
		datalibrary->setData(datapath + "/MapObjModuleId", objname);
		//执行脚本
	}
	element = doc->FirstChildElement("MapEffect");
	for(child = child.begin(element); child != child.end(); child++)
	{
		std::string particlename;
		std::string datapath;
		child->GetValue(&particlename);
		datapath = std::string("GameData/BattleData/MapData/MapParticleInfo/") + particlename;
		int particlex,particley;
		std::string scriptname;
		child->GetAttribute("GridX",&particlex);
		child->GetAttribute("GridY",&particley);
		child->GetAttribute("Type",&scriptname);
		datalibrary->setData(datapath + "/GridX", particlex);
		datalibrary->setData(datapath + "/GridY", particley);
		datalibrary->setData(datapath + "/Script", scriptname);
	}
	
	terrain->createTerrain(this);

	//载入区域信息
	element = doc->FirstChildElement("MapArea");
	for(child = child.begin(element); child != child.end(); child++)
	{
		std::string areaname;
		std::string datapath;
		child->GetValue(&areaname);
		datapath = std::string("GameData/BattleData/MapData/Area/") + areaname;
		ticpp::Iterator<ticpp::Element> childchild;
		for(childchild = childchild.begin(child.Get()); childchild != childchild.end(); childchild++)
		{
			std::string coordname;
			childchild->GetValue(&coordname);
			int x;
			int y;
			childchild->GetAttribute("X",&x);
			childchild->GetAttribute("Y",&y);
			datalibrary->setData(datapath + std::string("/CoordList/") + coordname + std::string("/X"),x );
			datalibrary->setData(datapath + std::string("/CoordList/") + coordname + std::string("/Y"),y );
		}
	
	}
	//载入队伍信息
	element = doc->FirstChildElement("MapTeam");
	datalibrary->setData(std::string("GameData/BattleData/Team/Team1/FactionId"), std::string("player"));
	for(int n = 2; n < 5; n++)
	{
		std::string name = std::string("Team") + Ogre::StringConverter::toString(n);
		std::string factionid;
		ticpp::Element* subelement = element->FirstChildElement(name);
		subelement->GetAttribute("TeamFaction",&factionid);
		datalibrary->setData(std::string("GameData/BattleData/Team/")+ name+ "/FactionId", factionid);
		if(factionid != "none")
		{
			subelement->GetAttribute("TeamType",&factionid);
			datalibrary->setData(std::string("GameData/BattleData/Team/")+ name+ "/Relation", factionid);
		}
	}
	std::string playerfactionid;
	datalibrary->getData("GameData/StoryData/Faction",playerfactionid);
	datalibrary->setData("GameData/BattleData/Team/Team1/FactionId",playerfactionid);
	datalibrary->setData("GameData/BattleData/Team/Team1/Relation","player");
	
	//载入部队信息
	element = doc->FirstChildElement("MapSquad");
	for(child = child.begin(element); child != child.end(); child++)
	{
		std::string teamid;
		std::string datapath;
		child->GetValue(&teamid);
		datapath = std::string("GameData/BattleData/SquadList");
		ticpp::Iterator<ticpp::Element> childchild;
		for(childchild = childchild.begin(child.Get()); childchild != childchild.end(); childchild++)
		{
			std::string squadid;
			std::string squadtype;
			childchild->GetValue(&squadid);
			int x;
			int y;
			Direction d;
			int unitnum;
			Formation f;
			childchild->GetAttribute("Type",&squadtype);
			childchild->GetAttribute("GridX",&x);
			childchild->GetAttribute("GridY",&y);
			childchild->GetAttribute("UnitNum",&unitnum);
			childchild->GetAttribute("Direction",&d);
			childchild->GetAttribute("Formation",&f);
			AVGSquadManager::getSingleton().addSquad(squadid,squadtype, datapath);
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/GridX"), x, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/GridY"), y, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/UnitNum"), unitnum, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/Direction"), d, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/Formation"), f, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/TeamId"), teamid, true );
			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/CreateType"), MapSquad, true );
		}
	}
	//执行地图初始化脚本
	
	return true;
}


void MapDataManager::loadMapObj()
{
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	Terrain* terrain = Terrain::getSingletonPtr();
	std::string datapath("GameData/BattleData/MapData/MapObjModleInfo");
	std::vector<std::string> childlist;
	childlist = datalibrary->getChildList(datapath);
	if(childlist.size()>0)
	{
		for(int n = 0; n < childlist.size(); n++)
		{
			std::string meshname;
			int x,y;
			datalibrary->getData(datapath + std::string("/") + childlist[n] + std::string("/Mesh"),meshname);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridX"),x);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridY"),y);
			int index;
			index = terrain->createMapObj(x,y,meshname);
			datalibrary->setData(datapath + childlist[n] + std::string("/Index"),index);
		}
	}
	datapath = "GameData/BattleData/MapData/MapParticleInfo";
	childlist = datalibrary->getChildList(datapath);
	if(childlist.size()>0)
	{
		for(int n = 0; n < childlist.size(); n++)
		{
			std::string particlename;
			int x,y;
			datalibrary->getData(datapath + std::string("/") + childlist[n] + std::string("/Script"),particlename);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridX"),x);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridY"),y);
			int index;
			index = terrain->createMapParticle(x,y,particlename);
			datalibrary->setData(datapath + childlist[n] + std::string("/Index"),index);
		}
	}
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
	char datapathtemp[128];
	sprintf_s(datapathtemp, 128, "GameData/BattleData/MapData/Map/M%d/TerrainType", index);
	DataLibrary::getSingleton().getData(datapathtemp,terraintype);
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

	if(maxpassable == 2)
		return true;
	if(minpassable == 0)
		return false;
	return true;
}
int MapDataManager::getInfApCost(int x, int y, int team)
{
	return 0;
}
int MapDataManager::getCavApCost(int x, int y, int team)
{
	return 0;
}
int MapDataManager::getDefModify(int x, int y, int team)
{
	return 0;
}