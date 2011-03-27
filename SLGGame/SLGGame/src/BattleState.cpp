#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include <stdlib.h>
#include "Terrain.h"

#include "BillboardManager.h"

#include "GUISystem.h"

#include "InputControl.h"

#include "BattleLoadState.h"

BattleState::BattleState(void)
{

}

BattleState::~BattleState(void)
{

}

void BattleState::initialize( std::string arg )
{
	mTerrain = new Terrain();
	srand((int)time(0));
	new BillboardManager();

	BattleLoadState* loadState = new BattleLoadState(this,arg);
	PushState(loadState);

	//载入新战场
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
		s=mSquadGrapManager->createSquad("NinjaSquad",2,8,8,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",3,10,9,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",4,10,8,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",5,9,9,SquadGrapManager::North,SquadGrapManager::Loose);
		//s=mSquadGrapManager->createSquad("NinjaSquad",6,9,8,SquadGrapManager::North,SquadGrapManager::Loose);

		s->setEffect("Seal/mp_seal_01",SquadGraphics::Commander);
//		std::cout<<mTerrain->getHeight(96,-144)<<std::endl;
		
	}
	GUIPUDebug* puDebug=(GUIPUDebug*)GUISystem::getSingletonPtr()->createScene(PUDebugScene);
	//puDebug->mDirector = mDirector;
	*/
	
}

void BattleState::uninitialize()
{
	if(mTerrain != NULL)
	{
		mTerrain->destoryTerrian();
		//delete mTerrain;
		//mTerrain = NULL;
	}

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
	mSubStateStack.push_back(substate);

}
void BattleState::PushState(SubBattleState* substate)
{
	mSubStateStack.push_back(substate);
}
void BattleState::PopState()
{
	SubBattleState* ite = mSubStateStack.back();
	delete ite;
	mSubStateStack.pop_back();
}