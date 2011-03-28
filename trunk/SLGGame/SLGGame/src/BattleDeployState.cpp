#include "BattleDeployState.h"

#include "BattleState.h"

#include "CameraContral.h"

#include "Core.h"

#include "InputControl.h"

BattleDeployState::BattleDeployState(BattleState* mainState)
:SubBattleState(mainState)
{
	mCameraContral = new CameraContral;
	mCameraContral->resetCamera();
	mCameraContral->riseCameraTo(50.0f);
	Core::getSingleton().mInputControl->pushListener(this);
	mMouseX = 640;
	mMouseY = 320;
	//Core::getSingleton().mInputControl->setCameraContral(mCameraContral);
}
BattleDeployState::~BattleDeployState()
{
	//Core::getSingleton().mInputControl->setCameraContral(NULL);
	Core::getSingleton().mInputControl->popListener();
}

void BattleDeployState::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	if(mMouseX < 20)
		dx = -1.0f;
	if(mMouseX > 1260)
		dx = 1.0f;
	if(mMouseY < 20)
		dy = -1.0f;
	if(mMouseY > 700)
		dy = 1.0f;
	mCameraContral->moveCamera(dx,dy);
}

bool BattleDeployState::keyPressed(const OIS::KeyEvent &arg)
{
	return false;
}
bool BattleDeployState::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattleDeployState::mouseMoved(const OIS::MouseEvent &arg)
{
	mMouseX = arg.state.X.abs;
	mMouseY = arg.state.Y.abs;
	return true;
}
bool BattleDeployState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}
bool BattleDeployState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}