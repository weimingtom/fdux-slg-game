#pragma once

#include <ogre.h>
#include <string>
#include <vector>

#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemListener.h>

#include "WeaponGrap.h"

class AnimationBlender;

//单位类,由单位组成小队
class UnitGrap:public ParticleUniverse::ParticleSystemListener 
{
public:
	UnitGrap(std::string meshName,std::string matName,Ogre::SceneNode* node);
	~UnitGrap(void);
	
	enum WeaponType
	{
		NoneWepon,
		MainWepon,
		SecWepon,
		Shield
	};

	void createWeapon(std::string name,WeaponType type);

	void setWeapon(WeaponType type,std::string boneName);

	void setEffect(std::string name);

	bool isEffectOver();

	void stopEffect();

	void setPosition(float x,float z);

	void setHeight();

	void update(unsigned int deltaTime);

	void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

	Ogre::SceneNode* mNode;
	Ogre::Entity* mUnitEntity;
	bool mIsCheckHeight;

	WeaponGrap* mMainWeapon;
	WeaponGrap* mSecWeapon;
	WeaponGrap* mShield;

	AnimationBlender* mAniBlender;//动画代理
	ParticleUniverse::ParticleSystem* mPUSystem;
	bool mPUSystemEnd;
};
