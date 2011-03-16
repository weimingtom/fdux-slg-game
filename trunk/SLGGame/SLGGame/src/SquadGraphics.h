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

	void setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions);
	bool isMoveOver();

	void setAnimation(std::string name,Object object,bool isLoop);
	bool isAnimationOver(Object object);
	void setInitAnimation(Object object);

	void setEffect(std::string name,Object object);
	bool isEffectOver(Object object);
	void stopEffect(Object object);

	void setGrid(int x,int y);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDirection(Direction d,bool isAnim);

	void setHealth(int health);

	void setWeaponMode(WeaponMode mode);

private:
	SquadGraphics(std::string unitName,Ogre::Vector2& grid,Direction direction,unsigned int index);

	void update(unsigned int deltaTime);

	void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

	unsigned int mID;

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSceneMgr;

	UnitGrap* mCommanderUnit;
	std::vector<UnitGrap*> mSoldierUnits;
	
	ParticleUniverse::ParticleSystem* mPUSystem;
	bool mPUSystemEnd;

	Ogre::Animation* mNodeAnimation;
	Ogre::AnimationState* mNodeAnimationState;

};
