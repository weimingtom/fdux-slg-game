#pragma once

#include "cutscene.h"

#include "Core.h"

class MapPUCutScene: public CutScene
{
public:
	MapPUCutScene(Ogre::Vector3 pos, float estime, std::string name, std::string sound);
	~MapPUCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	std::string mSound;
	float mEsTime;
	ParticleUniverse::ParticleSystem* mParticle;
	Ogre::SceneNode* mNode;
};