#include "ChangeStateCutScene.h"

#include "StateManager.h"

ChangeStateCutScene::ChangeStateCutScene(enumtype nextstate, std::string arg)
:mNextState(nextstate), mArg(arg)
{

}

ChangeStateCutScene::~ChangeStateCutScene( )
{

}

void ChangeStateCutScene::startCutScence()
{
	StateManager::getSingleton().changeState(mArg, StateManager::AVG);
}

bool ChangeStateCutScene::endCutScene()
{
	return true;
}

void ChangeStateCutScene::skipCutScene()
{
	StateManager::getSingleton().changeState(mArg, StateManager::AVG);
}

void ChangeStateCutScene::updateCutScene( unsigned int deltaTime )
{

}
