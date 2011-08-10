#include "RampManager.h"

RampManager::RampManager(int blockSize,int gridSize)
{
	mBlockSize = blockSize;
	mMapSize = gridSize;
	memset(mRamp, 0, sizeof(bool) * MAX_MAPSIZE * MAX_MAPSIZE);
}

RampManager::~RampManager()
{
	RampEntIte ite;
	for(ite = mRampEntList.begin();ite!=  mRampEntList.end(); ite++)
	{
		delete ite->second;
	}
}

void RampManager::setRamp(int x,int y)
{
	if(!mRamp[x][y])
	{
		mRamp[x][y] = true;
		RampEnt* newent = new RampEnt;
		newent->rampNode = IIRoot::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
		newent->rampEnt = IIRoot::getSingleton().mSceneMgr->createEntity("Cube.mesh");
		newent->rampEnt->setMaterialName("CUBE_BLUE");
		newent->rampNode->attachObject(newent->rampEnt);
		float xx = x * mBlockSize - mMapSize * mBlockSize / 2.0f + mBlockSize /2.0f;
		float yy = y * mBlockSize - mMapSize * mBlockSize / 2.0f + mBlockSize /2.0f;
		newent->rampNode->setPosition(xx,0.0f,yy);
		mRampEntList.insert(std::map<int, RampEnt*>::value_type(x + y * MAX_MAPSIZE, newent));
		
	}
}
void RampManager::removeRamp(int x,int y)
{
	if(mRamp[x][y])
	{
		RampEntIte ite;
		ite = mRampEntList.find(x + y * MAX_MAPSIZE);
		delete ite->second;
		mRampEntList.erase(ite);
		mRamp[x][y] = false;
	}
}

bool RampManager::isRamp(int x,int y)
{
	return mRamp[x][y];
}