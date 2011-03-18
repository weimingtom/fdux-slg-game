#pragma once

#include <ogre.h>

#include <string>
#include <vector>

#include "iisingleton.hpp"

class SquadGraphics;

using namespace izayoi;

class SquadGrapManager:public IISingleton<SquadGrapManager>
{
public:
	SquadGrapManager(Ogre::SceneManager* sceneMgr);
	~SquadGrapManager(void);

	enum Direction
	{
		North,
		South,
		West,
		East
	};

	enum Formation
	{
		Line,
		Circular,
		Loose
	};

	SquadGraphics* createSquad(std::string unitName,unsigned int id,int x,int y,Direction d,Formation f);
	void destorySquad(unsigned int id);
	SquadGraphics* getSquad(unsigned int id);

	void update(unsigned int deltaTime);

private:
	std::vector<SquadGraphics*> mUnitList;
	unsigned int unitIndex;
};
