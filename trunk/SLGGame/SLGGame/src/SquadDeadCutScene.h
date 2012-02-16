#pragma once
#include "cutscene.h"

#include <string>

class SquadGraphics;

class SquadDeadCutScene:public CutScene
{
public:
	SquadDeadCutScene(std::string squadgpid,int deadnum);
	~SquadDeadCutScene();
private:
	virtual void startCutScence();
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquad;
	int mDeadNum;
};