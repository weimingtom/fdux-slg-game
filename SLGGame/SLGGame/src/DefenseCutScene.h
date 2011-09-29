#pragma once
#include "cutscene.h"

class SquadGraphics;

class DefenseCutScene:public CutScene
{
public:
	DefenseCutScene(unsigned int attackID,unsigned int defenseID,unsigned int defenseDeadCount);
	~DefenseCutScene();
protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mAttackSG;
	SquadGraphics* mDefenseSG;
	unsigned int mDeadCount;

};