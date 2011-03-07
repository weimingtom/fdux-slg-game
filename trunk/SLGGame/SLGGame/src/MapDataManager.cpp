#include "MapDataManager.h"

#include "DataLibrary.h"
#include <ticpp.h>

MapDataManager::MapDataManager()
{

}

MapDataManager::~MapDataManager()
{

}

bool MapDataManager::loadMap(std::string mapname)
{
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
						if(str[tempindex * 2] == 'h')
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
	return true;
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