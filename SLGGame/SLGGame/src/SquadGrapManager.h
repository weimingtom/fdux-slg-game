#pragma once

#include <ogre.h>

#include <string>
#include <vector>

#include "iisingleton.hpp"

class SquadGraphics;
class BillboardManager;

using namespace izayoi;

#include "squaddefine.h"

class SquadGrapManager:public IISingleton<SquadGrapManager>
{
public:
	SquadGrapManager(Ogre::SceneManager* sceneMgr);
	~SquadGrapManager(void);

	void clear();

//	SquadGraphics* createSquad(std::string unitName,std::string datapath,unsigned int id,int x,int y,Direction d,Formation f,int soldierCount=4);
//	void destorySquad(unsigned int id);
//	SquadGraphics* getSquad(unsigned int id);

	void update(unsigned int deltaTime);

//	void setParticleVisible(bool visible);

	bool createSquadGrap(std::string squadid, std::string datapath, int gridx, int gridy, int direction, int formation, int soldierCount);
	void destorySquad(std::string squadid);
	SquadGraphics* getSquad(std::string squadid);
	void clearBBState();

	void hideSquad();

private:
	std::map<std::string, SquadGraphics*> mSquadGrapMap;
// 	std::vector<SquadGraphics*> mUnitList;
// 	unsigned int unitIndex;
	BillboardManager* mBBManager;
};
