#include "BattleLoadState.h"

#include "Terrain.h"

#include "BattleState.h"
#include "BattleDeployState.h"
#include "LoadScene.h"
#include "BattleSquadManager.h"
#include "DataLibrary.h"

#include "MapDataManager.h"

BattleLoadState::BattleLoadState( std::string arg)
{
	mState = LOADSCENE;
	mLoadFromMap =true;
	mMapFile = arg;
	mLoadScene = static_cast<LoadScene*>(GUISystem::getSingleton().createScene(LoadingScene));
	mMapDataManager = MapDataManager::getSingletonPtr();
}

BattleLoadState::~BattleLoadState()
{
	GUISystem::getSingleton().destoryScene(LoadingScene);
}

void BattleLoadState::update(unsigned int deltaTime)
{
	switch(mState)
	{
	case LOADSCENE:
		mState = LOADTERRAIN;
		mLoadScene->setText("Loading Terrain");
		break;
	case LOADTERRAIN:
		if(mLoadFromMap)
			mMapDataManager->loadMapFormFile(mMapFile);
		Core::getSingleton().mRoot->renderOneFrame(0.0f);
		mState = LOADOBJECT;
		mLoadScene->setProgress(25);
		mLoadScene->setText("Loading MapObject");
		break;
	case LOADOBJECT:
		mMapDataManager->loadMapObj();
		mState = LOADUNIT;
		mLoadScene->setProgress(50);
		mLoadScene->setText("Loading Unit");
		break;
	case LOADUNIT:
		BattleSquadManager::getSingleton().initBattleSquad(true);
		mState = LOADGRID;
		mLoadScene->setProgress(75);
		mLoadScene->setText("Creating Grid");
		break;
	case LOADGRID:
		Terrain::getSingleton().createGrid();
		BattleDeployState* deploystate = new BattleDeployState;
		DataLibrary::getSingleton().saveXmlData(DataLibrary::GameData,"test.xml");
		mLoadScene->setProgress(100);
		mLoadScene->setText("Finish");
		mMainState->ChangeState(deploystate);
		break;
	}
}
