#include "WeaponGrap.h"

#include "Core.h"
#include "DataLibrary.h"

WeaponGrap::WeaponGrap(std::string name)
{
	std::string mesh;
	std::string mat;
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Weapon/")+name+std::string("/meshName"),mesh);
	DataLibrary::getSingletonPtr()->getData(std::string("GameData/Weapon/")+name+std::string("/matName"),mat);

	Ogre::Entity* entity=Core::getSingletonPtr()->mSceneMgr->createEntity(mesh);
	if (mat!="null")
	{
		entity->setMaterialName(mat);
	}
}

WeaponGrap::~WeaponGrap(void)
{
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mWeaponEntity);
}
