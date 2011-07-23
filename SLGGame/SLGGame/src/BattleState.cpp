#include "BattleState.h"

#include "Core.h"

#include <ticpp.h>
#include <stdlib.h>
#include "Terrain.h"
#include "DataLibrary.h"
#include "BattleLoadState.h"
#include "SquadGrapManager.h"
#include "BattleSquadManager.h"
#include "StateManager.h"
#include "TriggerManager.h"
#include "GUISystem.h"
#include "AudioSystem.h"

BattleState::BattleState(void)
{
	mSquadGrapManager = SquadGrapManager::getSingletonPtr();
	mEndTrigger = false;
	mIsEnd = false;
	mStateType = 0;
	mArg = "";
}

BattleState::~BattleState(void)
{

}

void BattleState::initialize( std::string arg )
{
	srand((int)time(0));

	BattleLoadState* loadState = new BattleLoadState(arg);
	PushState(loadState);

	TriggerManager::getSingleton().setBattleState(this);

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
	GUISystem::getSingleton().destoryScene(BattleScene);
	TriggerManager::getSingleton().setBattleState(NULL);
	mIsEnd = true;
	if(mSubStateStack.size()>0)
		PopState();
	Terrain::getSingleton().destoryTerrian();
	BattleSquadManager::getSingleton().clear();
	SquadGrapManager::getSingleton().clear();
	DataLibrary::getSingleton().delNode(std::string("GameData/BattleData"));
	AudioSystem::getSingletonPtr()->stopSample();
	AudioSystem::getSingletonPtr()->stopStream(1000);
}

void BattleState::update(unsigned int deltaTime)
{
	if(mSubStateStack.size() > 0)
		mSubStateStack.back()->update(deltaTime);
	mSquadGrapManager->update(deltaTime);
	if(mEndTrigger)
		StateManager::getSingleton().changeState(mArg,StateManager::StateType::AVG);
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
	if(mIsEnd)
		mEndTrigger = true;
	else
		mSubStateStack.back()->reactiveState();
}

void BattleState::setNextState(int statetype, std::string arg)
{
	mIsEnd = true;
	mStateType = statetype;
	mArg = arg;
}