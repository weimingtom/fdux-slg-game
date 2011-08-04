#pragma once

#include <Ogre.h>
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemListener.h>

#include <string>
#include <vector>

#include "squaddefine.h"

//小队的图形类,负责一切图形活动

class UnitGrap;
class SquadGrapManager;
class GUISquadBillBoard; 
class GUISquadValueBillBoard;

class SquadGraphics//:public ParticleUniverse::ParticleSystemListener 
{
public:
	friend SquadGrapManager;//仅限定单位管理器可以构造单位

	~SquadGraphics(void);

	enum WeaponMode
	{
		MainWepon,
		SceWepon
	};

	void setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,std::map<int,Direction>& directions);
	void combatPosition(Direction d);
	void idlePosition();
	void changeUnitPosition(Direction d,Ogre::Vector3 offsetVector);
	void setDirection(Direction d,bool isAnim);
	Direction getDirection();
	void setFormation(Formation f,bool isAnim);
	bool isFormationOrDirectionOver();
	bool isTransformOver();
	void stopTransform();

	void setAnimation(std::string name,UnitType object,bool isLoop,bool returnInit);
	bool isAnimationOver(UnitType object);
	void setInitAnimation(UnitType object);

// 	void setEffect(std::string name,UnitType object);
// 	bool isEffectOver(UnitType object);
// 	void stopEffect(UnitType object);

	void setGrid(int x,int y);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDeath();
	void setRecover(int num);
	bool isDeathOver();
	bool isRecoverOver();
	void stopDeath();

	void setWeaponMode(WeaponMode mode);

	void setVisible(bool visible);
	bool getVisible() {return mVisibale;}
	void setParticleVisible(bool visible);

	bool addParticle(std::string id,std::string name,UnitType object);
	void startParticle(std::string id);
	void stopParticle(std::string id);
	void delParticle(std::string id);

	void showValue(std::string value,Ogre::ColourValue c);
	void stopShowValue();
	void setSquadBillBoardState(bool hasAp);

	Ogre::Vector3 getLeaderPosition(); 
	std::vector<Ogre::Vector3> getSoiderPosition();

	std::string mSName;

private:
	SquadGraphics(std::string squadName, std::string datapath, Ogre::Vector2& grid,Direction direction,Formation f,unsigned int index,int soldierCount);

	void update(unsigned int deltaTime);

	//void handleParticleSystemEvent (ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent);

	void setCheckUnitHeight(bool enable);

	void doDeathStep();

	UnitGrap* createSoldier();

	void getFormationPosition(Formation f,Direction d,Ogre::Vector3& CommanderVector,Ogre::Vector3 SoldierVector[]);

	std::map<int,Ogre::Vector3>* getUnitMovePath(UnitGrap* unit,std::map<int,Ogre::Vector3>& vectors,std::map<int,Direction>& directions,bool isCommander);

	unsigned int mID;

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSceneMgr;

	GUISquadBillBoard* mSquadBB;
	GUISquadValueBillBoard* mSquadValueBB;

	std::string mSquadId;
	std::string mLeaderMesh;
	std::string mLeaderMat;
	UnitGrap* mCommanderUnit;
	std::string mSoilderMesh;
	std::string mSoilderMat;
	std::string mPWeaponMesh;
	std::string mPWeaponMat;
	std::string mPWeaponAniGroup;
	std::string mSWeaponMesh;
	std::string mSWeaponMat;
	std::string mSWeaponAniGroup;
	bool mSWeaponBow;
	std::string mShieldMesh;
	std::string mShieldMat;
	std::string mFactionTexture;
	std::vector<UnitGrap*> mSoldierUnits;
	int mSoldierIndex;
	Formation mFormation;
	Direction mDirection;
	Direction mIdleDirection;
	std::string mMoveSound;

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
	
// 	ParticleUniverse::ParticleSystem* mPUSystem;
// 	bool mPUSystemEnd;

	Ogre::Animation* mNodeAnimation;
	Ogre::AnimationState* mNodeAnimationState;
	bool mReturnInitAni;
	
	bool mVisibale;
};
