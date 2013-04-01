#include "GUIMapWindow.h"

#include "GUIBattle.h"
#include "boost/format.hpp"
#include "DataLibrary.h"

#include "BattleSquadManager.h"
#include "MapDataManager.h"

#include "StringTable.h"

#define OFFSET_X 3 
#define OFFSET_Y 3
#define LINE_WIDTH 1

GUIMapWindow::GUIMapWindow(MyGUI::Window* window,int Width,int Height):GUISubWindows(window,Width,Height),mWindow(window),mSelectPoint(NULL),mIsFadeEnd(true)
{
	assignWidget(mMap,"Map");

	std::string mapName;
	DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapMini",mapName);
	if(mapName!="")
		mMap->setImageTexture(mapName);
	else
	{
		DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapInfo",mapName);
		mapName=mapName.erase(0,7);
		mapName=std::string("battle")+mapName+".xml";
		rapidxml::xml_document<> doc;
		//doc.LoadFile(path,TIXML_ENCODING_UTF8);
		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(mapName, "Data", true);
		char* s=new char[stream->size()+1];
		stream->read(s,stream->size());
		s[stream->size()]='\0';
		doc.parse<0>(s);

		std::string str1;
		rapidxml::xml_node<> * element = doc.first_node("MapMini");
		str1 = element->value();
		DataLibrary::getSingletonPtr()->setData("GameData/BattleData/MapData/MapMini", str1);
		
		mMap->setImageTexture(str1);
		delete []s;
	}

	mSelect=mMap->createWidget<MyGUI::ImageBox>(MyGUI::WidgetStyle::Overlapped, "ImageBox", MyGUI::IntCoord(-20,-20,10,10), MyGUI::Align::Default);
	mSelect->setImageTexture("Select.png");

	mMapSize=MapDataManager::getSingletonPtr()->getMapSize();

	BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();

	for (std::map<std::string, BattleSquad*>::iterator it=battlesquadmanager->mSquadList.begin();it!=battlesquadmanager->mSquadList.end();it++)
	{
		addPoint(it->second);
	}

	/*assignWidget(mTerrainTypeLabel,"TerrainType");
	assignWidget(mGroundTypeLabel,"GroundType");
	assignWidget(mGroundObjLabel,"GroundObj");
	assignWidget(mPassableLabel,"Passable");*/
	assignWidget(mTerrainCovertLabel,"TerrainCovertLabel");
	assignWidget(mTerrainDefenceLabel,"TerrainDefenceLabel");
	assignWidget(mTerrainCavApLabel,"TerrainCavApLabel");
	assignWidget(mTerrainInfApLabel,"TerrainInfApLabel");

	MyGUI::TextBox* textBox;
	assignWidget(textBox,"DefenceLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("GUITerrainDefence"));
	assignWidget(textBox,"CovertLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("GUITerrainCovert"));
	assignWidget(textBox,"CavApLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("GUITerrainCavAp"));
	assignWidget(textBox,"InfApLabel");
	textBox->setCaption(StringTable::getSingletonPtr()->getString("GUITerrainInfAp"));

}

GUIMapWindow::~GUIMapWindow(void)
{

}

void GUIMapWindow::updateInfo( int x,int y )
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	TerrainType terraintype = MapDataManager::getSingleton().getTerrainType(x,y);
	GroundType groundtype = MapDataManager::getSingleton().getGroundType(x,y);
	std::string path = str(boost::format("StaticData/TerrainData/Terrain%1%/Name")%Ogre::StringConverter::toString(terraintype));
	std::string terrainname;
	bool re = datalib->getData(path, terrainname);
	
	std::string groundname;
	re = datalib->getData(str(boost::format("GameData/BattleData/MapData/Ground/G%1%")%groundtype),groundname);
	path = str(boost::format("StaticData/GroundData/%1%/Name")%groundname);
	//path = str(boost::format("StaticData/GroundData/Ground%1%/Name")%Ogre::StringConverter::toString(groundtype));
	re = datalib->getData(path, groundname);

	std::string groundobj;
	int gridid = MapDataManager::getSingleton().getGridId(x, y);
	path = str(boost::format("GameData/BattleData/MapData/Map/M%1%/MapObjType")%Ogre::StringConverter::toString(gridid));
	re = datalib->getData(path, groundobj, true);
	if(re)
	{
		path = str(boost::format("StaticData/MapObjType/%1%/Name")%groundobj);
		re = datalib->getData(path, groundobj);
	}

	float modifier;
	modifier = MapDataManager::getSingleton().getDefModify(x,y,0);
	mTerrainDefenceLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getCovert(x,y,0);
	mTerrainCovertLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getCavApCost(x,y,0);
	mTerrainCavApLabel->setCaption(Ogre::StringConverter::toString(modifier));
	modifier = MapDataManager::getSingleton().getInfApCost(x,y,0);
	mTerrainInfApLabel->setCaption(Ogre::StringConverter::toString(modifier));
}


void GUIMapWindow::showScene(std::string arg)
{
	mWindow->setVisible(true);
}

void GUIMapWindow::hideScene()
{
	mWindow->setVisible(false);
}

void GUIMapWindow::addPoint( BattleSquad* squad )
{
	int x=squad->getGridX();
	int y=squad->getGridY();
	MyGUI::ImageBox* point=mMap->createWidget<MyGUI::ImageBox>(MyGUI::WidgetStyle::Overlapped, "ImageBox", MyGUI::IntCoord(OFFSET_X+(8+LINE_WIDTH)*(x+(20-mMapSize)/2),OFFSET_Y+(8+LINE_WIDTH)*(y+(20-mMapSize)/2),8,8), MyGUI::Align::Default);
	
	std::string tempid;
	DataLibrary::getSingletonPtr()->getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%squad->getTeam()), tempid);
	if (tempid=="player")
	{
		updatePointState(squad,point);
	}
	else if (tempid=="enemy1" || tempid=="enemy2" ||tempid=="enemy3")
	{
		point->setImageTexture("EnemyPoint.png");
	}
	else if (tempid=="alliance")
	{
		point->setImageTexture("AlliancePoint.png");
	}
		
	mPoints[squad]=point;
}

