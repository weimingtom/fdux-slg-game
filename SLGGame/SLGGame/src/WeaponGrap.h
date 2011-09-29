#pragma once

#include <ogre.h>
#include <string>

#include "Core.h"

//Œ‰∆˜¿‡
class WeaponGrap
{
public:
	WeaponGrap(std::string mesh, std::string mat,std::string particleName,Ogre::Vector3 particleVector);
	~WeaponGrap(void);

	void attachWeapon(Ogre::Entity* body,std::string boneName);

	void detachWeapon(Ogre::Entity* body);

	std::string getAttachBoneName();

	void playParticleUniverse(std::string name);

	void stopParticleUniverse();

	void startFade();
	
	void overFade(bool isV);

	void doFade(float alpha);

private:
	Ogre::Entity* mBody;
	std::string mBoneName;
	Ogre::Entity* mWeaponEntity;
	std::string mParticleName;
	Ogre::Vector3 mParticleVector;
	ParticleUniverse::ParticleSystem* pSys;
	ParticleUniverse::ParticleSystem* displayPSys;

};
