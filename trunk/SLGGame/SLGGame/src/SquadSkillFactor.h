#pragma once

#include "DecisionMapFactor.h"

#include "Area.h"

class BattleSquad;

struct UseSkillInfo
{
	std::string skillid;
	Crood targetCrood;
};

class SquadSkillbyAtkEffectiveFactor: public DecisionMapFactor<UseSkillInfo>
{
public:
	SquadSkillbyAtkEffectiveFactor(BattleSquad* squad);

	virtual float calcDecision(UseSkillInfo &decision);
private:
	BattleSquad* mSquad;
};

class SquadSkillbySptEffectiveFactor: public DecisionMapFactor<UseSkillInfo>
{
public:
	SquadSkillbySptEffectiveFactor(BattleSquad* squad);

	virtual float calcDecision(UseSkillInfo &decision);
private:
	BattleSquad* mSquad;
};

class SquadSkillbyRoleFactor: public DecisionMapFactor<UseSkillInfo>
{
public:
	SquadSkillbyRoleFactor(BattleSquad* squad, int role);

	virtual float calcDecision(UseSkillInfo &decision);
private:
	BattleSquad* mSquad;
	int mRole;
};