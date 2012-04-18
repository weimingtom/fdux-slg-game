#pragma once

#include <string>
#include <vector>
#include "Core.h"

class AreaGrap
{
public:
	AreaGrap(std::string path, std::string mat, float height = 0.5f);
	AreaGrap(std::vector<int> coordlist, std::string mat, float height = 0.5f);
	~AreaGrap();
	
	bool inArea(int x, int y);
	void changeArea(std::vector<int> coordlist);
private:
	std::vector<int> mCoordList;

	void creatArea(std::string mat);

	float mHeight;
	std::string mMat;
	Ogre::SceneNode* mNode;
	Ogre::ManualObject* mAreaObj;
};