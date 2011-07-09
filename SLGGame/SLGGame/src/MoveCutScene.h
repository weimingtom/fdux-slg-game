#pragma once

#include <Ogre.h>
#include <vector>

#include "cutscene.h"

#include "SquadGraphics.h"

class MoveCutScene:public CutScene
{
public:
	MoveCutScene(unsigned int id,std::vector<Ogre::Vector2>& grids,Ogre::Vector2& currentGrid);
	~MoveCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	std::map<int,Ogre::Vector3> vectors;
	std::map<int,Ogre::Quaternion> quaternions;
	std::map<int,Direction> directions;
	SquadGraphics* mSquadGraphics;
	Ogre::Vector3 mEndPosition;
	int mDirection;
};
