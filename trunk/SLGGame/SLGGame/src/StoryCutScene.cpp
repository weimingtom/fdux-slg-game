#include "StoryCutScene.h"

#include "GUIBattle.h"
#include "StateManager.h"

StoryCutScene::StoryCutScene( std::string scriptName ):mScriptName(scriptName)
{

}

StoryCutScene::~StoryCutScene( void )
{
	if(mStarted)
	{
		GUIBattle* mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
		mGUIBattle->showAllWindows();
	}
}

void StoryCutScene::startCutScence()
{
	GUIBattle* mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	mGUIBattle->hideAllWindows();
	mCanSkip=false;
	
	StateManager::getSingletonPtr()->addAffixationState(mScriptName+".StoryInit",StateManager::AVG);
}

bool StoryCutScene::endCutScene()
{
	return !StateManager::getSingletonPtr()->hasAffixationState();
}

void StoryCutScene::skipCutScene()
{
	//StateManager::getSingletonPtr()->removeAffixationState();
}

void StoryCutScene::updateCutScene( unsigned int deltaTime )
{

}
