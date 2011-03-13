#include "SquadGraphics.h"

#include "Core.h"
#include "DataLibrary.h"

#include "UnitGrap.h"
#include "AnimationBlender.h"

SquadGraphics::SquadGraphics(std::string unitName,unsigned int index):mPUSystem(NULL)
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
	std::string initAnimation;
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMesh"),commanderMesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMat"),commanderMat);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMesh"),soldierMesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMat"),soldierMat);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderMainWeapon"),mainWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderSecWeapon"),secWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderShield"),shieldName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/CommanderInitAnimation"),initAnimation);

	//组建单位队伍与组建武器
	mCommanderUnit=new UnitGrap(commanderMesh,commanderMat,mNode->createChildSceneNode("Commander"));
	mCommanderUnit->createWeapon(mainWeaponName,UnitGrap::MainWepon);
	mCommanderUnit->createWeapon(secWeaponName,UnitGrap::SecWepon);
	mCommanderUnit->createWeapon(shieldName,UnitGrap::Shield);
	mCommanderUnit->mAniBlender->init(initAnimation);

	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierMainWeapon"),mainWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierSecWeapon"),secWeaponName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierShield"),shieldName);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Squad/")+unitName+std::string("/SoldierInitAnimation"),initAnimation);
	for (int i=0;i<4;i++)
	{
		UnitGrap* unit=new UnitGrap(soldierMesh,soldierMat,mNode->createChildSceneNode("Soldier"+Ogre::StringConverter::toString(i)));
		
		unit->createWeapon(mainWeaponName,UnitGrap::MainWepon);
		unit->createWeapon(secWeaponName,UnitGrap::SecWepon);
		unit->createWeapon(shieldName,UnitGrap::Shield);
		unit->mAniBlender->init(initAnimation);

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

	if (mPUSystem!=NULL)
	{
		mNode->detachObject(mPUSystem);
		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
		mPUSystem=NULL;
	}
}

void SquadGraphics::setMovePath()
{

}

void SquadGraphics::setAnimation(std::string name,Object object,bool isLoop)
{
	switch(object)
	{
	case Squad:
		{

		}
	case Commander:
		{
			mCommanderUnit->mAniBlender->blend(name,AnimationBlender::BlendWhileAnimating,0.2,isLoop);
			if (object!=Squad)
			{
				break;
			}
		}
	case Soldier:
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				(*it)->mAniBlender->blend(name,AnimationBlender::BlendWhileAnimating,0.2,isLoop);
			}
			break;
		}
	}
}

void SquadGraphics::setEffect( std::string name,Object object)
{
	switch(object)
	{
	case Squad:
		{
			if (mPUSystem!=NULL)
			{
				mNode->detachObject(mPUSystem);
				Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
				mPUSystem=NULL;
			}

			mPUSystem=Core::getSingletonPtr()->createPUSystem(mNode->getName()+"_PU",name);
			mPUSystem->prepare();
			mNode->attachObject(mPUSystem);
			mPUSystem->start();
			break;
		}
	case Commander:
		{
			mCommanderUnit->setEffect(name);
			break;
		}
	case Soldier:
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				(*it)->setEffect(name);
			}
			break;
		}
	}
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
	mCommanderUnit->mNode->setPosition(0,5,0);
	mSoldierUnits.at(0)->mNode->setPosition(-10,5,-10);
	mSoldierUnits.at(1)->mNode->setPosition(10,5,-10);
	mSoldierUnits.at(2)->mNode->setPosition(-10,5,10);
	mSoldierUnits.at(3)->mNode->setPosition(10,5,10);
}

void SquadGraphics::setWeaponMode( WeaponMode mode )
{
	UnitGrap::WeaponType type;
	if (mode==MainWepon)
	{
		type=UnitGrap::MainWepon;
	}
	else
	{
		type=UnitGrap::SecWepon;
	}

	mCommanderUnit->setWeapon(type,"Handle.R");
	mCommanderUnit->setWeapon(UnitGrap::Shield,"Handle.L");
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setWeapon(type,"Handle.R");
		(*it)->setWeapon(UnitGrap::Shield,"Handle.L");
	}
}

void SquadGraphics::update( unsigned int deltaTime )
{
	mCommanderUnit->update(deltaTime);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->update(deltaTime);
	}
}

