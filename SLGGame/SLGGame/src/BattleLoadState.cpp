#include "BattleLoadState.h"

#include "Terrain.h"
#include "InputControl.h"

#include "BattleState.h"
#include "BattleDeployState.h"
#include "LoadScene.h"
#include "BattleSquadManager.h"
#include "DataLibrary.h"
#include "GUIBattle.h"
#include "MapLoader.h"
#include "StringTable.h"
#include "DataLibrary.h"

#include "MapDataManager.h"

BattleLoadState::BattleLoadState( std::string arg)
{
	Core::getSingleton().mInputControl->pushListener(this);
	mState = LOADSCENE;
	mLoadFromMap =true;
	mMapFile = arg;
	mLoadScene = static_cast<LoadScene*>(GUISystem::getSingleton().createScene(LoadingScene));
	mMapLoader = new MapLoader;
	mIsPressKey=false;
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
		if(mLoadFromMap)
		{
			mMapLoader->loadMapFormFile(mMapFile);
			std::string temp;
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapLoadBG",temp);
			mLoadScene->setBackGround(temp);
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapName",temp);
			mLoadScene->setMapName(temp);
			DataLibrary::getSingletonPtr()->getData("GameData/BattleData/MapData/MapInfo",temp);
			mLoadScene->setMapInfo(temp);
		}
		mLoadScene->setText(StringTable::getSingletonPtr()->getString("LoadingTerrain"));
		break;
	case LOADTERRAIN:
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
		{
			if(mLoadFromMap)
				mMapLoader->initMapScript();
			Terrain::getSingleton().createGrid();
			GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().createScene(BattleScene));
			guibattle->setBattleState(mMainState);
			mState=LOADFINISH;
			mLoadScene->setProgress(100);
			mLoadScene->setText(StringTable::getSingletonPtr()->getString("Finish"));
			mLoadScene->isStartCheck=true;
			break;
		}
	case LOADFINISH:
		if (mIsPressKey || mLoadScene->isClick)
		{
			Core::getSingleton().mInputControl->popListener();
			BattleDeployState* deploystate = new BattleDeployState;
			GUISystem::getSingletonPtr()->destoryScene(LoadingScene);
			mMainState->ChangeState(deploystate);
		}
		break;
	}
}

bool BattleLoadState::keyPressed( const OIS::KeyEvent &arg )
{
	if (mState==LOADFINISH)
	{
		mIsPressKey=true;
		return false;
	}
}

