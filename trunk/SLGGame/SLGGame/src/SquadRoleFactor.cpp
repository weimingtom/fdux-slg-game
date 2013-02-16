#include "SquadRoleFactor.h"

#include "BattleSquad.h"

//SquadRolebyTypeFactor
SquadRolebyTypeFactor::SquadRolebyTypeFactor(int squadrole)
:mSquadRole(squadrole)
{

}

float SquadRolebyTypeFactor::calcDecision(BattleSquad* &decision)
{
	int squadtype = decision->getSquadType();
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
	return possibility;
}