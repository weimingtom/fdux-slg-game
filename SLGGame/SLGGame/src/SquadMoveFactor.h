#pragma once

#include "DecisionMapFactor.h"

#include "BattleSquadManager.h"
#include "Area.h"

class BattleSquad;

class SquadMoveClosetoPathFactor: public DecisionMapFactor<Crood>
{
public:
	SquadMoveClosetoPathFactor(std::map<int, BattleSquadManager::MoveNode>* area,
		std::map<int, BattleSquadManager::MoveNode>* path);

	virtual float calcDecision(Crood &decision);
private:
	float mClose;
	float mHighAP;
	std::map<int, BattleSquadManager::MoveNode>* mArea;
	std::map<int, BattleSquadManager::MoveNode>* mPath;
};