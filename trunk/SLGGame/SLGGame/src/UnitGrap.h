#pragma once

#include <ogre.h>
#include <string>
#include <vector>
#include <map>

#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemListener.h>

#include "WeaponGrap.h"

class AnimationBlender;

//单位类,由单位组成小队
class UnitGrap//:public ParticleUniverse::ParticleSystemListener 
{
public:
	UnitGrap(std::string unitmesh, std::string unitmat,std::string factiontex,Ogre::SceneNode* node);
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

	void createWeapon(std::string mesh, std::string mat,WeaponType type);

	void setWeapon(WeaponType type,BoneType bone);

	void setAniGroup(std::string anigroup);

// 	void setEffect(std::string name,Ogre::Vector3 offect=Ogre::Vector3::ZERO);
// 
// 	bool isEffectOver();
// 
// 	void stopEffect();

	void setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,float MoveSpeed=1.0);

	void setPosition(float x,float z);

	void setHeight();

	void setPositionOffset(float ox,float oy);

	void setAnimation(std::string name,bool loop,bool returnInit);

	void stopTransform();

	void setFadeInOut(bool isIn);

	void doFadeInOut(unsigned int deltaTime);

	void update(unsigned int deltaTime);

//	void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

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
	std::string mAttackName;
	std::string mDeathName;
	std::string mRecoverName;
	std::string mIdleName;
	int mFormationPosition;
	float mOffsetX;
	float mOffsetY;

	AnimationBlender* mAniBlender;//动画代理
	Ogre::Animation* mNodeAnimation;
	Ogre::AnimationState* mNodeAnimationState;

// 	Ogre::SceneNode* mPUNode;
// 	ParticleUniverse::ParticleSystem* mPUSystem;
// 	bool mPUSystemEnd;
	bool mReturnInitAni;
	bool mIsAnimationComplete;


	void setParticleVisible(bool visible);
	bool mParticleVisible;

	bool addParticle(std::string id,std::string name);
	void startParticle(std::string id);
	void stopParticle(std::string id);
	void delParticle(std::string id);

	Ogre::SceneNode* mParticleNode;
	typedef std::map<std::string, ParticleUniverse::ParticleSystem*> PUMap;
	PUMap mPUMap;
	typedef std::map<std::string, ParticleUniverse::ParticleSystem*>::iterator PUMapIte;
};
