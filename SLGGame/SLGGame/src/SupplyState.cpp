
#include "SupplyState.h"

#include "GUISystem.h"
#include "GUIScene.h"

#include "MapLoader.h"

#include "DataLibrary.h"

SupplyState::SupplyState()
{

}

SupplyState::~SupplyState()
{

}

void SupplyState::initialize( std::string arg )
{

	GUIScene* supplyScene=GUISystem::getSingletonPtr()->createScene(SupplyScene);

	/*DataLibrary::getSingletonPtr()->setData("GameData/StoryData/GameState",std::string("Supply"));

	std::string next;
	if(arg=="save.xml")
	{
		DataLibrary::getSingletonPtr()->getData("GameData/StoryData/SupplyNextScene",next);
	}
	else
	{
		next=arg;
		DataLibrary::getSingletonPtr()->setData("GameData/StoryData/SupplyNextScene",arg);
	}*/

	supplyScene->showScene("");
}

void SupplyState::uninitialize()
{
	GUISystem::getSingletonPtr()->destoryScene(SupplyScene);
}

void SupplyState::update( unsigned int deltaTime )
{

}
