#pragma once

#include "DecisionMapFactor.h"

#include "Area.h"

class BattleSquad;

class SquadRolebyTypeFactor: public DecisionMapFactor<BattleSquad*>
{
public:
	SquadRolebyTypeFactor(int squadrole);

	virtual float calcDecision(BattleSquad* &decision);
private:
	int mSquadRole;
};