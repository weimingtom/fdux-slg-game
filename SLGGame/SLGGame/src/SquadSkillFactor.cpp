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
		std::string skillpath = std::string("StaticData/SkillData/")+ decision.skillid;
		int skilltype;
		datalib->getData(skillpath + "/Type",skilltype);
		int skillrole;
		datalib->getData(skillpath + "/SkillRole",skillrole);
		BattleSquad* tgtsquad = 
			squadmgr->getBattleSquadAt(decision.targetCrood.mX, decision.targetCrood.mY, mSquad->getFaction(), true);
		if(tgtsquad->getFaction() != mSquad->getFaction())
		{
			if(skillrole & ROLETYPE_MAINFORCE)
			{
				possibility += mSquad->getDef(0);
				possibility += mSquad->getAtk(0);
				possibility += 15.0f - tgtsquad->getDef(1);
			}
			if(skillrole & ROLETYPE_SUPPORT_RANGE)
			{
				possibility += mSquad->getRangedAtk();
				possibility += 15.0f - mSquad->getDef(0);
				possibility += 15.0f - tgtsquad->getRangedDef();
			}
			if(skillrole & ROLETYPE_SUPPORT_CLOSE)
			{
				possibility += mSquad->getDef(0);
				possibility += mSquad->getAtk(0);
				possibility += 15.0f - tgtsquad->getDef(1);
			}
		}
	}
	return possibility;
}