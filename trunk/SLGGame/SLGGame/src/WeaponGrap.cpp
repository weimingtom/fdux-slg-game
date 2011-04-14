#include "WeaponGrap.h"

#include "Core.h"
#include "DataLibrary.h"

#include <OgreTagPoint.h>

WeaponGrap::WeaponGrap(std::string mesh, std::string mat)
{
	mWeaponEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(mesh);
	if (mat!="none")
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

	//ParticleUniverse::ParticleSystem* pSys = Core::getSingletonPtr()->createPUSystem(mWeaponEntity->getName()+"_"+Ogre::StringConverter::toString(1),"PUMediaPack/Fireplace_01");
	//Ogre::TagPoint* p= body->attachObjectToBone(boneName,pSys);
	//pSys->setScale(Ogre::Vector3(0.01,0.01,0.01));
	//pSys->setScaleVelocity(0.01);
	//pSys->prepare();
	//pSys->start();

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

void WeaponGrap::startFade()
{
	for(int i = 0; i < mWeaponEntity->getNumSubEntities(); ++i)
	{
		Ogre::MaterialPtr p;
		if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(mWeaponEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy"))
		{
			p=Ogre::MaterialManager::getSingletonPtr()->getByName(mWeaponEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
		}
		else
		{
			p=mWeaponEntity->getSubEntity(i)->getMaterial()->clone(mWeaponEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
		}

		Ogre::Pass *pass = p->getTechnique(0)->getPass(0);
		pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA); 
		pass->setDepthCheckEnabled(true); 
		pass->setDepthWriteEnabled(false);
		mWeaponEntity->getSubEntity(i)->setMaterial(p);
	}
}

void WeaponGrap::overFade(bool isV)
{
	for(int i = 0; i < mWeaponEntity->getNumSubEntities(); ++i)
	{
		std::string n = mWeaponEntity->getSubEntity(i)->getMaterial()->getName();
		n.replace(n.find("_Copy"),5,"");
		mWeaponEntity->getSubEntity(i)->setMaterialName(n);
		Ogre::MaterialManager::getSingletonPtr()->remove(mWeaponEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
	}
	mWeaponEntity->setVisible(isV);
}

void WeaponGrap::doFade(float alpha)
{
	for(int i = 0; i < mWeaponEntity->getNumSubEntities(); ++i)
	{
		Ogre::Pass *pass = mWeaponEntity->getSubEntity(i)->getMaterial()->getTechnique(0)->getPass(0);
		pass->setDiffuse(pass->getDiffuse().r, pass->getDiffuse().g, pass->getDiffuse().b, alpha); 
	}
}
