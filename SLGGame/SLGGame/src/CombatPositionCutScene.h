#pragma once

#include "cutscene.h"
#include "squaddefine.h"

#include <string>

class SquadGraphics;

class CombatPositionCutScene:public CutScene
{
public:
	CombatPositionCutScene(std::string id, Direction direction, bool isBack);
	virtual ~CombatPositionCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	bool mIsBack;
	SquadGraphics* mSquadGraphics;
	Direction mDirection;
};
