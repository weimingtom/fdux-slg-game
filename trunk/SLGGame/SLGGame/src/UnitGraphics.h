#pragma once

#include <Ogre.h>

#include <string>
#include <vector>

//单位的图形类,负责一切图形活动

class UnitGrapManager;

class UnitGraphics
{
public:
	friend UnitGrapManager;//仅限定单位管理器可以构造单位

	~UnitGraphics(void);

	void setMovePath();

	void setAnimation(std::string name);

	void setEffect(std::string name,std::string position);

	void setPosition(Ogre::Vector3 v);

	void setScale(Ogre::Vector3 scale,bool isAnim);

	void setDirection(Ogre::Vector3 d,bool isAnim);

	void setDamage(int damage);

private:
	UnitGraphics(void);

	void update(unsigned int deltaTime);
	bool needUpdate;

	Ogre::SceneNode* mNode;

	std::vector<Ogre::Entity*> mUnitEntitys;
	Ogre::Entity* mMainWeapon;
	Ogre::Entity* mSecWeapon;
	Ogre::Entity* mShield;

	std::vector<Ogre::AnimationState*> mAnimsList;
	Ogre::AnimationState* mCurrentAnim;

};
