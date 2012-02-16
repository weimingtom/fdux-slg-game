#pragma once

#include <string>

#include "cutscene.h"
#include "squaddefine.h"

#include <string>

class SquadGraphics;

class EffectCutScene:public CutScene
{
public:
	EffectCutScene(std::string id,UnitType object,std::string name,std::string sound,unsigned int lasttime);
	~EffectCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	std::string mParticleId;
	std::string mSound;
};
