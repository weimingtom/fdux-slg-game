#include "BattlePlayerState.h"

#include "InputControl.h"
#include "CameraContral.h"

#include "DataLibrary.h"
#include "StringTable.h"

#include "GUISystem.h"
#include "GUIBattle.h"
#include "GUIGameStateWindows.h"
#include "GUIMenuWindow.h"
#include "GUIInfoWindow.h"
#include "GUISquadWindows.h"

#include "Terrain.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"

BattlePlayerState::BattlePlayerState(bool newturn)
{
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUISystem::getSingletonPtr()->setFrameUpdateScene(BattleScene);
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	mGUIState->setAllowNextTurn(true);
	mGUIMenu=static_cast<GUIMenuWindow *>(GUISystem::getSingleton().createScene(MenuWindowsScene));
	mGUIMenu->hideScene();
	mGUISquad = static_cast<GUISquadWindows *>(mGUIBattle->getSubWindow("SquadWindow"));
	mGUISquad->setSquad(NULL);
	GUIInfoWindow* infoWindow=(GUIInfoWindow*)mGUIBattle->getSubWindow("InfoWindow");
	infoWindow->setCaption(StringTable::getSingletonPtr()->getString("PlayerTurn"),MyGUI::Colour::White);
	infoWindow->showScene("");

	Core::getSingleton().mInputControl->pushListener(this);
	mMouseX = 640;
	mMouseY = 360;

	mCameraContral = CameraContral::getSingletonPtr();

	mControlState = PLAYERCONTROL_NONE;

	mSelectSquad = NULL;

	if(newturn)
		newTurn();
}
BattlePlayerState::~BattlePlayerState()
{
	Core::getSingleton().mInputControl->popListener();
}

void BattlePlayerState::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	float dt = (float)deltaTime / 5.0f;
	if(mMouseX < 20)
		dx = -dt;
	if(mMouseX > 1260)
		dx = dt;
	if(mMouseY < 20)
		dy = -dt;
	if(mMouseY > 680)
		dy = dt;
	mCameraContral->moveCamera(dx,dy);
}

bool BattlePlayerState::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key==OIS::KC_ESCAPE )
	{
		switch(mControlState)
		{
		case PLAYERCONTROL_NONE:
			mGUIMenu->setAllowSave(true);
			mGUIMenu->showScene("");
			mControlState = PLAYERCONTROL_MENU;
			break;
		case PLAYERCONTROL_CHOOSESKILL:
			mSelectSquad = NULL;
			mGUISquad->setSquad(NULL);
			mControlState = PLAYERCONTROL_NONE;
			break;
		case PLAYERCONTROL_CHOOSETARGET:
			mControlState = PLAYERCONTROL_CHOOSESKILL;
			break;
		case PLAYERCONTROL_MENU:
			mGUIMenu->hideScene();
			mControlState = PLAYERCONTROL_NONE;
			break;
		}
		return true;
	}
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
	return false;
}
bool BattlePlayerState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	int GX,GY;
	Terrain::getSingletonPtr()->coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
	if(id == OIS::MB_Left)
	{
		switch(mControlState)
		{
		case PLAYERCONTROL_NONE:
			{
				BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquadAt(GX,GY,true);
				if(squad)
				{
					if(squad ->getTeam() == 1)
					{
						mSelectSquad = squad;
						mGUISquad->setSquad(mSelectSquad);
						mControlState = PLAYERCONTROL_CHOOSESKILL;
					}
				}
			}
			break;
		case PLAYERCONTROL_CHOOSESKILL:
			{
				BattleSquad* squad = BattleSquadManager::getSingleton().getBattleSquadAt(GX,GY,true);
				if(squad)
				{
					if(squad!= mSelectSquad && squad ->getTeam() == 1)
					{
						mSelectSquad = squad;
						mGUISquad->setSquad(mSelectSquad);
					}
				}
			}
			break;
		case PLAYERCONTROL_CHOOSETARGET:
			mControlState = PLAYERCONTROL_CHOOSESKILL;
			break;
		case PLAYERCONTROL_MENU:
			break;
		}
		return true;
	}
	else if(id == OIS::MB_Right)
	{
		switch(mControlState)
		{
		case PLAYERCONTROL_NONE:
			break;
		case PLAYERCONTROL_CHOOSESKILL:
			break;
		case PLAYERCONTROL_CHOOSETARGET:
			break;
		case PLAYERCONTROL_MENU:
			break;
		}
		return true;
	}
	return false;
}
bool BattlePlayerState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}

void BattlePlayerState::newTurn()
{

}