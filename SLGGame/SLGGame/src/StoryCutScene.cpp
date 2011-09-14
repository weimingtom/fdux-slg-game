#include "StoryCutScene.h"

#include "StateManager.h"

StoryCutScene::StoryCutScene( std::string scriptName ):mScriptName(scriptName)
{

}

StoryCutScene::~StoryCutScene( void )
{

}

void StoryCutScene::startCutScence()
{
	StateManager::getSingletonPtr()->addAffixationState(mScriptName+".StoryInit",StateManager::AVG);
}

bool StoryCutScene::endCutScene()
{
	return !StateManager::getSingletonPtr()->hasAffixationState();
}

void StoryCutScene::skipCutScene()
{
	StateManager::getSingletonPtr()->removeAffixationState();
}

void StoryCutScene::updateCutScene( unsigned int deltaTime )
{

}
