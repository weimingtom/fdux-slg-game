#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include <stdlib.h>
#include "Terrain.h"
#include "MapDataManager.h"
#include "CameraContral.h"
#include "cutscenediretor.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"

#include "GUISystem.h"
#include "GUIPUDebug.h"

BattleState::BattleState(void)
{
}

BattleState::~BattleState(void)
{
}

#include "DelayCutScene.h"
void BattleState::initialize( std::string arg )
{
	mMapDataManager = new MapDataManager(); 
	mTerrain = new Terrain();
	srand((int)time(0));

	//载入新战场
	if(mMapDataManager->loadMap(arg, mTerrain))
	{
		mCameraContral = new CameraContral(mTerrain);
		mCameraContral->resetCamera();
		mCameraContral->moveCamera(0,0);
		mCameraContral->riseCamera(20);

		DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml");
		mSquadGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
		SquadGraphics* s=mSquadGrapManager->createSquad("SinbadSquad",1,10,10,SquadGrapManager::North,SquadGrapManager::Loose);
		s=mSquadGrapManager->createSquad("NinjaSquad",2,8,8,SquadGrapManager::North,SquadGrapManager::Loose);

		s->setEffect("Seal/mp_seal_01",SquadGraphics::Commander);
		
	}
	mDirector = new CutSceneDirector();
	GUIPUDebug* puDebug=(GUIPUDebug*)GUISystem::getSingletonPtr()->createScene(PUDebugScene);
	puDebug->mDirector =mDirector;
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