void GUIMapWindow::updatePoint()
{
	BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();

	for (std::map<std::string, BattleSquad*>::iterator it=battlesquadmanager->mSquadList.begin();it!=battlesquadmanager->mSquadList.end();it++)
	{
		if(mPoints.count(it->second)!=0)
		{
			int x=it->second->getGridX();
			int y=it->second->getGridY();
		
			MyGUI::ImageBox* point=mPoints[it->second];

			if (it->second->getUnitNum()==0)
			{
				point->setVisible(false);

				continue;
			}

			point->setPosition(OFFSET_X+(8+LINE_WIDTH)*(x+(20-mMapSize)/2),OFFSET_Y+(8+LINE_WIDTH)*(y+(20-mMapSize)/2));

			if(it->second->getViewbyPlayer())
			{
				point->setVisible(true);
			}
			else
			{
				point->setVisible(false);
			}

		}
		else
		{
			addPoint(it->second);
		}
	}

	if (mIsFadeEnd && mSelectPoint!=NULL)
	{
		if (mFadeIn)
		{
			MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
			mFadeController = item->castType<MyGUI::ControllerFadeAlpha>();

			mFadeController->setAlpha(0);
			mFadeController->setCoef(1/(500.f/1000));
			mFadeController->setEnabled(true);
			mFadeIn=false;
			mIsFadeEnd=false;

			mFadeController->eventPostAction+=MyGUI::newDelegate(this, &GUIMapWindow::eventUpdateAction);
			MyGUI::ControllerManager::getInstance().addItem(mSelectPoint,mFadeController); 
		}
		else
		{
			MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
			mFadeController = item->castType<MyGUI::ControllerFadeAlpha>();

			mFadeController->setAlpha(1);
			mFadeController->setCoef(1/(500.f/1000));
			mFadeController->setEnabled(true);
			mFadeIn=true;
			mIsFadeEnd=false;


			mFadeController->eventPostAction+=MyGUI::newDelegate(this, &GUIMapWindow::eventUpdateAction);
			MyGUI::ControllerManager::getInstance().addItem(mSelectPoint,mFadeController); 
		}
	}
}

void GUIMapWindow::updatePointState(BattleSquad* squad,MyGUI::ImageBox* point)
{
	MyGUI::ImageBox* tmpPoint;
	if (point!=NULL)
	{
		tmpPoint=point;
	}
	else
	{
		if (squad->getUnitNum()==0)
		{
			return ;
		}

		tmpPoint=mPoints[squad];
	}
		
	if (squad->getActionPoint()<2)
	{
		tmpPoint->setImageTexture("PlayerPointAPEnd.png");
	}
	else
	{
		tmpPoint->setImageTexture("PlayerPoint.png");
	}
}

bool GUIMapWindow::GridInputEvent( int x,int y )
{
	mSelect->setPosition(2+9*(x+(20-mMapSize)/2),2+9*(y+(20-mMapSize)/2));
	updateInfo(x,y);
	return false;
}

void GUIMapWindow::setSelectPoint(BattleSquad* squad)
{
	clearSelect();

	MyGUI::ImageBox* point=mPoints[squad];
	mSelectPoint=point;
	MyGUI::ControllerItem* item = MyGUI::ControllerManager::getInstance().createItem(MyGUI::ControllerFadeAlpha::getClassTypeName());
	mFadeController = item->castType<MyGUI::ControllerFadeAlpha>();
	mFadeController->eventPostAction+=MyGUI::newDelegate(this, &GUIMapWindow::eventUpdateAction);

	point->setAlpha(1);

	mFadeController->setAlpha(0);
	mFadeController->setCoef(1/(500.f/1000));
	mFadeController->setEnabled(true);
	mFadeIn=false;
	mIsFadeEnd=false;

	MyGUI::ControllerManager::getInstance().addItem(point,mFadeController); 
}

void GUIMapWindow::eventUpdateAction(MyGUI::Widget* sender)
{
	mIsFadeEnd=true;
}

void GUIMapWindow::updateAllPlayerPointState()
{
	BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();

	for (std::map<std::string, BattleSquad*>::iterator it=battlesquadmanager->mSquadList.begin();it!=battlesquadmanager->mSquadList.end();it++)
	{
		std::string tempid;
		DataLibrary::getSingletonPtr()->getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%it->second->getTeam()), tempid);
		if (tempid=="player")
		{
			updatePointState(it->second);
		}
	}
}

void GUIMapWindow::clearSelect()
{
	if (mSelectPoint!=NULL)
	{
		MyGUI::ControllerManager::getInstance().removeItem(mSelectPoint);
		mSelectPoint->setAlpha(1);
		mSelectPoint=NULL;
	}
}