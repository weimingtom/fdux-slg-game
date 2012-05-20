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
	MapLoader* mMapLoader = new MapLoader;

	mMapLoader->loadMapFormFile("demo.xml");
	//mMapLoader->loadMapObj();
	mMapLoader->initBattleSquad(true);
	//mMapLoader->initMapScript();

	GUIScene* supplyScene=GUISystem::getSingletonPtr()->createScene(SupplyScene);

	supplyScene->showScene("");
}

void SupplyState::uninitialize()
{
	GUISystem::getSingletonPtr()->destoryScene(SupplyScene);
}

void SupplyState::update( unsigned int deltaTime )
{

}
