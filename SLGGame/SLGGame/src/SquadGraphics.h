#pragma once

#include <Ogre.h>
#include <ParticleUniverseSystem.h> 

#include <string>
#include <vector>

//小队的图形类,负责一切图形活动

class UnitGrap;
class SquadGrapManager;

class SquadGraphics
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

	void setMovePath();

	void setAnimation(std::string name,Object object,bool isLoop);

	void setEffect(std::string name,Object object);

	void setGrid(int x,int y);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDirection(Ogre::Vector3 d,bool isAnim);

	void setHealth(int health);

	void setWeaponMode(WeaponMode mode);

private:
	SquadGraphics(std::string unitName,unsigned int index);

	void update(unsigned int deltaTime);

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSceneMgr;

	UnitGrap* mCommanderUnit;
	std::vector<UnitGrap*> mSoldierUnits;
	
	ParticleUniverse::ParticleSystem* mPUSystem;

};
