#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include <stdlib.h>
#include "Terrain.h"

#include "BillboardManager.h"

#include "BattleLoadState.h"
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
	srand((int)time(0));
	new BillboardManager();

	BattleLoadState* loadState = new BattleLoadState(arg);
	PushState(loadState);

	//������ս��
	/*
	if(mMapDataManager->loadMap(arg, mTerrain))
	{
		mCameraContral = new CameraContral(mTerrain);
		mCameraContral->resetCamera();
		mCameraContral->moveCamera(0.0f,0.0f);
		mCameraContral->riseCamera(50.0f);

		Core::getSingletonPtr()->mInputControl->setCameraContral(mCameraContral);

		DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml",true);
		mSquadGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
		SquadGraphics* s;//=mSquadGrapManager->createSquad("SinbadSquad",1,10,10,SquadGrapManager::North,SquadGrapManager::Loose);
		s=mSquadGrapManager->createSquad("NinjaSquad",1,10,10,SquadGrapManager::North,SquadGrapManager::Loose);
		s=mSquadGrapManager->createSquad("NinjaSquad",2,8,8,SquadGrapManager::North,SquadGrapManager::Loose);
		s=mSquadGrapManager->createSquad("NinjaSquad",3,10,9,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",4,10,8,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",5,9,9,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",6,9,8,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",7,8,9,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",8,8,10,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",9,8,11,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",10,8,12,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",11,8,13,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",12,9,14,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",13,9,13,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",14,9,12,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",15,9,11,SquadGrapManager::North,SquadGrapManager::Loose);


		//s->setEffect("Seal/mp_seal_01",SquadGraphics::Commander);
//		std::cout<<mTerrain->getHeight(96,-144)<<std::endl;
		
	}
	GUIPUDebug* puDebug=(GUIPUDebug*)GUISystem::getSingletonPtr()->createScene(PUDebugScene);
	//puDebug->mDirector = mDirector;
	*/
	
}

void BattleState::uninitialize()
{
	Terrain::getSingleton().destoryTerrian();
	MapDataManager::getSingleton().clearMap();
	/*
	if(mTerrain != NULL)
	{
		
		mTerrain->destoryTerrian();
		//delete mTerrain;
		//mTerrain = NULL;
	}
	*/

	//GUISystem::getSingletonPtr()->destoryScene(PUDebugScene);
}

void BattleState::update(unsigned int deltaTime)
{
	mSubStateStack.back()->update(deltaTime);
}

void BattleState::ChangeState(SubBattleState* substate)
{
	if(substate == NULL)
		return;
	if(mSubStateStack.size() > 0)
	{
		SubBattleState* ite = mSubStateStack.back();
		delete ite;
		mSubStateStack.pop_back();
	}
	substate->setMainState(this);
	mSubStateStack.push_back(substate);

}
void BattleState::PushState(SubBattleState* substate)
{
	substate->setMainState(this);
	mSubStateStack.push_back(substate);
}
void BattleState::PopState()
{
	SubBattleState* ite = mSubStateStack.back();
	delete ite;
	mSubStateStack.pop_back();
}