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
				possibility += 18.0f - tgtsquad->getDef(1);
			}
			if(skillrole & ROLETYPE_SUPPORT_RANGE)
			{
				possibility += mSquad->getRangedAtk();
				possibility += 18.0f - mSquad->getDef(0);
				possibility += 18.0f - tgtsquad->getRangedDef();
			}
			if(skillrole & ROLETYPE_SUPPORT_CLOSE)
			{
				possibility += mSquad->getDef(0);
				possibility += mSquad->getAtk(0);
				possibility += 18.0f - tgtsquad->getDef(1);
			}
			if(skillrole & ROLETYPE_ANTI_CAV)
			{
				if(tgtsquad->getSquadType() == SQUADTYPE_CAVALRY || tgtsquad->getSquadType() == SQUADTYPE_MISSILECAVALRY)
					possibility += 30.0f;
			}
			if(skillrole & ROLETYPE_ANTI_HIGHFORM)
			{
				if(tgtsquad->getFormation() != Loose)
				{
					possibility += 5 * (tgtsquad->getAttr(ATTR_FORM, ATTRCALC_FULL) * tgtsquad->getUnitNum() / 50.0f);
				}
			}
			if(skillrole & ROLETYPE_ANTI_MAGE)
			{
				if(tgtsquad->getType() == SQUAD_SPECIAL )
					possibility += 30.0f;
			}
			if(skillrole & ROLETYPE_ANTI_HIGHARMOR)
			{
				if(tgtsquad->getSquadType() == SQUADTYPE_INFANTRY || tgtsquad->getSquadType() == SQUADTYPE_CAVALRY)
					possibility += 30.0f;
			}
		}
	}
	return possibility;
}

//SquadSkillbySptEffectiveFactor
SquadSkillbySptEffectiveFactor::SquadSkillbySptEffectiveFactor(BattleSquad* squad)
:mSquad(squad)
{

}

float SquadSkillbySptEffectiveFactor::calcDecision(UseSkillInfo &decision)
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
		if(tgtsquad->getFaction() == mSquad->getFaction())
		{
			if(skillrole & ROLETYPE_SUPPORT_WOUND)
			{
				possibility += 3 * (tgtsquad->getUnitMaxNum() - tgtsquad->getUnitNum());
			}
			if(skillrole & ROLETYPE_SUPPORT_WAVER)
			{
				std::string eid;
				possibility += 5 * tgtsquad->getEffectLevelByName("Waver", eid);
			}
			if(skillrole & ROLETYPE_SUPPORT_DEF)
			{
				possibility += 4 * (-tgtsquad->getAttr(ATTR_DEFENCE, ATTRCALC_ONLYBONUS));
				possibility += 3 * (18.0f - tgtsquad->getAttr(ATTR_DEFENCE, ATTRCALC_FULL));
			}
			if(skillrole & ROLETYPE_SUPPORT_AP)
			{
				possibility += 4 * (-tgtsquad->getAttr(ATTR_ACTIONPOINT, ATTRCALC_ONLYBONUS));
				possibility += 3 * (10.0f - tgtsquad->getAttr(ATTR_ACTIONPOINT, ATTRCALC_FULL));
			}
		}
	}
	return possibility;
}

//SquadSkillbyRoleFactor
SquadSkillbyRoleFactor::SquadSkillbyRoleFactor(BattleSquad* squad, int role)
:mSquad(squad),mRole(role)
{

}

float SquadSkillbyRoleFactor::calcDecision(UseSkillInfo &decision)
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

		if(skillrole & mRole)
		{
			possibility += 100.0f;
		}
	}
	return possibility;
}