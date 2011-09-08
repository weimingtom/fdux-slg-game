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

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/GameState",std::string("Battle"));

	BattleLoadState* loadState = new BattleLoadState(arg);
	PushState(loadState);

	TriggerManager::getSingleton().setBattleState(this);
	
}

void BattleState::uninitialize()
{
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
	GUISystem::getSingleton().destoryScene(BattleScene);
	//DataLibrary::getSingletonPtr()->setData("GameData/StoryData/GameState",std::string("AVG"));
	//Core::getSingleton().mRoot->renderOneFrame(0.0f);
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