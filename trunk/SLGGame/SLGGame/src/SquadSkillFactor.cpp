#include "SquadSkillFactor.h"

#include "BattleSquadManager.h"
#include "BattleSquad.h"

//SquadSkillbyAtkEffectiveFactor
SquadSkillbyAtkEffectiveFactor::SquadSkillbyAtkEffectiveFactor(BattleSquad* squad)
:mSquad(squad)
{

}

float SquadSkillbyAtkEffectiveFactor::calcDecision(UseSkillInfo &decision)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	float possibility = 0.0f;
	if(decision.skillid != "none")
	{
		BattleSquad* tgtsquad = 
			squadmgr->getBattleSquadAt(decision.targetCrood.mX, decision.targetCrood.mY, mSquad->getFaction(), true);
		if(tgtsquad->getFaction() != mSquad->getFaction())
		{
			possibility += 100.0f;
		}
	}
	return possibility;
}