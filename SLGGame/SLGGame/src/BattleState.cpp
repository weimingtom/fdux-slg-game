#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include "Terrain.h"
#include "MapDataManager.h"
#include "CameraContral.h"
#include "cutscencediretor.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"

BattleState::BattleState(void)
{
}

BattleState::~BattleState(void)
{
}

#include "DelayCutScence.h"
#include "testcloselight.h"
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
		mCameraContral->riseCamera(100);

		DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml");
		mUnitGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
		mUnitGrapManager->createUnit("sinbad",1,1);

	}
	mDirector = new CutScenceDirector();
	mDirector->addCutScence(new DelayCutScence(5000, new TestCloseLight()));
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
	//测试用
	mDirector->update(deltaTime);
}