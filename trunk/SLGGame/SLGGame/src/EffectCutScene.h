#pragma once

#include <string>

#include "cutscene.h"
#include "squaddefine.h"

class SquadGraphics;

class EffectCutScene:public CutScene
{
public:
	EffectCutScene(unsigned int id,UnitType object,std::string name);
	~EffectCutScene(void);

protected:
	void startCutScence() {}
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	UnitType mObject;
};
