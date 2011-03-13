#include "WeaponGrap.h"

#include "Core.h"
#include "DataLibrary.h"

#include <OgreTagPoint.h>

WeaponGrap::WeaponGrap(std::string name)
{
	std::string mesh;
	std::string mat;
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Weapon/")+name+std::string("/meshName"),mesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Weapon/")+name+std::string("/matName"),mat);

	mWeaponEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(mesh);
	if (mat!="null")
	{
		mWeaponEntity->setMaterialName(mat);
	}
}

WeaponGrap::~WeaponGrap(void)
{
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mWeaponEntity);
}

void WeaponGrap::attachWeapon( Ogre::Entity* body,std::string boneName )
{
	body->attachObjectToBone(boneName,mWeaponEntity);
	mBoneName=boneName;

	ParticleUniverse::ParticleSystem* pSys = Core::getSingletonPtr()->createPUSystem(mWeaponEntity->getName()+"_"+Ogre::StringConverter::toString(1),"PUMediaPack/Fireplace_01");
	Ogre::TagPoint* p= body->attachObjectToBone(boneName,pSys);
	pSys->setScale(Ogre::Vector3(0.01,0.01,0.01));
	pSys->setScaleVelocity(0.01);
	pSys->prepare();
	pSys->start();

}

void WeaponGrap::detachWeapon(Ogre::Entity* body)
{
	body->detachObjectFromBone(mWeaponEntity);
	mBoneName="";
}

std::string WeaponGrap::getAttachBoneName()
{
	return mBoneName;
}
