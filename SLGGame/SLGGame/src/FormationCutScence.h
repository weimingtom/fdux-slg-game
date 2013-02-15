#pragma once

#include "cutscene.h"
#include "squaddefine.h"

#include <string>

class SquadGraphics;

class FormationCutScene:public CutScene
{
public:

	FormationCutScene(std::string id, int formation);
	~FormationCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	int mForm;
	unsigned int time;
};
