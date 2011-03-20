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
	UnitGrap(std::string unitName,Ogre::SceneNode* node);
	~UnitGrap(void);
	
	enum WeaponType
	{
		NoneWepon,
		MainWepon,
		SecWepon,
		Shield
	};

	enum BoneType
	{
		LeftHand,
		RightHand
	};

	void createWeapon(std::string name,WeaponType type);

	void setWeapon(WeaponType type,BoneType bone);

	void setEffect(std::string name);

	bool isEffectOver();

	void stopEffect();

	void setPosition(float x,float z);

	void setHeight();

	void setAnimation(std::string name,bool loop,bool returnInit);

	void setFadeInOut(bool isIn);

	void doFadeInOut(unsigned int deltaTime);

	void update(unsigned int deltaTime);

	void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

	Ogre::SceneNode* mNode;
	Ogre::Entity* mUnitEntity;
	bool mIsCheckHeight;
	float mAlpha;
	unsigned int mAlphaDeltaTime;
	bool mFadeInOut;

	WeaponGrap* mMainWeapon;
	WeaponGrap* mSecWeapon;
	WeaponGrap* mShield;
	std::string mLeftHandBoneName;
	std::string mRightHandBoneName;
	std::string mWalkName;
	std::string mDeathName;
	std::string mRecoverName;
	std::string mRotationName;
	int mFormationPosition;

	AnimationBlender* mAniBlender;//动画代理
	ParticleUniverse::ParticleSystem* mPUSystem;
	bool mPUSystemEnd;
	bool mReturnInitAni;
};
