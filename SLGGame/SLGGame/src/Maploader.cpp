#include "MapLoader.h"

#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "AVGSquadManager.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"

#include "MapDataManager.h"
#include "Terrain.h"

#include "StringTable.h"
#include "DataLibrary.h"
#include "LuaSystem.h"
#include "AudioSystem.h"
#include "boost/format.hpp"

#include "Area.h"

MapLoader::MapLoader()
{

}
MapLoader::~MapLoader()
{

}

bool MapLoader::loadMapFormFile(std::string mapname)
{
	int mapsize;
	Terrain* terrain = Terrain::getSingletonPtr();
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	std::string path = ".\\..\\Media\\Map\\" + mapname;

	//ticpp::Document *doc = new ticpp::Document();
	rapidxml::xml_document<> doc;
	//doc.LoadFile(path,TIXML_ENCODING_UTF8);
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(mapname, "Data", true);
	char* s=new char[stream->size()+1];
	stream->read(s,stream->size());
	s[stream->size()]='\0';
	doc.parse<0>(s);

	std::string str1;
	//载入地图名字，介绍和脚本名
	//ticpp::Element *element = doc.FirstChildElement("MapName");
	rapidxml::xml_node<> * element = doc.first_node("MapName");
	//element->GetText(&str1);
	str1 = element->value();
	datalibrary->setData("GameData/BattleData/MapData/MapName", StringTable::getSingleton().getString(str1));
	//delete element;

	//element = doc.FirstChildElement("MapScript");
	element = doc.first_node("MapScript");
	//element->GetText(&str1);
	str1 = element->value();
	datalibrary->setData("GameData/BattleData/MapData/MapScript", str1);
	//delete element;

	//element = doc.FirstChildElement("MapInfo");
	element = doc.first_node("MapInfo");
	//element->GetText(&str1);
	str1 = element->value();
	datalibrary->setData("GameData/BattleData/MapData/MapInfo",str1);
	//delete element;

	//element = doc.FirstChildElement("MapLoadBG");
	element = doc.first_node("MapLoadBG");
	//element->GetText(&str1);
	str1 = element->value();
	datalibrary->setData("GameData/BattleData/MapData/MapLoadBG",str1);
	//delete element;

	//载入地图地形信息
	//element = doc.FirstChildElement("MapSize");
	element = doc.first_node("MapSize");
	//element->GetText(&mapsize);
	mapsize = Ogre::StringConverter::parseUnsignedInt(element->value());
	MapDataManager::getSingleton().mMapSize = mapsize;
	datalibrary->setData("GameData/BattleData/MapData/MapSize", mapsize);
	//delete element;

	//element= doc.FirstChildElement("MapGround");
	element = doc.first_node("MapGround");
	//ticpp::Iterator<ticpp::Element> child;
	rapidxml::xml_node<> *child = element->first_node();
	std::string datapath;
	//for(child = child.begin(element); child != child.end(); child++)
	for(; child; child =child->next_sibling())
	{
		std::string layer,type,texture;
		//child->GetValue(&layer);
		layer = child->name();
		//child->GetAttribute("Type",&type);
		rapidxml::xml_attribute<> *attr = child->first_attribute("Type");
		type = attr->value();
		//child->GetAttribute("Texture",&texture);
		attr = child->first_attribute("Texture");
		texture = attr->value();
		datapath = str(boost::format("GameData/BattleData/MapData/Ground/%1%")%layer);
		datalibrary->setData(datapath, type);
		datapath = str(boost::format("GameData/BattleData/MapData/Ground/%1%Tex")%layer);
		datalibrary->setData(datapath, texture);
	}
	//delete element;

	//element = doc.FirstChildElement("MapData");
	element = doc.first_node("MapData");
	//element->GetText(&str1);
	str1 = element->value();
	for(int y = 0; y < mapsize; y++)
	{
		for(int x = 0; x < mapsize; x++)
		{
			int index = y * mapsize + x;
			char datapathtemp[64];
			sprintf_s(datapathtemp, 64, "GameData/BattleData/MapData/Map/M%d", MapDataManager::getSingleton().getGridId(x, y));
			std::string datapath = datapathtemp;
			if(str1[index * 2] == 'l')
			{
				bool iscliff = false;
				for(int i = y - 1; i < y + 2; i ++)
				{
					for(int j =  x - 1; j < x + 2; j++)
					{
						int u = (i<0)?0:i;
						u = (u >= mapsize)?mapsize-1:u;
						int v = (j<0)?0:j;
						v = (v >= mapsize)?mapsize-1:v;
						int tempindex = u * mapsize + v;
						if(str1[tempindex * 2] == 'h' )
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
			else if(str1[index * 2] == 'w')
			{
				datalibrary->setData(datapath + "/TerrainType", Water);
			}
			else if(str1[index * 2] == 'h')
			{
				datalibrary->setData(datapath + "/TerrainType", HighGround);
			}
			else if(str1[index * 2] == 'r')
			{
				datalibrary->setData(datapath + "/TerrainType", Ramp);
			}

			if(str1[index * 2+1] == 'g')
			{
				datalibrary->setData(datapath + "/GroundType", GreenLand);
			}
			else if(str1[index * 2+1] == 'd')
			{
				datalibrary->setData(datapath + "/GroundType", Desert);
			}
			else if(str1[index * 2+1] == 'w')
			{
				datalibrary->setData(datapath + "/GroundType", Swamp);
			}
			else if(str1[index * 2+1] == 's')
			{
				datalibrary->setData(datapath + "/GroundType", Snow);
			}
		}
	}
	//delete element;

	//element = doc.FirstChildElement("MapObject");
	element = doc.first_node("MapObject");
	//for(child = child.begin(element); child != child.end(); child++)
	for(child = element->first_node(); child; child =child->next_sibling())
	{
		std::string objname;
		//child->GetValue(&objname);
		objname = child->name();
		datapath = std::string("GameData/BattleData/MapData/MapObjModleInfo/") + objname;
		int objx,objy, objdir;
		std::string meshname,objtype;
		//child->GetAttribute("GridX",&objx);
		rapidxml::xml_attribute<> *attr = child->first_attribute("GridX");
		objx = Ogre::StringConverter::parseInt(attr->value());
		//child->GetAttribute("GridY",&objy);
		attr = child->first_attribute("GridY");
		objy = Ogre::StringConverter::parseInt(attr->value());
		//child->GetAttribute("Mesh",&meshname);
		attr=child->first_attribute("Mesh");
		meshname = attr->value();
		//child->GetAttribute("Type",&objtype);
		attr=child->first_attribute("Type");
		objtype = attr->value();
		attr=child->first_attribute("Direction");
		objdir = Ogre::StringConverter::parseInt(attr->value());
		datalibrary->setData(datapath + "/GridX", objx);
		datalibrary->setData(datapath + "/GridY", objy);
		datalibrary->setData(datapath + "/Mesh", meshname);
		datalibrary->setData(datapath + "/Direction", objdir);
		//物品类型脚本
		std::string mapobjscript("none");
		datalibrary->getData(str(boost::format("StaticData/MapObjType/%1%/Script")%objtype), mapobjscript);
		datapath = std::string("GameData/BattleData/MapData/Map/M") + Ogre::StringConverter::toString(MapDataManager::getSingleton().getGridId(objx, objy)) + std::string("/MapObjType");
		if(mapobjscript != "none")
		{
			MapObjScriptInfo scriptinfo;
			scriptinfo.x = objx;
			scriptinfo.y = objy;
			scriptinfo.script = mapobjscript;
			scriptinfo.path = datapath + "/ScriptContext";
			mMapObjScriptInfo.push(scriptinfo);
		}
		datalibrary->setData(datapath, objtype);
		datalibrary->setData(datapath + "/MapObjModuleId", objname);
	}
	//delete element;

	//element = doc.FirstChildElement("MapEffect");
	element = doc.first_node("MapEffect");
	//for(child = child.begin(element); child != child.end(); child++)
	for(child = element->first_node(); child; child =child->next_sibling())
	{
		std::string particlename;
		//child->GetValue(&particlename);
		particlename = child->name();
		datapath = std::string("GameData/BattleData/MapData/MapParticleInfo/") + particlename;
		int particlex,particley;
		std::string name;
		//child->GetAttribute("GridX",&particlex);
		rapidxml::xml_attribute<> *attr = child->first_attribute("GridX");
		particlex = Ogre::StringConverter::parseInt(attr->value());
		//child->GetAttribute("GridY",&particley);
		attr = child->first_attribute("GridY");
		particley = Ogre::StringConverter::parseInt(attr->value());
		//child->GetAttribute("Type",&name);
		attr = child->first_attribute("Type");
		name = attr->value();
		datalibrary->setData(datapath + "/GridX", particlex);
		datalibrary->setData(datapath + "/GridY", particley);
		datalibrary->setData(datapath + "/Type", name);
	}

	terrain->createTerrain();
	//delete element;

	//载入区域信息
	//element = doc.FirstChildElement("MapArea");
	element = doc.first_node("MapArea");
	//for(child = child.begin(element); child != child.end(); child++)
	for(child = element->first_node(); child; child =child->next_sibling())
	{
		std::string areaname;
		//child->GetValue(&areaname);
		areaname = child->name();
		datapath = std::string("GameData/BattleData/MapData/Area/") + areaname;
		Area area(datapath + "/CoordList");
		std::vector<Crood> croodVec;
		//ticpp::Iterator<ticpp::Element> childchild;
		rapidxml::xml_node<> *childchild = child->first_node();
		//for(childchild = childchild.begin(child.Get()); childchild != childchild.end(); childchild++)
		for(; childchild; childchild=childchild->next_sibling())
		{
			std::string coordname;
			//childchild->GetValue(&coordname);
			coordname = childchild->name();
			int x;
			int y;
			//childchild->GetAttribute("X",&x);
			rapidxml::xml_attribute<> *attr = childchild->first_attribute("X");
			x = Ogre::StringConverter::parseInt(attr->value());
			//childchild->GetAttribute("Y",&y);
			attr = childchild->first_attribute("Y");
			y = Ogre::StringConverter::parseInt(attr->value());
			croodVec.push_back(Crood(x, y));
		}
		area.setCroodVec(croodVec);
		MapDataManager::getSingleton().mMapArea.insert(std::make_pair(areaname, area));

	}
	//delete element;

	//载入队伍信息
	//element = doc.FirstChildElement("MapTeam");
	element = doc.first_node("MapTeam");
	for(int n = 2; n < 5; n++)
	{
		std::string name = std::string("Team") + Ogre::StringConverter::toString(n);
		std::string factionid;
		//ticpp::Element* subelement = element->FirstChildElement(name);
		child = element->first_node(name.c_str());
		//subelement->GetAttribute("TeamFaction",&factionid);
		rapidxml::xml_attribute<> *attr = child->first_attribute("TeamFaction");
		factionid = attr->value();
		datalibrary->setData(std::string("GameData/BattleData/Team/")+ name+ "/FactionId", factionid);
		if(factionid != "none")
		{
			//subelement->GetAttribute("TeamType",&factionid);
			attr = child->first_attribute("TeamType");
			factionid = attr->value();
			datalibrary->setData(std::string("GameData/BattleData/Team/")+ name+ "/Relation", factionid);
		}
		//delete subelement;
	}
	std::string playerfactionid;
	datalibrary->getData("GameData/StoryData/Faction",playerfactionid);
	datalibrary->setData("GameData/BattleData/Team/Team1/FactionId",playerfactionid);
	datalibrary->setData("GameData/BattleData/Team/Team1/Relation","player");
	//delete element;

	//载入部队信息
	//element = doc.FirstChildElement("MapSquad");
	element = doc.first_node("MapSquad");
	MapSquadInfo mapsquadinfo;
	//for(child = child.begin(element); child != child.end(); child++)
	for(child = element->first_node(); child;child = child->next_sibling())
	{
		std::string teamid;
		//child->GetValue(&teamid);
		teamid = child->name();
		if(teamid == "Team1")
			mapsquadinfo.team = 1;
		else if(teamid == "Team2")
			mapsquadinfo.team = 2;
		else if(teamid == "Team3")
			mapsquadinfo.team = 3;
		else
			mapsquadinfo.team = 4;
		datapath = std::string("GameData/BattleData/SquadList");
		//ticpp::Iterator<ticpp::Element> childchild;
		rapidxml::xml_node<> *childchild = child->first_node();
		//for(childchild = childchild.begin(child.Get()); childchild != childchild.end(); childchild++)
		for(; childchild; childchild =childchild->next_sibling())
		{
// 			std::string squadid;
// 			std::string squadtype;
			//childchild->GetValue(&mapsquadinfo.squadId);
			mapsquadinfo.squadId = childchild->name();
// 			int x;
// 			int y;
// 			Direction d;
// 			int unitnum;
// 			int morale;
			//childchild->GetAttribute("Type",&mapsquadinfo.squadTempId);
			rapidxml::xml_attribute<> *attr = childchild->first_attribute("Type");
			mapsquadinfo.squadTempId = attr->value();
			//childchild->GetAttribute("GridX",&mapsquadinfo.x);
			attr = childchild->first_attribute("GridX");
			mapsquadinfo.x = Ogre::StringConverter::parseInt(attr->value());
			//childchild->GetAttribute("GridY",&mapsquadinfo.y);
			attr = childchild->first_attribute("GridY");
			mapsquadinfo.y = Ogre::StringConverter::parseInt(attr->value());
			//childchild->GetAttribute("UnitNum",&mapsquadinfo.unitNum);
			attr = childchild->first_attribute("UnitNum");
			mapsquadinfo.unitNum = Ogre::StringConverter::parseInt(attr->value());
			//childchild->GetAttribute("Direction",&mapsquadinfo.dir);
			attr = childchild->first_attribute("Direction");
			mapsquadinfo.dir = Ogre::StringConverter::parseInt(attr->value());
			mMapSquadInfo.push(mapsquadinfo);
// 			AVGSquadManager::getSingleton().addSquad(squadid,squadtype, datapath);
// 			int type;
// 			Formation f;
// 			datalibrary->getData(datapath + std::string("/") + squadid + std::string("/Type"), type );
// 			if(type == SQUAD_NORMAL)
// 				f = Line;
// 			else
// 				f = Loose;
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/GridX"), x, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/GridY"), y, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/UnitNumber"), unitnum, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/Direction"), d, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/Formation"), f, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/TeamId"), teamid, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/CreateType"), MapSquad, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/ActionPoint"), 0.0f, true );
// 			datalibrary->setData(datapath + std::string("/") + squadid + std::string("/Morale"), morale, true );
		}
	}
	//delete element;
	delete []s;
	return true;
}
bool MapLoader::loadMapFormSave()
{
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	int mapsize;
	datalibrary->getData("GameData/BattleData/MapData/MapSize", mapsize);
	MapDataManager::getSingleton().mMapSize = mapsize;
	std::vector<std::string> arealist = datalibrary->getChildList("GameData/BattleData/MapData/Area");
	std::vector<std::string>::iterator ite = arealist.begin();
	for( ; ite != arealist.end(); ite++)
	{
		Area area(str(boost::format("GameData/BattleData/MapData/Area/%1%/CoordList")%(*ite)));
		MapDataManager::getSingleton().mMapArea.insert(std::make_pair(*ite, area));
	}
	Terrain::getSingleton().createTerrain();
	std::string music;
	datalibrary->getData("GameData/StoryData/MusicName", music);
	AudioSystem::getSingleton().playStream(music,true,2000);
	return true;
}

