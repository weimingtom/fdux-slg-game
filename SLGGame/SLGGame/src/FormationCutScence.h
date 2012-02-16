#pragma once

#include "cutscene.h"
#include "squaddefine.h"

#include <string>

class SquadGraphics;

class FormationCutScene:public CutScene
{
public:

	FormationCutScene(std::string id,Formation formation);
	~FormationCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Formation mForm;
	unsigned int time;
};
