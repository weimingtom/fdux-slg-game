#pragma once
#include "cutscene.h"

class SquadGraphics;

class SquadDeadCutScene:public CutScene
{
public:
	SquadDeadCutScene(unsigned int squadgpid,int deadnum);
	~SquadDeadCutScene();
private:
	virtual void startCutScence();
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquad;
	int mDeadNum;
};