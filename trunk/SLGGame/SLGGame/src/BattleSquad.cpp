#include "BattleSquad.h"

#include <math.h>
#include <stdio.h>

#include <boost/format.hpp>

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h" 
#include "LuaSystem.h"
#include "CommonFunction.h"

BattleSquad::BattleSquad(std::string path)
:Squad(path)
{

}

BattleSquad::~BattleSquad()
{

}

bool BattleSquad::init(std::string srcpath, int team, int unitnum, int x, int y, enumtype d)
{
	if(!Squad::init(srcpath))
		return false;
	DataLibrary *datalib = DataLibrary::getSingletonPtr();
	setTeam(team);
	setGridX(x);
	setGridY(y);
	setDirection(d);

	setUnitNum(unitnum);
	enumtype squadtype2;
	datalib->getData(srcpath + std::string("/Type"), squadtype2);
	if(squadtype2 == SQUAD_NORMAL)
		setUnitMaxNum(unitnum);
	else
		setUnitMaxNum(20);

	float covert;
	covert = getAttr(ATTR_COVERT, ATTRCALC_FULL);
	if(covert > 0.0f)
	{
		switch(getFaction())
		{
		case 0:
			setViewbyPlayer(1);
			setViewbyEnemy1(0);
			setViewbyEnemy2(0);
			setViewbyEnemy3(0);
			break;
		case 1:
			setViewbyPlayer(0);
			setViewbyEnemy1(1);
			setViewbyEnemy2(0);
			setViewbyEnemy3(0);
			break;
		case 2:
			setViewbyPlayer(0);
			setViewbyEnemy1(0);
			setViewbyEnemy2(1);
			setViewbyEnemy3(0);

			break;
		case 3:
			setViewbyPlayer(0);
			setViewbyEnemy1(0);
			setViewbyEnemy2(0);
			setViewbyEnemy3(1);
			break;
		}
	}
	else
	{
		setViewbyPlayer(1);
		setViewbyEnemy1(1);
		setViewbyEnemy2(1);
		setViewbyEnemy3(1);
	}

	setAmbushPlayer(0);
	setAmbushEnemy1(0);
	setAmbushEnemy2(0);
	setAmbushEnemy3(0);
	return true;
}
bool BattleSquad::init(std::string srcpath, int team)
{
	if(!Squad::init(srcpath))
		return false;
	DataLibrary *datalib = DataLibrary::getSingletonPtr();
	setTeam(team);
	setGridX(-10);
	setGridY(-10);
	setDirection(North);

	int unitnum;
	enumtype squadtype2;
	datalib->getData(srcpath + std::string("/Type"), squadtype2);
	if(squadtype2 == SQUAD_NORMAL)
		datalib->getData(srcpath + std::string("/UnitNum"), unitnum);
	else
		unitnum = 20;
	setUnitNum(unitnum);
	setUnitMaxNum(unitnum);

	float covert;
	covert = getAttr(ATTR_COVERT, ATTRCALC_ONLYBASE);
	if(covert > 0.0f)
	{
		switch(getFaction())
		{
		case 0:
			setViewbyPlayer(1);
			setViewbyEnemy1(0);
			setViewbyEnemy2(0);
			setViewbyEnemy3(0);
			break;
		case 1:
			setViewbyPlayer(0);
			setViewbyEnemy1(1);
			setViewbyEnemy2(0);
			setViewbyEnemy3(0);
			break;
		case 2:
			setViewbyPlayer(0);
			setViewbyEnemy1(0);
			setViewbyEnemy2(1);
			setViewbyEnemy3(0);

			break;
		case 3:
			setViewbyPlayer(0);
			setViewbyEnemy1(0);
			setViewbyEnemy2(0);
			setViewbyEnemy3(1);
			break;
		}
	}
	else
	{
		setViewbyPlayer(1);
		setViewbyEnemy1(1);
		setViewbyEnemy2(1);
		setViewbyEnemy3(1);
	}

	setAmbushPlayer(0);
	setAmbushEnemy1(0);
	setAmbushEnemy2(0);
	setAmbushEnemy3(0);
	return true;
}

