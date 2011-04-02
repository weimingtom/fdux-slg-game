#include "MapDataManager.h"

#include "DataLibrary.h"
#include "Terrain.h"
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
	datalibrary->setData("GameData/BattleData/MapName", str);
	//载入地图地形信息
	element = doc->FirstChildElement("MapSize");
	element->GetText(&mMapSize);
	datalibrary->setData("GameData/BattleData/MapSize", mMapSize);
	element = doc->FirstChildElement("MapData");
	element->GetText(&str);
	for(int y = 0; y < mMapSize; y++)
	{
		for(int x = 0; x < mMapSize; x++)
		{
			int index = (y * mMapSize + x);
			char datapathtemp[50];
			sprintf_s(datapathtemp, 50, "GameData/BattleData/Map/%d", index);
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
		datapath = std::string("GameData/BattleData/MapObjectModleInfo/") + objname;
		int objx,objy;
		std::string meshname,objtype;
		child->GetAttribute("GridX",&objx);
		child->GetAttribute("GridY",&objy);
		child->GetAttribute("Mesh",&meshname);
		child->GetAttribute("Type",&objtype);
		datalibrary->setData(datapath + "/GridX", objx);
		datalibrary->setData(datapath + "/GridY", objy);
		datalibrary->setData(datapath + "/Mesh", meshname);
	}
	element = doc->FirstChildElement("MapEffect");
	for(child = child.begin(element); child != child.end(); child++)
	{
		std::string particlename;
		std::string datapath;
		child->GetValue(&particlename);
		datapath = std::string("GameData/BattleData/MapParticleInfo/") + particlename;
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
	
	return true;
}


void MapDataManager::loadMapObj()
{
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	Terrain* terrain = Terrain::getSingletonPtr();
	std::string datapath("GameData/BattleData/MapObjectModleInfo");
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
			datalibrary->setData(datapath + childlist[n] + std::string("/ObjIndex"),index);
		}
	}
	datapath = "GameData/BattleData/MapParticleInfo";
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
			datalibrary->setData(datapath + childlist[n] + std::string("/ParticleIndex"),index);
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
	char datapathtemp[50];
	sprintf_s(datapathtemp, 50, "GameData/BattleData/Map/%d/GroundType", index);
	DataLibrary::getSingleton().getData(datapathtemp,index);
	return index;
}
TerrainType MapDataManager::getTerrainType(int x, int y)
{
	x = (x < 0)?0:x;
	x = (x > mMapSize -1)?mMapSize -1:x;
	y = (y < 0)?0:y;
	y = (y > mMapSize -1)?mMapSize -1:y;
	int index = y * mMapSize + x;
	char datapathtemp[50];
	sprintf_s(datapathtemp, 50, "GameData/BattleData/Map/%d/TerrainType", index);
	DataLibrary::getSingleton().getData(datapathtemp,index);
	return index;
}