#include "BattleAvgState.h"

#include "GUISystem.h"
#include "LuaSystem.h"

#include "BattleState.h"

BattleAvgState::BattleAvgState(BattleState* mainState,std::string arg):SubBattleState(mainState)
{
	GUISystem::getSingletonPtr()->createScene(StageScene);
	LuaSystem::getSingletonPtr()->registerListener(this);
	LuaSystem::getSingletonPtr()->runScriptFromFile(arg,0);
}

BattleAvgState::~BattleAvgState(void)
{
	LuaSystem::getSingletonPtr()->registerListener(NULL);
	GUISystem::getSingletonPtr()->destoryScene(StageScene);
}

void BattleAvgState::update( unsigned int deltaTime )
{

}

void BattleAvgState::onError( std::string error )
{

}

void BattleAvgState::onComplete()
{
	this->mMainState->PopState();
}
