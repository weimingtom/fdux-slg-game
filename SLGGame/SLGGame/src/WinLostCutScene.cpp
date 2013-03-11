#include "WinLostCutScene.h"

#include "StateManager.h"

WinLostCutScene::WinLostCutScene(bool isWin):mIsWin(isWin)
{

}

WinLostCutScene::~WinLostCutScene( )
{

}

void WinLostCutScene::startCutScence()
{
	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIGameOver* GameOver=(GUIGameOver*)guibattle->getSubWindow("GameOverWindow");
	if(mIsWin)
		GameOver->showScene("win");
	else
		GameOver->showScene("lost");

	if(mNextScene)
		mNextScene->skipall();
}

bool WinLostCutScene::endCutScene()
{
	return true;
}

void WinLostCutScene::skipCutScene()
{
	startCutScence();
}

void WinLostCutScene::updateCutScene( unsigned int deltaTime )
{

}
