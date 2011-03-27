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
	Core::getSingleton().mInputControl->setCameraContral(mCameraContral);
}
BattleDeployState::~BattleDeployState()
{
	Core::getSingleton().mInputControl->setCameraContral(NULL);
}

void BattleDeployState::update(unsigned int deltaTime)
{

}