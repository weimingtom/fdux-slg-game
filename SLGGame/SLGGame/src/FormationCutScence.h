#pragma once

#include "cutscene.h"
#include "squaddefine.h"

class SquadGraphics;

class FormationCutScene:public CutScene
{
public:

	FormationCutScene(unsigned int id,Formation formation);
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
