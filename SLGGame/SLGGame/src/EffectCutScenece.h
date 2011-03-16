#pragma once

#include <string>

#include "cutscenes.h"

class SquadGraphics;

class EffectCutScenece:public CutScence
{
public:
	enum EffectObject
	{
		Commander,
		Soldier,
		Squad
	};

	EffectCutScenece(unsigned int id,EffectObject object,std::string name);
	~EffectCutScenece(void);

protected:
	bool endCutScence();
	void skipCutScence();
	void updateCutScence(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	EffectObject mObject;
};
