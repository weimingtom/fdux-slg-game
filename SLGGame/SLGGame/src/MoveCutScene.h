#pragma once

#include <Ogre.h>
#include <vector>

#include "cutscene.h"

class SquadGraphics;

class MoveCutScene:public CutScene
{
public:
	MoveCutScene(unsigned int id,std::vector<Ogre::Vector2>& grids,Ogre::Vector2& currentGrid);
	~MoveCutScene(void);

protected:
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	Ogre::Vector3 mEndPosition;
	int mDirection;
};
