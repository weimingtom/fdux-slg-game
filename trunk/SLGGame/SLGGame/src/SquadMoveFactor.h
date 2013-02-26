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
	Crood mCloseCrood;
	std::map<int, BattleSquadManager::MoveNode>* mArea;
	std::map<int, BattleSquadManager::MoveNode>* mPath;
};

class HighTerrainAttrFactor: public DecisionMapFactor<Crood>
{
public:
	HighTerrainAttrFactor(int attrtype);
	
	virtual float calcDecision(Crood &crood);
private:
	int mAttrType;
};

class CloseToEnemyFactor: public DecisionMapFactor<Crood>
{
public:
	CloseToEnemyFactor(int faction, bool avoidsurround);

	virtual float calcDecision(Crood &crood);
private:
	int mFaction;
	bool mAvoidSurround;
};