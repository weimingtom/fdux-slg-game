#include "BattleState.h"

#include <ticpp.h>
#include "Terrain.h"
#include "MapDataManager.h"

BattleState::BattleState(void)
{
}

BattleState::~BattleState(void)
{
}

void BattleState::initialize( std::string arg )
{
	mMapDataManager = new MapDataManager(); 
	//载入新战场
	if(mMapDataManager->loadMap(arg))
	{
		mTerrain = new Terrain();
		mTerrain->createTerrain(mMapDataManager);

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