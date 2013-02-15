#pragma once

#include "DecisionMapFactor.h"

#include "Area.h"

class BattleSquad;

class SquadRolebyTypeFactor: public DecisionMapFactor<BattleSquad*>
{
public:
	SquadRolebyTypeFactor(float scale, int squadrole);

	virtual void calcDecision(std::vector<DecisionInfo<BattleSquad*>> &decisionVec);
private:
	int mSquadRole;
};