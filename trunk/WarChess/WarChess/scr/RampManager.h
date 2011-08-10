#pragma once;

#include "IIRoot.h"
#include "Common.h"
#include <map>

class RampManager
{
public:
	RampManager(int blockSize,int gridSize);
	~RampManager();

	void setRamp(int x,int y);
	void removeRamp(int x,int y);

	bool isRamp(int x,int y);
private:
	float mBlockSize;
	int mMapSize;

	struct RampEnt
	{
		Ogre::SceneNode* rampNode;
		Ogre::Entity* rampEnt;
		~RampEnt()
		{
			rampNode->detachObject(rampEnt);

			IIRoot::getSingleton().mSceneMgr->destroySceneNode(rampNode);
			IIRoot::getSingleton().mSceneMgr->destroyEntity(rampEnt);
		}
	};
	bool mRamp[MAX_MAPSIZE][MAX_MAPSIZE];
	typedef std::map<int, RampEnt*>::iterator RampEntIte;
	std::map<int, RampEnt*> mRampEntList;
};