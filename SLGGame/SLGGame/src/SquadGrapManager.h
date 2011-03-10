#pragma once

#include "SquadGraphics.h"

#include <string>
#include <vector>

class SquadGrapManager
{
public:
	SquadGrapManager(Ogre::SceneManager* sceneMgr);
	~SquadGrapManager(void);

	SquadGraphics* createUnit(std::string unitName,int x,int y);
	void destoryUnit(SquadGraphics* unit);

	void update(unsigned int deltaTime);

private:
	std::vector<SquadGraphics*> mUnitList;
	unsigned int unitIndex;
};
