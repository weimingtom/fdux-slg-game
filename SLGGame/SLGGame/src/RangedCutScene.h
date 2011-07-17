#pragma once
#include "cutscene.h"

#include "Core.h"

class RangedCutScene:public CutScene
{
public:
	RangedCutScene(Ogre::Vector3 startpoint, Ogre::Vector3 endpoint, int type, std::string resname);
	~RangedCutScene();
private:
	virtual void startCutScence();
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);

	void clear();

	Ogre::Vector3 mStartpoint;
	Ogre::Vector3 mEndpoint;
	Ogre::SceneNode* mNode;
	ParticleUniverse::ParticleSystem* mParticle;
	std::string mParticleId;
	Ogre::Entity* mEntity;
};