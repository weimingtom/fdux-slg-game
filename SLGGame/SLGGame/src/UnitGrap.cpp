#include "UnitGrap.h"

#include "Core.h"

UnitGrap::UnitGrap(std::string meshName,std::string matName,Ogre::SceneNode* node):
mNode(node),
mMainWeapon(NULL),
mSecWeapon(NULL),
mShield(NULL)
{
	mUnitEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(meshName);
	if (matName!="null")
	{
		mUnitEntity->setMaterialName(matName);
	}
	mNode->attachObject(mUnitEntity);
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
	
	mNode->detachAllObjects();
	mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mUnitEntity);
}

void UnitGrap::setWeapon( WeaponType type,std::string boneName )
{

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
