#pragma once

#include <string>
#include <vector>

#include "squaddefine.h"
#include "Squad.h"

class BattleSquad: public Squad
{
public:
	BattleSquad(std::string path);
	virtual ~BattleSquad();

	virtual bool init(std::string srcpath, int team, int unitnum, int x, int y, enumtype d);
	virtual bool init(std::string srcpath, int team);
	virtual bool init();
public:
	virtual float getAttr(enumtype attrtype , enumtype calctype);

	AttackInfo getAttackRolls(bool rangedattack,bool asdefender, enumtype d);
	void applyAttackRolls(bool rangedattack, enumtype d, AttackInfo &attackinfo);

//ªÒ»° Ù–‘
public:
	int getFaction();
	std::string getFactionId();

	int getUnitGrapNum();

public:
	INTVAL(GridX);
	INTVAL(GridY);
	INTVAL(Direction);
	INTVAL(Formation);

	INTVAL(Team);
	INTVAL(ViewbyPlayer);
	INTVAL(ViewbyEnemy1);
	INTVAL(ViewbyEnemy2);
	INTVAL(ViewbyEnemy3);
	INTVAL(AmbushPlayer);
	INTVAL(AmbushEnemy1);
	INTVAL(AmbushEnemy2);
	INTVAL(AmbushEnemy3);

	INTVAL(UnitMaxNum);
	FLOATVAL(ActionPoint);
};