#pragma once

#include <ogre.h>
#include <string>

//Œ‰∆˜¿‡
class WeaponGrap
{
public:
	WeaponGrap(std::string mesh, std::string mat);
	~WeaponGrap(void);

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