void MapLoader::loadMapObj()
{
	DataLibrary* datalibrary = DataLibrary::getSingletonPtr();
	Terrain* terrain = Terrain::getSingletonPtr();
	std::string datapath("GameData/BattleData/MapData/MapObjModleInfo");
	std::vector<std::string> childlist;
	childlist = datalibrary->getChildList(datapath);
	if(childlist.size()>0)
	{
		for(unsigned int n = 0; n < childlist.size(); n++)
		{
			std::string meshname;
			int x,y,dir;
			datalibrary->getData(datapath + std::string("/") + childlist[n] + std::string("/Mesh"),meshname);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridX"),x);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridY"),y);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/Direction"),dir);
			int index;
			index = terrain->createMapObj(x,y,meshname, dir);
			datalibrary->setData(datapath + std::string("/") + childlist[n] + std::string("/Index"),index);
		}
	}
	datapath = "GameData/BattleData/MapData/MapParticleInfo";
	childlist = datalibrary->getChildList(datapath);
	if(childlist.size()>0)
	{
		for(unsigned int n = 0; n < childlist.size(); n++)
		{
			std::string particlename;
			int x,y;
			datalibrary->getData(datapath + std::string("/") + childlist[n] + std::string("/Particle"),particlename);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridX"),x);
			datalibrary->getData(datapath + std::string("/") +childlist[n] + std::string("/GridY"),y);
			int index;
			index = terrain->createMapParticle(x,y,particlename);
			datalibrary->setData(datapath + std::string("/") + childlist[n] + std::string("/Index"),index);
		}
	}
}

