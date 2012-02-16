#pragma once
#include "cutscene.h"

#include <string>

class SquadGraphics;

class DefenseCutScene:public CutScene
{
public:
	DefenseCutScene(std::string attackID, std::string defenseID, unsigned int defenseDeadCount);
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