bool BattleSquad::init()
{
	return Squad::init();
}

float BattleSquad::getAttr(enumtype attrtype , enumtype calctype)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> modifierlist = datalib->getChildList(mPath + std::string("/ModifierList"));
	if(modifierlist.size() == 0)
		return 0.0f;
	if(attrtype == ATTR_RANGEDDEFENCE )
		attrtype = ATTR_DEFENCE;
	float base = 0.0f;
	float mbouse = 0.0f;
	float mbane = 0.0f;
	float resist = 0.0f;
	float cbouse = 0.0f;
	float cbane = 0.0f;
	std::vector<std::string>::iterator ite;
	for(ite = modifierlist.begin(); ite != modifierlist.end(); ite++)
	{
		enumtype type = ATTRMODIFIER_BASE;
		float attrval = 0.0f;
		std::string datapath = mPath + std::string("/ModifierList/") + (*ite);
		datalib->getData(datapath + std::string("/Type"), type);
		switch(attrtype)
		{
		case ATTR_ATTACK:
			datalib->getData(datapath + std::string("/Attack"), attrval);
			break;
		case ATTR_RANGEDATTACK:
			datalib->getData(datapath + std::string("/RangedAttack"), attrval);
			break;
		case ATTR_DEFENCE:
			datalib->getData(datapath + std::string("/Defence"), attrval);
			break;
		case ATTR_FORM:
			datalib->getData(datapath + std::string("/Formation"), attrval);
			break;
		case ATTR_INITIATIVE:
			datalib->getData(datapath + std::string("/Initiative"), attrval);
			break;
		case ATTR_ACTIONPOINT:
			datalib->getData(datapath + std::string("/ActionPoint"), attrval);
			break;
		case ATTR_DETECTION:
			datalib->getData(datapath + std::string("/Detection"), attrval);
			break;
		case ATTR_COVERT:
			datalib->getData(datapath + std::string("/Covert"), attrval);
			break;
		case ATTR_TOUGHNESS:
			datalib->getData(datapath + std::string("/Injury"), attrval);
			break;
		case ATTR_CONTER:
			datalib->getData(datapath + std::string("/Conter"), attrval);
			break;
		}
		switch(type)
		{
		case ATTRMODIFIER_BASE:
			base += attrval;
			break;
		case ATTRMODIFIER_MAGIC:
			if(attrval > mbouse)
				mbouse = attrval;
			if(attrval < mbane)
				mbane = attrval;
			break;
		case ATTRMODIFIER_COMMAND:
			if(attrval > cbouse)
				cbouse = attrval;
			if(attrval < cbane)
				cbane = attrval;
			break;
		case ATTRMODIFIER_RESISTANCE:
			if(attrval > resist)
				resist = attrval;
			break;
		}
	}
	float bouse = cbouse + mbouse;
	float bane = cbane + mbane;
	float terrainbouse = 0.0f;
	switch(attrtype)
	{
		case ATTR_DEFENCE:
			terrainbouse = MapDataManager::getSingleton().getDefModify(getGridX(), getGridY(), getTeam());
			break;
		case ATTR_COVERT:
			terrainbouse = MapDataManager::getSingleton().getCovert(getGridX(), getGridY(), getTeam());
			break;
	}
	if(terrainbouse > 0.0f)
		bouse += terrainbouse;
	else
		bane += terrainbouse;
	if(bane < -resist)
	{
		bane += resist;
		resist = 0.0f;
	}
	else
	{
		bane = 0.0f;
		resist += bane;
	}

	bouse = bouse + bane;
	switch(calctype)
	{
	case ATTRCALC_FULL:
		return base + bouse;
		break;
	case ATTRCALC_ONLYBASE:
		return base;
		break;
	case ATTRCALC_ONLYBONUS:
		return bouse;
		break;
	}
	return 0.0f;
}