void MapLoader::initBattleSquad(bool loadfrommap)
{
	BattleSquadManager* battlesuqadmanager = BattleSquadManager::getSingletonPtr();
	DataLibrary* datalib =DataLibrary::getSingletonPtr();
	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();
	//AVGSquadManager* avgsquadmanager = AVGSquadManager::getSingletonPtr();
	std::string path = "GameData/BattleData/SquadList";
	if(loadfrommap)
	{
		//载入地图部队
		while(mMapSquadInfo.size() > 0)
		{
			MapSquadInfo squadinfo = mMapSquadInfo.front();
			if(squadinfo.unitNum==0)
				DataLibrary::getSingletonPtr()->getData(str(boost::format("StaticData/SquadData/%1%/UnitNum")%squadinfo.squadTempId),squadinfo.unitNum);
			BattleSquad* battlesquad = new BattleSquad(str(boost::format("%1%/%2%")%path%squadinfo.squadId));
			battlesuqadmanager->mSquadList.insert(std::make_pair(battlesquad->getSquadId(),battlesquad));
			if(!battlesquad->init(str(boost::format("StaticData/SquadData/%1%")%squadinfo.squadTempId),
				squadinfo.team, squadinfo.unitNum, squadinfo.x, 
				squadinfo.y, squadinfo.dir))
			{
				BattleSquadManager::BattleSquadIte ite = battlesuqadmanager->mSquadList.find(battlesquad->getSquadId());
				delete battlesquad;
				battlesuqadmanager->mSquadList.erase(ite);
			}
			else
			{
				suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
													battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
				SquadGraphics* grap = suqadgrapmanager->getSquad(battlesquad->getSquadId());
				grap->setVisible(battlesquad->getViewbyPlayer());
			}
			mMapSquadInfo.pop();
		}
		//载入玩家部队
		std::vector<std::string> childlist;
		childlist = datalib->getChildList(std::string("GameData/StoryData/SquadData"));
		if(childlist.size()>0)
		{
			std::vector<std::string>::iterator ite;
			for(ite = childlist.begin(); ite != childlist.end(); ite++)
			{
				BattleSquad* battlesquad = new BattleSquad(str(boost::format("%1%/%2%")%path%(*ite)));
				battlesuqadmanager->mSquadList.insert(std::make_pair(battlesquad->getSquadId(),battlesquad));
// 				std::string datapath = std::string("GameData/BattleData/SquadList/") + (*ite);
// 				datalib->copyNode(std::string("GameData/StoryData/SquadData/EnableSquad/") + (*ite),datapath, true);
// 				int type;
// 				Formation f;
// 				datalib->getData(datapath + std::string("/Type"), type );
// 				if(type == SQUAD_NORMAL)
// 					f = Line;
// 				else
// 					f = Loose;
// 				datalib->setData(datapath +std::string("/TeamId"), std::string("Team1"), true );
// 				datalib->setData(datapath +std::string("/Grapid"),battlesuqadmanager->mCurid, true);
// 				datalib->setData(datapath +std::string("/CreateType"), StroySquad, true );
// 				datalib->setData(datapath +std::string("/Direction"), North, true );
// 				datalib->setData(datapath +std::string("/Formation"), f, true );
// 				datalib->setData(datapath +std::string("/ActionPoint"), 0.0f, true );
// 				BattleSquad* battlesquad = new BattleSquad((*ite),battlesuqadmanager->mCurid,-10,-10); 
// 				SquadGraphics* squadgrap = suqadgrapmanager->createSquad((*ite), datapath, battlesuqadmanager->mCurid, -10, -10,North,Line,battlesquad->getUnitGrapNum());
// 				squadgrap->setFormation(f,false);
// 				squadgrap->setDirection(North,false);
				if(!battlesquad->init(str(boost::format("GameData/StoryData/SquadData/%1%")%(*ite)),1))
				{
					BattleSquadManager::BattleSquadIte ite = battlesuqadmanager->mSquadList.find(battlesquad->getSquadId());
					delete battlesquad;
					battlesuqadmanager->mSquadList.erase(ite);
				}
				else
				{
					suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
						battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
				}
//				battlesuqadmanager->mCurid ++;
			}
		}
	}
	else
	{
		std::vector<std::string> childlist;
		childlist = datalib->getChildList(path);
		if(childlist.size()>0)
		{
			std::vector<std::string>::iterator ite;
			for(ite = childlist.begin(); ite != childlist.end(); ite++)
			{
				std::string datapath = path + std::string("/") + (*ite);
				BattleSquad* battlesquad = new BattleSquad(datapath);
				battlesquad->init();
				battlesuqadmanager->mSquadList.insert(std::make_pair(battlesquad->getSquadId(),battlesquad));
				suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
					battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
				SquadGraphics* grap = suqadgrapmanager->getSquad(battlesquad->getSquadId());
				if(battlesquad->getUnitNum() > 0)
					grap->setVisible(battlesquad->getViewbyPlayer());
				else
					grap->setVisible(false);
			}
		}
	}
}

