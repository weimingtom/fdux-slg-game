#include "SquadGraphics.h"

#include "Core.h"
#include "DataLibrary.h"

#include "UnitGrap.h"

SquadGraphics::SquadGraphics(std::string unitName,unsigned int index)
{
	mNode=Core::getSingletonPtr()->mSceneMgr->getRootSceneNode()->createChildSceneNode(unitName+Ogre::StringConverter::toString(index));

	//获取数据
	std::string commanderMesh;
	std::string commanderMat;
	std::string soldierMesh;
	std::string soldierMat;
	std::string mainWeaponName;
	std::string secWeaponName;
	std::string shieldName;
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMesh"),commanderMesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMat"),commanderMat);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMesh"),soldierMesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMat"),soldierMat);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMainWeapon"),mainWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderSecWeapon"),secWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderShield"),shieldName);

	//组建单位队伍与组建武器
	mCommanderUnit=new UnitGrap(commanderMesh,commanderMat,mNode->createChildSceneNode("Commander"));
	mCommanderUnit->createWeapon(mainWeaponName,UnitGrap::MainWepon);
	mCommanderUnit->createWeapon(secWeaponName,UnitGrap::SecWepon);
	mCommanderUnit->createWeapon(shieldName,UnitGrap::Shield);

	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMainWeapon"),mainWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierSecWeapon"),secWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierShield"),shieldName);
	for (int i=0;i<4;i++)
	{
		UnitGrap* unit=new UnitGrap(soldierMesh,soldierMat,mNode->createChildSceneNode("Soldier"+Ogre::StringConverter::toString(i)));
		
		unit->createWeapon(mainWeaponName,UnitGrap::MainWepon);
		unit->createWeapon(secWeaponName,UnitGrap::SecWepon);
		unit->createWeapon(shieldName,UnitGrap::Shield);

		mSoldierUnits.push_back(unit);
	}
	
	//设置参数
	setHealth(5);
	setWeaponMode(SquadGraphics::MainWepon);
}

SquadGraphics::~SquadGraphics(void)
{
	delete mCommanderUnit;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		delete (*it);
	}
}

void SquadGraphics::setMovePath()
{

}

void SquadGraphics::setAnimation( std::string name )
{

}

void SquadGraphics::setEffect( std::string name,std::string position )
{

}

void SquadGraphics::setGrid(int x,int y)
{

}

void SquadGraphics::setScale( Ogre::Vector3 scale,bool isAnim )
{

}

void SquadGraphics::setDirection( Ogre::Vector3 d,bool isAnim )
{

}

void SquadGraphics::setHealth( int health )
{
	mSoldierUnits.at(0)->mNode->setPosition(-10,0,-10);
	mSoldierUnits.at(1)->mNode->setPosition(10,0,-10);
	mSoldierUnits.at(2)->mNode->setPosition(-10,0,10);
	mSoldierUnits.at(3)->mNode->setPosition(10,0,10);
}

void SquadGraphics::setWeaponMode( WeaponMode mode )
{

}

void SquadGraphics::update( unsigned int deltaTime )
{

}

