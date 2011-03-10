#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include "Terrain.h"
#include "MapDataManager.h"
#include "CameraContral.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"

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
	//������ս��
	if(mMapDataManager->loadMap(arg, mTerrain))
	{
		mTerrain = new Terrain();
		mTerrain->createTerrain(mMapDataManager);

		mCameraContral = new CameraContral(mTerrain);
		mCameraContral->resetCamera();
		mCameraContral->moveCamera(-100.0f,-100.0f);

		DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml");
		mUnitGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
		mUnitGrapManager->createUnit("sinbad",1,1);

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

	if (mUnitGrapManager!=NULL)
	{
		delete mUnitGrapManager;
		mUnitGrapManager=NULL;
	}
}

void BattleState::update(unsigned int deltaTime)
{

}