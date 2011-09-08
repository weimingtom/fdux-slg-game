#pragma once

#include <string>
#include <vector>

#include "squaddefine.h"

class BattleSquad
{
public:
	BattleSquad(std::string id, int grapid,int x, int y);
	~BattleSquad();

	std::string getId() {return mId;}

	std::string getPath();

	void setCrood(int x, int y);
	void getCrood(int* x, int* y);

	void setDirection(Direction d);
	Direction getDirection();

	void setFormation(Formation f);
	Formation getFormation();

	std::string getSquadName();
	std::string getFactionId();
	int getGrapId() { return mGrapId; }

	float getAttr(AttrType attrtype, AttrCalcType calctype, Direction direction);

	float getMoraleBonse();
	void modifyMorale(int m);

	int getUnitGrapNum();
	int getUnitRealNum();

	void newTurn();
	int getTeam();

	bool viewbyTeam(int team);
	void setViewbyTeam(int team, bool view);

	bool ambushTeam(int team);
	void setAmbushTeam(int team, bool ambush);

	float getActionPoint();
	float getActionPointCost(int type);

	SquadType getType();

	AttackInfo getAttackRolls(bool rangedattack,bool asdefender, Direction d);
	void applyAttackRolls(bool rangedattack, Direction d, AttackInfo &attackinfo);

	void OnEliminated();
	void OnTurnEnd();

	bool IsEliminated() {return mIsEliminated;}

	static int getTeamFaction(int team);
private:
	int mX;
	int mY;
	int mGrapId;
	int mTeam;
	std::string mId;
	bool mIsEliminated;

	float mCovert;
	float mDetection;
	bool mViewbyFaction[4];
	bool mAmbushFaction[4];
};