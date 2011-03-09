#include "BattleState.h"

#include <ticpp.h>
#include "Terrain.h"
#include "MapDataManager.h"
#include "CameraContral.h"

BattleState::BattleState(void)
{
}

BattleState::~BattleState(void)
{
}

void BattleState::initialize( std::string arg )
{
	mMapDataManager = new MapDataManager(); 
	mTerrain = new Terrain();
	//载入新战场
	if(mMapDataManager->loadMap(arg, mTerrain))
	{
		mCameraContral = new CameraContral(mTerrain);
		mCameraContral->resetCamera();
		mCameraContral->moveCamera(-100.0f,-100.0f);
	}
}

void BattleState::uninitialize()
{
	if(mTerrain != NULL)
	{
		mTerrain->destoryTerrian();
		delete mTerrain;
		mTerrain = NULL;
	}
	if(mMapDataManager != NULL)
	{
		delete mMapDataManager;
		mMapDataManager =NULL;
	}
}

void BattleState::update(unsigned int deltaTime)
{

}