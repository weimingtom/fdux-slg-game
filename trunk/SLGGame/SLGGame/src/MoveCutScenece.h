#pragma once

#include <Ogre.h>
#include <vector>

#include "cutscenes.h"

class SquadGraphics;

class MoveCutScenece:public CutScence
{
public:
	MoveCutScenece(unsigned int id,std::vector<Ogre::Vector2>& grids,Ogre::Vector2& currentGrid);
	~MoveCutScenece(void);

protected:
	bool endCutScence();
	void skipCutScence();
	void updateCutScence(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Ogre::Vector3 mEndPosition;
	int mDirection;
};
