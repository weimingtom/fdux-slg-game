#pragma once

#include <Ogre.h>
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemListener.h>

#include <string>
#include <vector>

//小队的图形类,负责一切图形活动

class UnitGrap;
class SquadGrapManager;

class SquadGraphics:public ParticleUniverse::ParticleSystemListener 
{
public:
	friend SquadGrapManager;//仅限定单位管理器可以构造单位

	~SquadGraphics(void);

	enum WeaponMode
	{
		MainWepon,
		SceWepon
	};

	enum Object
	{
		Commander,
		Soldier,
		Squad
	};

	enum Direction
	{
		North,
		South,
		West,
		East
	};

	enum Formation
	{
		Line,
		Circular,
		Loose
	};

	void setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions);
	void setDirection(Direction d,bool isAnim);
	void setFormation(Formation f,bool isAnim);
	bool isTransformOver();
	void stopTransform();

	void setAnimation(std::string name,Object object,bool isLoop,bool returnInit);
	bool isAnimationOver(Object object);
	void setInitAnimation(Object object);

	void setEffect(std::string name,Object object);
	bool isEffectOver(Object object);
	void stopEffect(Object object);

	void setGrid(int x,int y);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDeath();
	void setRecover(int num);
	bool isDeathOver();
	bool isRecoverOver();
	void stopDeath();

	void setWeaponMode(WeaponMode mode);

private:
	SquadGraphics(std::string squadName,Ogre::Vector2& grid,Direction direction,Formation f,unsigned int index);

	void update(unsigned int deltaTime);

	void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

	void setCheckUnitHeight(bool enable);

	void doDeathStep();

	UnitGrap* createSoldier();

	unsigned int mID;

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSceneMgr;

	std::string mCommanderUnitName;
	UnitGrap* mCommanderUnit;
	std::string mSoldierUnitName;
	std::string mMainWeaponName;
	std::string mSecWeaponName;
	std::string mShieldName;
	std::vector<UnitGrap*> mSoldierUnits;
	int mSoldierIndex;
	Formation mFormation;

	enum DeathStep
	{
		playAni,
		changeMat,
		moveUnit,
		resetAni
	};
	UnitGrap* mDeathUnit;
	UnitGrap* mReliefUnit;
	std::string mReliefAniName;
	bool mReliefAniLoop;
	DeathStep mDeathStep;
	
	ParticleUniverse::ParticleSystem* mPUSystem;
	bool mPUSystemEnd;

	Ogre::Animation* mNodeAnimation;
	Ogre::AnimationState* mNodeAnimationState;
	bool mReturnInitAni;

};
