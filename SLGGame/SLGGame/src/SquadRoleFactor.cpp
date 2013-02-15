#include "SquadRoleFactor.h"

#include "BattleSquad.h"

//SquadRolebyTypeFactor
SquadRolebyTypeFactor::SquadRolebyTypeFactor(float scale, int squadrole)
:DecisionMapFactor(scale),mSquadRole(squadrole)
{

}

void SquadRolebyTypeFactor::calcDecision(std::vector<DecisionInfo<BattleSquad*>> &decisionVec)
{
	std::vector<DecisionInfo<BattleSquad*>>::iterator decite = decisionVec.begin();
	for( ; decite != decisionVec.end(); decite++)
	{
		int squadtype = (*decite).decision->getSquadType();
		float possibility = 0.0f;
		switch(squadtype)
		{
		case SQUADTYPE_INFANTRY:
			if(mSquadRole & ROLETYPE_MAINFORCE)
				possibility += 100.0f;
			break;
		case SQUADTYPE_MISSILEINFANTRY:
			if(mSquadRole & ROLETYPE_MAINFORCE)
				possibility += 50.0f;
			if(mSquadRole & ROLETYPE_SUPPORT_RANGE)
				possibility += 100.0f;
			break;
		case SQUADTYPE_CAVALRY:
			if(mSquadRole & ROLETYPE_MAINFORCE)
				possibility += 50.0f;
			if(mSquadRole & ROLETYPE_SUPPORT_CLOSE)
				possibility += 75.0f;
			break;
		case SQUADTYPE_MISSILECAVALRY:
			if(mSquadRole & ROLETYPE_SUPPORT_RANGE)
				possibility += 75.0f;
			if(mSquadRole & ROLETYPE_SUPPORT_CLOSE)
				possibility += 75.0f;
			break;
		case SQUADTYPE_SAINT:
			if(mSquadRole & ROLETYPE_MAINFORCE)
				possibility += 100.0f;
			break;
		case SQUADTYPE_BATTLEMAGE:
			if(mSquadRole & ROLETYPE_MAINFORCE)
				possibility += 75.0f;
			if(mSquadRole & ROLETYPE_SUPPORT_CLOSE)
				possibility += 75.0f;
			break;
		case SQUADTYPE_ARCANEMAGE:
			if(mSquadRole & ROLETYPE_SUPPORT_RANGE)
				possibility += 100.0f;
			break;
		}
		if(possibility > 100.0f)
			possibility = 100.0f;
		(*decite).possibility += possibility * mScale;
	}
}