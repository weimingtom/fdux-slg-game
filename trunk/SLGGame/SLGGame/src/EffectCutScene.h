#pragma once

#include <string>

#include "cutscene.h"

class SquadGraphics;

class EffectCutScene:public CutScene
{
public:
	enum EffectObject
	{
		Commander,
		Soldier,
		Squad
	};

	EffectCutScene(unsigned int id,EffectObject object,std::string name);
	~EffectCutScene(void);

protected:
	void startCutScence() {}
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	EffectObject mObject;
};