AttackInfo BattleSquad::getAttackRolls(bool rangedattack,bool asdefender, enumtype d)
{
	DataLibrary *datalib = DataLibrary::getSingletonPtr();
	AttackInfo attackinfo;
	int soildernum = getUnitNum();
	int atktime =  floor((-0.010907f) * soildernum * soildernum  + 1.37256f * soildernum+ 8.638347f + 0.5f);
	if(asdefender)
	{
		attackinfo.AtkTime = atktime * getAttr(ATTR_CONTER,ATTRCALC_FULL);
	}
	else
	{
		attackinfo.AtkTime = atktime;
	}

	float atkf;
	if(rangedattack)
	{
		atkf = getAttr(ATTR_RANGEDATTACK, ATTRCALC_FULL);
	}
	else
	{
		atkf = getAttr(ATTR_ATTACK, ATTRCALC_FULL);
		float formation;
		formation = getAttr(ATTR_FORM, ATTRCALC_FULL);
		formation = formation * soildernum / 50.0f;
		enumtype formtype = getFormation();
		enumtype mydir = getDirection();
		int side = GetSide(mydir,d);
		formation *= GetFormationBonus(side, formtype);
		atkf += formation;
	}
	attackinfo.Atk = atkf;

	std::string soilderid = getSoilderId();
	float randomness;
	datalib->getData(std::string("StaticData/SoilderData/") + soilderid + std::string("/Randomness"),randomness);
	attackinfo.Randomness = randomness;

	return attackinfo;
}

void BattleSquad::applyAttackRolls(bool rangedattack, enumtype d, AttackInfo &attackinfo)
{
	DataLibrary *datalib = DataLibrary::getSingletonPtr();

	int soildernum = getUnitNum();
	float deff;
	if(rangedattack)
	{
		deff = getAttr(ATTR_RANGEDDEFENCE, ATTRCALC_FULL);
	}
	else
	{
		deff = getAttr(ATTR_DEFENCE, ATTRCALC_FULL);
		float formation;
		formation = getAttr(ATTR_FORM, ATTRCALC_FULL);
		formation = formation * soildernum / 50.0f;
		enumtype formtype = getFormation();
		enumtype mydir = getDirection();
		int side = GetSide(mydir,d);
		formation *= GetFormationBonus(side, formtype);
		deff += formation;
	}
	int def = floor(deff + 0.5f);

	int atk = floor(attackinfo.Atk + 0.5f);
	float perc = AtkDefToPerc(atk,def);
	float killf = perc * attackinfo.AtkTime;
	killf += killf * (rand() % (attackinfo.Randomness * 2 + 1) - attackinfo.Randomness) / 100.0f;
	int kill = floor(killf + 0.5f);
	if(kill == 0)
	{
		if(rand() % 100 < attackinfo.Randomness)
			kill = 1;
	}
	soildernum -= kill;
	soildernum = (soildernum < 0)? 0: soildernum;
	setUnitNum(soildernum);

	int maxnum = getUnitMaxNum();
	maxnum -= kill * (1.0f - getAttr(ATTR_TOUGHNESS, ATTRCALC_FULL));
	setUnitMaxNum(maxnum);
}

int BattleSquad::getFaction()
{
	int team = getTeam();
	std::string relation;
	bool re = DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%team),relation);
	if(re)
	{
		if(relation == "enemy1")
			return 1;
		else if(relation == "enemy2")
			return 2;
		else if(relation == "enemy3")
			return 3;
	}
	return 0;
}

std::string BattleSquad::getFactionId()
{
	int team = getTeam();
	std::string factionid;
	DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Team/Team%1%/FactionId")%team),factionid);
	return factionid;
}

int BattleSquad::getUnitGrapNum()
{
	enumtype squadtype = getType();
	int unitnum = getUnitNum();
	if(unitnum == 0)
		return 0;
	else if(squadtype == SQUAD_NORMAL)
	{
		return (unitnum-1)/10; 
	}
	else
	{
		return (unitnum+9)/10;
	}
}