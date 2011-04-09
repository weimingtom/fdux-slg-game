#pragma once

#include <ogre.h>
#include <string>

//Œ‰∆˜¿‡
class WeaponGrapIG
{
public:
	WeaponGrapIG(std::string name);
	~WeaponGrapIG(void);

	void attachWeapon(Ogre::Entity* body,std::string boneName);

	void detachWeapon(Ogre::Entity* body);

	std::string getAttachBoneName();

	void startFade();
	
	void overFade(bool isV);

	void doFade(float alpha);

private:
	std::string mBoneName;
	Ogre::Entity* mWeaponEntity;
};
