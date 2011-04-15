#pragma once

#include <ogre.h>

#include <string>
#include <vector>

#include "iisingleton.hpp"

class SquadGraphics;

using namespace izayoi;

#include "squaddefine.h"

class SquadGrapManager:public IISingleton<SquadGrapManager>
{
public:
	SquadGrapManager(Ogre::SceneManager* sceneMgr);
	~SquadGrapManager(void);

	SquadGraphics* createSquad(std::string unitName,std::string datapath,unsigned int id,int x,int y,Direction d,Formation f,int soldierCount=4);
	void destorySquad(unsigned int id);
	SquadGraphics* getSquad(unsigned int id);

	void update(unsigned int deltaTime);

private:
	std::vector<SquadGraphics*> mUnitList;
	unsigned int unitIndex;
};
