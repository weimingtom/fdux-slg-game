#pragma once

#include <ogre.h>
#include <string>
#include <vector>

#include "WeaponGrap.h"

//单位类,由单位组成小队
class UnitGrap
{
public:
	UnitGrap(std::string meshName,std::string matName,Ogre::SceneNode* node);
	~UnitGrap(void);
	
	enum WeaponType
	{
		MainWepon,
		SecWepon,
		Shield
	};

	void createWeapon(std::string name,WeaponType type);

	void setWeapon(WeaponType type,std::string boneName);

	void setAnimation(std::string name);

	void update(unsigned int deltaTime);

	Ogre::SceneNode* mNode;
	Ogre::Entity* mUnitEntity;

	WeaponGrap* mMainWeapon;
	WeaponGrap* mSecWeapon;
	WeaponGrap* mShield;

	std::vector<Ogre::AnimationState*> mAnimsList;
	Ogre::AnimationState* mCurrentAnim;
};
