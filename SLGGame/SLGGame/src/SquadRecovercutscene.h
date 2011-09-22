#pragma once
#include "cutscene.h"

class SquadGraphics;

class SquadRecoverCutScene:public CutScene
{
public:
	SquadRecoverCutScene(unsigned int squadgpid,int deadnum);
	~SquadRecoverCutScene();
private:
	virtual void startCutScence();
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquad;
	int mRecoverNum;
};