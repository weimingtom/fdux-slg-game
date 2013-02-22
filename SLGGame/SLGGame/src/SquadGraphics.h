#pragma once

#include <Ogre.h>
#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemListener.h>

#include <string>
#include <vector>
#include <map>

#include "squaddefine.h"

//小队的图形类,负责一切图形活动

class UnitGrap;
class SquadGrapManager;
class GUISquadBillBoard; 
class GUISquadValueBillBoard;

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

	void setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,std::map<int,Direction>& directions);
	void combatPosition(Direction d,bool isAnim);
	void idlePosition(bool isAnim);
	void changeUnitPosition(Direction d,Ogre::Vector3 offsetVector,bool isAnim);
	void setDirection(Direction d,bool isAnim);
	Direction getDirection();
	bool isDirectionOver();
	void setFormation(int f,bool isAnim);
	bool isFormationOrDirectionOver();
	bool isTransformOver();
	void stopTransform();

	void setAnimation(std::string name,UnitType object,bool isLoop,bool returnInit);
	bool isAnimationOver(UnitType object);
	void setInitAnimation(UnitType object);

	void setGrid(int x,int y);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDeath(int num);
	void setRecover(int num);
	bool isDeathOver();
	bool isRecoverOver();
	void stopDeath();

	void setWeaponMode(WeaponMode mode);

	void defenseAction(SquadGraphics* enemy,bool isMove);
	bool isDefenseActionOver();

	void setVisible(bool visible);
	bool getVisible() {return mVisibale;}
	void setParticleVisible(bool visible);

	bool addParticle(std::string id,std::string name,int object);
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
	//SquadGraphics(std::string squadName, std::string datapath, Ogre::Vector2& grid,Direction direction,Formation f,unsigned int index,int soldierCount);
	SquadGraphics(std::string squadid, std::string datapath, int gridx, int gridy, int direction, int formation, int soldierCount);

	void update(unsigned int deltaTime);

	void setCheckUnitHeight(bool enable);

	void doDeathStep();

	UnitGrap* createSoldier();

	void getFormationPosition(int f,int d,Ogre::Vector3& CommanderVector,Ogre::Vector3 SoldierVector[]);

	void updateBB();

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
	int mSoilderHaveWeapon;
	std::string mPWeaponMesh;
	std::string mPWeaponMat;
	std::string mPWeaponAniGroup;
	std::string mPWeaponPU;
	Ogre::Vector3 mPWeaponPUVector;
	std::string mSWeaponMesh;
	std::string mSWeaponMat;
	std::string mSWeaponPU;
	Ogre::Vector3 mSWeaponPUVector;
	std::string mSWeaponAniGroup;
	bool mSWeaponBow;
	std::string mShieldMesh;
	std::string mShieldMat;
	std::string mShieldPU;
	std::string mHorseMesh;
	std::string mHorseMat;
	Ogre::Vector3 mShieldVector;
	std::string mFactionTexture;
	std::vector<UnitGrap*> mSoldierUnits;
	int mSoldierIndex;
	int mFormation;
	int mDirection;
	int mIdleDirection;
	int mNextDirection;
	std::string mMoveSound;
	int mX;
	int mY;

	enum DeathStep
	{
		playAni,
		changeMat,
		moveUnit,
		resetAni
	};
	std::map<UnitGrap*,UnitGrap*> mDeathUnits;
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
