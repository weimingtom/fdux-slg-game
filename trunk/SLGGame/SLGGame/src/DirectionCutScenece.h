#pragma once

#include "cutscenes.h"

class SquadGraphics;

class DirectionCutScenece:public CutScence
{
public:
	enum Direction
	{
		North,
		South,
		West,
		East
	};

	DirectionCutScenece(unsigned int id,Direction direction);
	~DirectionCutScenece(void);

protected:
	bool endCutScence();
	void skipCutScence();
	void updateCutScence(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Direction mDirection;
};
