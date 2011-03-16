#include "UnitGrap.h"

#include "Core.h"
#include "AnimationBlender.h"

#include <iostream>

UnitGrap::UnitGrap(std::string meshName,std::string matName,Ogre::SceneNode* node):
mNode(node),
mMainWeapon(NULL),
mSecWeapon(NULL),
mShield(NULL),
mPUSystem(NULL),
mPUSystemEnd(false)
{
	mUnitEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(meshName);
	if (matName!="null")
	{
		mUnitEntity->setMaterialName(matName);
	}
	mNode->attachObject(mUnitEntity);

	mAniBlender=new AnimationBlender(mUnitEntity);
}

UnitGrap::~UnitGrap(void)
{	
	mUnitEntity->detachAllObjectsFromBone();

	if (mMainWeapon!=NULL)
	{
		delete mMainWeapon;
	}

	if (mSecWeapon!=NULL)
	{
		delete mSecWeapon;
	}

	if (mShield!=NULL)
	{
		delete mShield;
	}
	
	if (mPUSystem!=NULL)
	{
		mNode->detachObject(mPUSystem);
		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
		mPUSystem=NULL;
	}

	mNode->detachAllObjects();
	mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mUnitEntity);
}

void UnitGrap::setWeapon( WeaponType type,std::string boneName )
{

	if (mMainWeapon!=NULL)
	{
		if (mMainWeapon->getAttachBoneName()==boneName)
		{
			mMainWeapon->detachWeapon(mUnitEntity);
		}
	}

	if (mSecWeapon!=NULL)
	{
		if (mSecWeapon->getAttachBoneName()==boneName)
		{
			mSecWeapon->detachWeapon(mUnitEntity);
		
		}
	}

	if (mShield!=NULL)
	{
		if (mShield->getAttachBoneName()==boneName)
		{
			mShield->detachWeapon(mUnitEntity);
		}
	}


	switch(type)
	{
	case MainWepon:
		{
			if (mMainWeapon!=NULL)
			{
				mMainWeapon->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	case SecWepon:
		{
			if (mSecWeapon!=NULL)
			{
				mSecWeapon->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	case Shield:
		{
			if (mShield!=NULL)
			{
				mShield->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	}
}

void UnitGrap::createWeapon( std::string name,WeaponType type )
{
	if (name!="null")
	{
		switch(type)
		{
		case MainWepon:
			{
				mMainWeapon=new WeaponGrap(name);
				break;
			}
		case SecWepon:
			{
				mSecWeapon=new WeaponGrap(name);
				break;
			}
		case Shield:
			{
				mShield=new WeaponGrap(name);
				break;
			}
		}
	}
}

void UnitGrap::update( unsigned int deltaTime )
{
	mAniBlender->addTime(deltaTime/1000.0f);
}

void UnitGrap::setEffect( std::string name )
{
	if (mPUSystem!=NULL)
	{
		mNode->detachObject(mPUSystem);
		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
		mPUSystem=NULL;
	}

	mPUSystem=Core::getSingletonPtr()->createPUSystem(mNode->getName()+"_PU",name);
	mPUSystem->addParticleSystemListener(this);
	mNode->attachObject(mPUSystem);
	mPUSystem->prepare();
	mPUSystem->start();
}

bool UnitGrap::isEffectOver()
{
	return mPUSystemEnd;
}

void UnitGrap::handleParticleSystemEvent( ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent )
{
	if (particleUniverseEvent.componentType==ParticleUniverse::CT_SYSTEM && particleUniverseEvent.eventType==ParticleUniverse::PU_EVT_NO_PARTICLES_LEFT)
	{
		mPUSystemEnd=true;
	}
}

void UnitGrap::stopEffect()
{
	mPUSystem->stop();
}
