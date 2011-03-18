#pragma once

#include "cutscene.h"

class SquadGraphics;

class DirectionCutScene:public CutScene
{
public:
	enum Direction
	{
		North,
		South,
		West,
		East
	};

	DirectionCutScene(unsigned int id,Direction direction);
	~DirectionCutScene(void);

protected:
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Direction mDirection;
};
