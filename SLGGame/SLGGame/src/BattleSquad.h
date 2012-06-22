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

	//移动
	bool tryMove(int srcx, int srcy, int tgx, int tgy, float &apleft, unsigned int &eventflag);
	bool move(int tgx, int tgy, unsigned int &eventflag);
	//阵型
	bool changeFormation(enumtype formation, bool costap);
	//技能
	bool useSkillOn(BattleSquad* targetsquad, std::string skillid);
	bool useSkillAt(int x, int y, std::string skillid);

public:
	void turnStart();
	void turnEnd();
	void onMeleeAttack(BattleSquad* targetsquad);
	void afterMeleeAttack(BattleSquad* targetsquad);

//获取属性
public:
	int getFaction();
	std::string getFactionId();

	bool getViewByFaction(int faction);
	void setViewByFaction(int faction, bool view);

	bool getAmbushFaction(int faction);
	void setAmbushFaction(int faction, bool ambush);

	int getUnitGrapNum();

	struct ActiveSkillInfo
	{
		std::string skillid;
		bool available;
		int apcost;
	};
	std::vector<ActiveSkillInfo> GetActiveSkillList();

	enum SkillState
	{
		SKILLSTATE_NOSKILL = 0,
		SKILLSTATE_NOTAVAILABLE = 1,
		SKILLSTATE_AVAILABLE =2
	};
	SkillState canMove();
	SkillState canChangeFormation(enumtype formation);
	SkillState canUseSkill(std::string skillid);

	float getChangeFormationApCost(enumtype formation);
	float getSkillApCost(std::string skillid);

	float getAPTypeCostModify(enumtype aptype);
	void setAPTypeCostModify(enumtype aptype, float val);

	//重载
	void setUnitNum(int val);
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
	FLOATVAL(APSetup);
	FLOATVAL(APBattle);
};