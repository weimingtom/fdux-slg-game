#pragma once

#include "IIRoot.h"
#include <list>
#include <string>
#include <vector>

class Area
{
public:
	Area(std::string name);
	~Area();

	std::string mName;

	void setVisable(bool visable);

	void addCoord(int x, int y);
	void removeCoord(int x, int y);
	std::vector<int> getCoordList();
private:
	struct AreaCoord
	{
		int x;
		int y;
		Ogre::SceneNode* mCoordNode;
		Ogre::Entity * mCoordEnt;
		~AreaCoord()
		{
			mCoordNode->detachObject(mCoordEnt);
			IIRoot::getSingleton().mSceneMgr->destroySceneNode(mCoordNode);
			IIRoot::getSingleton().mSceneMgr->destroyEntity(mCoordEnt);
		}
	};
	typedef std::list<AreaCoord*>::iterator CoordIte;
	std::list<AreaCoord*> mCoordList;
	bool mVisable;
};