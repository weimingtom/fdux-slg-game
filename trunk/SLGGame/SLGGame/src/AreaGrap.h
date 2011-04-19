#pragma once

#include <string>
#include <vector>
#include "Core.h"

class AreaGrap
{
public:
	AreaGrap(std::string path, std::string mat);
	AreaGrap(std::vector<int> coordlist, std::string mat);
	~AreaGrap();
	
	bool inArea(int x, int y);
private:
	std::vector<int> mCoordList;

	void creatArea(std::string mat);

	Ogre::SceneNode* mNode;
	Ogre::ManualObject* mAreaObj;
};