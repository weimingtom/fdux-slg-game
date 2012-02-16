#pragma once

#include "cutscene.h"
#include "squaddefine.h"

#include <string>

class SquadGraphics;

class DirectionCutScene:public CutScene
{
public:

	DirectionCutScene(std::string id,Direction direction);
	~DirectionCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Direction mDirection;
};
