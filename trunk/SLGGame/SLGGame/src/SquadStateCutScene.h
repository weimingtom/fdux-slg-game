#pragma once

#include <string>

#include "cutscene.h"
#include "squaddefine.h"

class BattleSquad;
class SquadGraphics;

typedef unsigned short SquadStateType;
const SquadStateType SQUAD_STATE_VISIBLE  = 0;
const SquadStateType SQUAD_STATE_PARTICLE = 1;


class SquadStateCutScene:public CutScene
{
public:
	SquadStateCutScene(BattleSquad* battlesquad, SquadStateType type, std::string stateid ,int val);
	~SquadStateCutScene(void);

protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	BattleSquad* mSquad;
	SquadGraphics* mSquadGraphics;
	SquadStateType mStateType;
	int mStateValue;
	std::string mStateId;
};
