#pragma once

#include <string>
#include <vector>

#include "squaddefine.h"
#include "Squad.h"

class SquadGraphics;

class BattleSquad: public Squad
{
public:
	BattleSquad(std::string id, int grapid,int x, int y);

public:
	void setCrood(int x, int y);
	void getCrood(int* x, int* y);

	void setDirection(Direction d);
	Direction getDirection();

	void setFormation(Formation f);
	Formation getFormation();

	std::string getSquadName();
	std::string getFactionId();
	int getGrapId() { return mGrapId; }

	float getAttr(enumtype attrtype, enumtype calctype, Direction direction);

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

	enumtype getType();

	void OnEliminated();
	void OnTurnEnd();

	bool IsEliminated() {return mIsEliminated;}

	static int getTeamFaction(int team);
private:
	int mX;
	int mY;
	int mGrapId;
	int mTeam;
	bool mIsEliminated;

	float mCovert;
	float mDetection;
	bool mViewbyFaction[4];
	bool mAmbushFaction[4];

//ÐÂ°æ½Ó¿Ú
public:
	BattleSquad(std::string path, std::string srcpath, int team, int unitnum, int x, int y, enumtype d);
	BattleSquad(std::string path, std::string srcpath, int team);
	BattleSquad(std::string path);
	virtual ~BattleSquad();

public:
	virtual float getAttr(enumtype attrtype , enumtype calctype);

	AttackInfo getAttackRolls(bool rangedattack,bool asdefender, Direction d);
	void applyAttackRolls(bool rangedattack, Direction d, AttackInfo &attackinfo);
};