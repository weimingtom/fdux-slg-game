#include "GUITerrainWindows.h"

#include "DataLibrary.h"
#include "StringTable.h"
#include "MapDataManager.h"

#include "boost\format.hpp"

GUITerrainWindows::GUITerrainWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mTerrainTypeLabel,"TerrainType");
	assignWidget(mGroundTypeLabel,"GroundType");
	assignWidget(mGroundObjLabel,"GroundObj");
	assignWidget(mPassableLabel,"Passable");
	assignWidget(mTerrainCovertLabel,"TerrainCovertLabel");
	assignWidget(mTerrainDefenceLabel,"TerrainDefenceLabel");
	assignWidget(mTerrainCavApLabel,"TerrainCavApLabel");
	assignWidget(mTerrainInfApLabel,"TerrainInfApLabel");
	assignWidget(mTerrainGridXLabel,"TerrainGridX");
	assignWidget(mTerrainGridYLabel,"TerrainGridY");

	window->setPosition(Width-window->getWidth(),0);

	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapSize",mMapSize);

	StringTable* stringtabel = StringTable::getSingletonPtr();
	mWindow->setCaption(stringtabel->getString("GUITerrainWindow"));

	mCurX = -1;
	mCurY = -1;
}

GUITerrainWindows::~GUITerrainWindows(void)
{
}

void GUITerrainWindows::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUITerrainWindows::hideScene()
{
	mWindow->setVisible(false);
}

void GUITerrainWindows::FrameEvent()
{

}

bool GUITerrainWindows::GridInputEvent( int x,int y )
{
	/*
	int Grid=x+mMapSize*y;

	int TerrainType,GroundType;
	std::string s=str(boost::format("GameData/BattleData/MapData/Map/M%1%/")%Ogre::StringConverter::toString(Grid));
	DataLibrary::getSingletonPtr()->getData(s+"TerrainType",TerrainType);
	
	DataLibrary::getSingletonPtr()->getData(s+"GroundType",GroundType);

	mTerrainNameLabel->setCaption("T:"+Ogre::StringConverter::toString(TerrainType)+",G:"+Ogre::StringConverter::toString(GroundType));
	
	std::string MapObjType;
	if(DataLibrary::getSingletonPtr()->getData(s+"MapObjType",MapObjType,true))
	{
		mTerrainDescribeLabel->setCaption("ID:"+MapObjType);
	}
	else
	{
		mTerrainDescribeLabel->setCaption("ID:None");
	}
	*/
	if(mCurY == y && mCurX == x)
		return false;
	mCurX = x;
	mCurY = y;
	mTerrainGridXLabel->setCaption(Ogre::StringConverter::toString(x));
	mTerrainGridYLabel->setCaption(Ogre::StringConverter::toString(y));
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	TerrainType terraintype = MapDataManager::getSingleton().getTerrainType(x,y);
	GroundType groundtype = MapDataManager::getSingleton().getGroundType(x,y);
	std::string path = str(boost::format("StaticData/TerrainData/Terrain%1%/Name")%Ogre::StringConverter::toString(terraintype));
	std::string terrainname;
	bool re = datalib->getData(path, terrainname);
	mTerrainTypeLabel->setCaption(terrainname);
	
	std::string groundname;
	path = str(boost::format("StaticData/GroundData/Ground%1%/Name")%Ogre::StringConverter::toString(groundtype));
	re = datalib->getData(path, groundname);
	mGroundTypeLabel->setCaption(groundname);

	std::string groundobj;
	int gridid = x+mMapSize*y;
	path = str(boost::format("GameData/BattleData/MapData/Map/M%1%/MapObjType")%Ogre::StringConverter::toString(gridid));
	re = datalib->getData(path, groundobj, true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/Name")%groundobj);
		re = datalib->getData(path, groundobj);
		mGroundObjLabel->setCaption(groundobj);
	}
	else
	{
		mGroundObjLabel->setCaption("");
	}
	float modifier;
	modifier = MapDataManager::getSingleton().getDefModify(x,y,1);
	mTerrainDefenceLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getCovert(x,y,1);
	mTerrainCovertLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getCavApCost(x,y,1);
	mTerrainCavApLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getInfApCost(x,y,1);
	mTerrainInfApLabel->setCaption(Ogre::StringConverter::toString(modifier));
	return false;
}
