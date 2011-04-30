#include "BattlePlayerState.h"

#include "GUISystem.h"
#include "GUIBattle.h"
#include "Core.h"
#include "InputControl.h"
#include "GUISquadWindows.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CameraContral.h"
#include "GUIGameStateWindows.h"

BattlePlayerState::BattlePlayerState()
{
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mCameraContral = CameraContral::getSingletonPtr();
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	Core::getSingleton().mInputControl->pushListener(this);
	mSquadWindow = static_cast<GUISquadWindows *>(mGUIBattle->getSubWindow("SquadWindow"));
	mSquadWindow->setSquad(NULL);
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	newTurn();
	mGUIState->setAllowNextTurn(true);
}
BattlePlayerState::~BattlePlayerState()
{
	Core::getSingleton().mInputControl->popListener();
	mSquadWindow->setSquad(NULL);
	mGUIState->setAllowNextTurn(false);
}

void BattlePlayerState::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	if(mMouseX < 20)
		dx = -1.0f;
	if(mMouseX > 1260)
		dx = 1.0f;
	if(mMouseY < 20)
		dy = -1.0f;
	if(mMouseY > 680)
		dy = 1.0f;
	mCameraContral->moveCamera(dx,dy);
}

bool BattlePlayerState::keyPressed(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattlePlayerState::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattlePlayerState::mouseMoved(const OIS::MouseEvent &arg)
{
	mMouseX = arg.state.X.abs;
	mMouseY = arg.state.Y.abs;
	mGUIBattle->SceneInputEvent(arg.state.X.abs,arg.state.Y.abs);
	return true;
}

bool BattlePlayerState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}

bool BattlePlayerState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}

void BattlePlayerState::newTurn()
{
	for(int n = 0; n < mSquadManager->mSquadList.size(); n++)
	{
		if(mSquadManager->mSquadList[n]->getTeam() == 1)
			mSquadManager->mSquadList[n]->newTurn();
	}
}