// void MapLoader::creatSquadGrapAtPath(std::string path)
// {
// 	BattleSquadManager* battlesuqadmanager = BattleSquadManager::getSingletonPtr();
// 	DataLibrary* datalib =DataLibrary::getSingletonPtr();
// 	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();
// //	AVGSquadManager* avgsquadmanager = AVGSquadManager::getSingletonPtr();
// 	std::vector<std::string> childlist;
// 	childlist = datalib->getChildList(path);
// 	if(childlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = childlist.begin(); ite != childlist.end(); ite++)
// 		{
// 			std::string datapath = path + std::string("/") + (*ite);
// // 			int x,y;
// // 			Direction d;
// // 			Formation f;
// // 			datalib->getData(datapath + "/GridX",x);
// // 			datalib->getData(datapath + "/GridY",y);
// // 			datalib->getData(datapath + "/Direction",d);
// // 			datalib->getData(datapath + "/Formation",f);
// 			BattleSquad* battlesquad = new BattleSquad(datapath);
// 			if(!battlesquad->isInit())
// 			{
// 				delete battlesquad;
// 			}
// 			else
// 			{
// 				battlesuqadmanager->mSquadList.insert(std::make_pair(battlesquad->getSquadId(),battlesquad));
// 				if(battlesquad->getUnitNum() > 0)
// 				{
// 					suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
// 						battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
// 				}
// 			}
// // 			BattleSquad* battlesquad =  new BattleSquad((*ite),battlesuqadmanager->mCurid,x,y); 
// // 			SquadGraphics* squadgrap  = suqadgrapmanager->createSquad((*ite), datapath, battlesuqadmanager->mCurid,x,y,d,f, battlesquad->getUnitGrapNum());
// // 			if(!battlesquad->viewbyTeam(1) || battlesquad->IsEliminated())
// // 			{
// // 				squadgrap->setVisible(false);
// // 			}
// // 			squadgrap->setFormation(f,false);
// // 			squadgrap->setDirection(d,false);
// // 			datalib->setData(datapath +std::string("/Grapid"),battlesuqadmanager->mCurid);
// // 			battlesuqadmanager->mSquadList.push_back(battlesquad);
// // 			battlesuqadmanager->mCurid ++;
// 		}
// 	}
// }

void MapLoader::initMapScript()
{
	//运行场景物件脚本
	while(mMapObjScriptInfo.size() > 0)
	{
		MapObjScriptInfo& mapscriptinfo = mMapObjScriptInfo.front();
		LuaTempContext *tempcontext = new LuaTempContext();
		tempcontext->intMap.insert(std::make_pair("x", mapscriptinfo.x));
		tempcontext->intMap.insert(std::make_pair("y", mapscriptinfo.y));
		LuaSystem::getSingleton().executeFunction(mapscriptinfo.script, "onmap", mapscriptinfo.path, tempcontext);
		delete tempcontext;
		mMapObjScriptInfo.pop();
	}

	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",0);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",4);

	//运行地图初始化脚本
	std::string mapscript;
	bool re = DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapScript",mapscript);
	LuaSystem::getSingleton().executeFunction(mapscript, "initmap", "GameData/BattleData/MapData/MapScript/ScriptContext");
}