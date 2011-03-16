#include "SquadGraphics.h"

#include "Core.h"
#include "DataLibrary.h"

#include "UnitGrap.h"
#include "AnimationBlender.h"

#include "Terrain.h"

SquadGraphics::SquadGraphics(std::string unitName,Ogre::Vector2& grid,Direction direction,unsigned int index):mID(index),mPUSystem(NULL),mPUSystemEnd(false),mNodeAnimation(NULL),mNodeAnimationState(NULL)
{
	mSceneMgr=Core::getSingletonPtr()->mSceneMgr;
	mNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(unitName+Ogre::StringConverter::toString(index));

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
	setGrid(grid.x,grid.y);
	setDirection(direction,false);
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

	if (mNodeAnimationState!=NULL)
	{
		mSceneMgr->destroyAnimationState(mNode->getName()+"_AniState");
		mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
	}
	
	mNode->removeAndDestroyAllChildren();
	mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());
}

void SquadGraphics::setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions)
{
	mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani", vectors.size()*1);
	mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mNode);
	
	int timePosition=0;
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(timePosition);
	kf->setTranslate(mNode->getPosition());
	kf->setRotation(mNode->getOrientation());

	std::map<int,Ogre::Vector3>::iterator itr  =  vectors.begin();
	for(  ;  itr !=  vectors.end();  ++itr )
	{
		timePosition+=1;
		kf = track->createNodeKeyFrame(timePosition);

		kf->setTranslate(itr->second);

		std::map<int,Ogre::Quaternion>::iterator itr1;
		itr1 = quaternions.find(itr->first);

		if( itr1 != quaternions.end() )
		{
			kf->setRotation(itr1->second);
		}
	}
	
	mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

	mNodeAnimationState->setLoop(false);
	mNodeAnimationState->setEnabled(true);

}

bool SquadGraphics::isMoveOver()
{
	if (mNodeAnimationState!=NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
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


void SquadGraphics::setInitAnimation( Object object )
{
	switch(object)
	{
	case Squad:
		{

		}
	case Commander:
		{
			mCommanderUnit->mAniBlender->BackToInit();
			if (object!=Squad)
			{
				break;
			}
		}
	case Soldier:
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				(*it)->mAniBlender->BackToInit();
			}
			break;
		}
	}
}


bool SquadGraphics::isAnimationOver(Object object)
{
	if (object==Commander)
	{
		return mCommanderUnit->mAniBlender->complete;
	}
	else
	{
		if (mSoldierUnits.size()!=0)
		{
			return mSoldierUnits.at(0)->mAniBlender->complete;
		}
		else
		{
			return true;
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
			mPUSystem->addParticleSystemListener(this);
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

void SquadGraphics::handleParticleSystemEvent( ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent )
{
	if (particleUniverseEvent.componentType==ParticleUniverse::CT_SYSTEM && particleUniverseEvent.eventType==ParticleUniverse::PU_EVT_NO_PARTICLES_LEFT)
	{
		mPUSystemEnd=true;
	}
}

bool SquadGraphics::isEffectOver( Object object )
{
	switch(object)
	{
	case Squad:
		{
			return mPUSystemEnd;
			break;
		}
	case Commander:
		{
			mCommanderUnit->isEffectOver();
			break;
		}
	case Soldier:
		{
			if (mSoldierUnits.size()!=0)
			{
				return mSoldierUnits.at(0)->isEffectOver();
			}
			else
			{
				return true;
			}
			break;
		}
	}

	return true;
}

void SquadGraphics::stopEffect( Object object )
{
	if (mPUSystem!=NULL)
	{
		switch(object)
		{
		case Squad:
			{
				mPUSystem->stop();
				break;
			}
		case Commander:
			{
				mCommanderUnit->stopEffect();
				break;
			}
		case Soldier:
			{
				for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
				{
					(*it)->stopEffect();
				}
				break;
			}
		}
	}
}

void SquadGraphics::setGrid(int x,int y)
{
	float wx,wy=0;
	Terrain::getSingletonPtr()->getWorldCoords(x,y,wx,wy);
	
	mNode->setPosition(wx,Terrain::getSingletonPtr()->getHeight(wx,wy),wy);
}

void SquadGraphics::setScale( Ogre::Vector3 scale,bool isAnim )
{

}

void SquadGraphics::setDirection( Direction d,bool isAnim )
{
	Ogre::Quaternion q;

	switch(d)
	{
	case North:
		{
			q.FromAngleAxis(Ogre::Degree(180),Ogre::Vector3(0,1,0));
			break;
		}
	case South:
		{
			q.FromAngleAxis(Ogre::Degree(0),Ogre::Vector3(0,1,0));
			break;
		}
	case West:
		{
			q.FromAngleAxis(Ogre::Degree(270),Ogre::Vector3(0,1,0));
			break;
		}
	case East:
		{
			q.FromAngleAxis(Ogre::Degree(90),Ogre::Vector3(0,1,0));
			break;
		}
	}

	if (isAnim)
	{
		mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani", 2);
		mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mNode);

		Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(4);
		kf->setRotation(q);

		mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

		mNodeAnimationState->setEnabled(true);
	}
	else
	{
		mNode->setOrientation(q);
	}
}

void SquadGraphics::setHealth( int health )
{
	mCommanderUnit->mNode->setPosition(0,5,0);
	mSoldierUnits.at(0)->mNode->setPosition(-2,5,2);
	mSoldierUnits.at(1)->mNode->setPosition(2,5,-2);
	mSoldierUnits.at(2)->mNode->setPosition(-2,5,-2);
	mSoldierUnits.at(3)->mNode->setPosition(2,5,2);
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
	
	if (mNodeAnimationState!=NULL)
	{
		if (mNodeAnimationState->getTimePosition() >= mNodeAnimationState->getLength())
		{
			mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
			mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
			mNodeAnimation=NULL;
			mNodeAnimationState=NULL;
		}
		else
		{
			mNodeAnimationState->addTime(deltaTime/1000.0f);
		}
	}

	mCommanderUnit->update(deltaTime);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->update(deltaTime);
	}
}

