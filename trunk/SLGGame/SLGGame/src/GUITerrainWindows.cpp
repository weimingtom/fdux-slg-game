#include "GUITerrainWindows.h"

#include "DataLibrary.h"

GUITerrainWindows::GUITerrainWindows(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window)
{
	assignWidget(mTerrainNameLabel,"TerrainNameLabel");
	assignWidget(mTerrainDescribeLabel,"TerrainDescribeLabel");
	assignWidget(mTerrainDefenceLabel,"TerrainDefenceLabel");
	assignWidget(mTerrainCavApLabel,"TerrainCavApLabel");
	assignWidget(mTerrainInfApLabel,"TerrainInfApLabel");

	window->setPosition(Width-window->getWidth(),0);

	DataLibrary::getSingletonPtr()->getData("GameData/GameData/BattleData/MapData/MapSize",mMapSize);
}

GUITerrainWindows::~GUITerrainWindows(void)
{
}

void GUITerrainWindows::showScene( std::string arg )
{

}

void GUITerrainWindows::hideScene()
{

}

void GUITerrainWindows::FrameEvent()
{

}

bool GUITerrainWindows::GridInputEvent( int x,int y )
{
	int Grid=x+mMapSize*y;

	int TerrainType,GroundType;
	DataLibrary::getSingletonPtr()->getData("GameData/GameData/BattleData/MapData/Map/M"+Ogre::StringConverter::toString(Grid)+"/TerrainType",TerrainType);
	
	DataLibrary::getSingletonPtr()->getData("GameData/GameData/BattleData/MapData/Map/M"+Ogre::StringConverter::toString(Grid)+"/GroundType",GroundType);

	mTerrainNameLabel->setCaption("T:"+Ogre::StringConverter::toString(TerrainType)+",G:"+Ogre::StringConverter::toString(GroundType));
	
	std::string MapObjType;
	if(DataLibrary::getSingletonPtr()->getData("GameData/GameData/BattleData/MapData/Map/M"+Ogre::StringConverter::toString(Grid)+"/MapObjType",MapObjType,true))
	{
		mTerrainDescribeLabel->setCaption("ID:"+MapObjType);
	}
	else
	{
		mTerrainDescribeLabel->setCaption("ID:None");
	}
	
	return true;
}
