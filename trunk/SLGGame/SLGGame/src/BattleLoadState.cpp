#include "BattleLoadState.h"

#include "Terrain.h"

#include "BattleState.h"
#include "BattleDeployState.h"
#include "LoadScene.h"
#include "BattleSquadManager.h"
#include "DataLibrary.h"
#include "GUIBattle.h"
#include "MapLoader.h"
#include "StringTable.h"

#include "MapDataManager.h"

BattleLoadState::BattleLoadState( std::string arg)
{
	mState = LOADSCENE;
	mLoadFromMap =true;
	mMapFile = arg;
	mLoadScene = static_cast<LoadScene*>(GUISystem::getSingleton().createScene(LoadingScene));
	mMapLoader = new MapLoader;
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
		mLoadScene->setText(StringTable::getSingletonPtr()->getString("LoadingTerrain"));
		break;
	case LOADTERRAIN:
		if(mLoadFromMap)
			mMapLoader->loadMapFormFile(mMapFile);
		Core::getSingleton().mRoot->renderOneFrame(0.0f);
		mState = LOADOBJECT;
		mLoadScene->setProgress(25);
		mLoadScene->setText(StringTable::getSingletonPtr()->getString("LoadingMapObject"));
		break;
	case LOADOBJECT:
		mMapLoader->loadMapObj();
		mState = LOADUNIT;
		mLoadScene->setProgress(50);
		mLoadScene->setText(StringTable::getSingletonPtr()->getString("LoadingUnit"));
		break;
	case LOADUNIT:
		mMapLoader->initBattleSquad(mLoadFromMap);
		mState = LOADGRID;
		mLoadScene->setProgress(75);
		mLoadScene->setText(StringTable::getSingletonPtr()->getString("CreatingGrid"));
		break;
	case LOADGRID:
		if(mLoadFromMap)
			mMapLoader->initMapScript();
		Terrain::getSingleton().createGrid();
		GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().createScene(BattleScene));
		BattleDeployState* deploystate = new BattleDeployState;
		guibattle->setBattleState(mMainState);
		//GUISystem::getSingleton().setFrameUpdateScene(BattleScene);
		mLoadScene->setProgress(100);
		mLoadScene->setText("Finish");
		mMainState->ChangeState(deploystate);
		break;
	}
}
