#pragma once

#include "SubBattleState.h"

class CameraContral;

class BattleDeployState:public SubBattleState
{
public:
	BattleDeployState(BattleState* mainState);
	~BattleDeployState();

	virtual void update(unsigned int deltaTime);
private:
	CameraContral* mCameraContral;
};