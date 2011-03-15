#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include "Terrain.h"
#include "MapDataManager.h"
#include "CameraContral.h"
#include "cutscencediretor.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"

#include "GUISystem.h"

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
		mCameraContral->moveCamera(0,0);
		mCameraContral->riseCamera(50);
		
		GUISystem::getSingletonPtr()->createScene(PUDebugScene);

		DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml");
		mSquadGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
		SquadGraphics* s=mSquadGrapManager->createUnit("sinbad",1,1);
		s->setEffect("Seal/mp_seal_01",SquadGraphics::Commander);
		//s->setAnimation("IdleTop",SquadGraphics::Squad,true);
		
	}
	mDirector = new CutScenceDirector();
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

	if (mSquadGrapManager!=NULL)
	{
		delete mSquadGrapManager;
		mSquadGrapManager=NULL;
	}

	GUISystem::getSingletonPtr()->destoryScene(PUDebugScene);
}

void BattleState::update(unsigned int deltaTime)
{
	//测试用
	mDirector->update(deltaTime);
	mSquadGrapManager->update(deltaTime);
}