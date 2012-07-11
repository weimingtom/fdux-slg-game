#include "SupplyState.h"

#include "GUISystem.h"
#include "GUIScene.h"

#include "MapLoader.h"

SupplyState::SupplyState()
{

}

SupplyState::~SupplyState()
{

}

void SupplyState::initialize( std::string arg )
{

	GUIScene* supplyScene=GUISystem::getSingletonPtr()->createScene(SupplyScene);

	supplyScene->showScene(arg);
}

void SupplyState::uninitialize()
{
	GUISystem::getSingletonPtr()->destoryScene(SupplyScene);
}

void SupplyState::update( unsigned int deltaTime )
{

}
