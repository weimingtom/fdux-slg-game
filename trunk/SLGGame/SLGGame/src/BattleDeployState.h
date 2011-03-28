#pragma once

#include "SubBattleState.h"
#include "InputListener.h"

class CameraContral;

class BattleDeployState:public SubBattleState, public InputListener
{
public:
	BattleDeployState(BattleState* mainState);
	~BattleDeployState();

	virtual void update(unsigned int deltaTime);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
private:
	CameraContral* mCameraContral;

	int mMouseX;
	int mMouseY;
};