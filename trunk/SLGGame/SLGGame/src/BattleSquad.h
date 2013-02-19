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

	virtual bool init(std::string srcpath, int team, int unitnum, int x, int y, int d);
	virtual bool init(std::string srcpath, int team);
	virtual bool init();
public:
	virtual float getAttr(int attrtype , int calctype);

	float getRangedAtk();
	float getAtk(int side);
	AttackInfo getAttackRolls(bool rangedattack,bool asdefender, int d);
	float getRangedDef();
	float getDef(int side);
	void applyAttackRolls(bool rangedattack, int d, AttackInfo &attackinfo);

	//移动
	bool tryMove(int srcx, int srcy, int tgx, int tgy, float &apleft, unsigned int &eventflag);
	bool move(int tgx, int tgy, unsigned int &eventflag);
	//阵型
	bool changeFormation(int formation, bool costap);
	//技能
	bool useSkillOn(BattleSquad* targetsquad, std::string skillid);
	bool useSkillAt(int x, int y, std::string skillid);

	//粒子特效(数据)
	bool addParticle(std::string particlename, int object, std::string &particleid);
	void removeParticle(std::string particleid);

	//各种触发器 
public:
	void turnStart();
	void turnEnd();
	void onMeleeAttack(BattleSquad* targetsquad, bool asdefender = false);
	void afterMeleeAttack(BattleSquad* targetsquad, bool asdefender = false);
	void onCharge();
	void afterCharge();
	void moveIn(int srcx, int srcy, int tgx, int tgy);

	//获取属性
public:
	int getFaction();
	std::string getFactionId();

	bool getViewByFaction(int faction);
	void setViewByFaction(int faction, bool view);

	bool getAmbushFaction(int faction);
	void setAmbushFaction(int faction, bool ambush);

	int getUnitGrapNum();

	float getSquadStrength();

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
	SkillState canChangeFormation(int formation);
	SkillState canUseSkill(std::string skillid);

	float getChangeFormationApCost(int formation);
	float getSkillApCost(std::string skillid);

	float getAPTypeCostModify(int aptype);
	void setAPTypeCostModify(int aptype, float val);

	void setUnitNum(int val); //重载Squad::setUnitNum
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