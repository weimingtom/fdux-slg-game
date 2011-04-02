#include "BattleLoadState.h"

#include "Terrain.h"

#include "BattleState.h"
#include "BattleDeployState.h"

#include "MapDataManager.h"

BattleLoadState::BattleLoadState(BattleState* mainSate, std::string arg)
:SubBattleState(mainSate)
{
	mState = LOADTERRAIN;
	mMapDataManager = new MapDataManager;
	mMapDataManager->loadMapFormFile(arg);
}

BattleLoadState::~BattleLoadState()
{

}

void BattleLoadState::update(unsigned int deltaTime)
{
	switch(mState)
	{
	case LOADTERRAIN:
		mState = LOADOBJECT;
		break;
	case LOADOBJECT:
		mMapDataManager->loadMapObj();
		mState = LOADGRID;
		break;
	case LOADGRID:
		Terrain::getSingleton().createGrid();
		BattleDeployState* deploystate = new BattleDeployState(mMainState);
		mMainState->ChangeState(deploystate);
		break;
	}
}
