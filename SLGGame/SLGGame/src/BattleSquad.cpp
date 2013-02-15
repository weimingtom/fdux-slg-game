#include "BattleSquad.h"

#include <math.h>
#include <stdio.h>

#include <boost/format.hpp>

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "MapDataManager.h"
#include "LuaSystem.h"
#include "CommonFunction.h"
#include "MapDataManager.h"

BattleSquad::BattleSquad(std::string path)
:Squad(path)
{

}

BattleSquad::~BattleSquad()
{

}

bool BattleSquad::init(std::string srcpath, int team, int unitnum, int x, int y, int d)
{
	if(!Squad::init(srcpath))
		return false;
	DataLibrary *datalib = DataLibrary::getSingletonPtr();
	setTeam(team);
	setGridX(x);
	setGridY(y);
	setDirection(d);

	setUnitNum(unitnum);
	int squadtype2;
	datalib->getData(srcpath + std::string("/Type"), squadtype2);
	if(squadtype2 == SQUAD_NORMAL)
	{
		setUnitMaxNum(unitnum);
		setFormation(Line);
	}
	else
	{
		setUnitMaxNum(20);
		setFormation(Loose);
	}

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

	setActionPoint(0.0f);
	setAPSetup(0.0f);
	setAPBattle(0.0f);
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
	int squadtype2;
	datalib->getData(srcpath + std::string("/Type"), squadtype2);
	if(squadtype2 == SQUAD_NORMAL)
	{
		datalib->getData(srcpath + std::string("/UnitNum"), unitnum);
		setFormation(Line);
	}
	else
	{
		unitnum = 20;
		setFormation(Loose);
	}
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

	setActionPoint(0.0f);
	setAPSetup(0.0f);
	setAPBattle(0.0f);
	return true;
}

bool BattleSquad::init()
{
	return Squad::init();
}

float BattleSquad::getAttr(int attrtype , int calctype)
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
		int type = ATTRMODIFIER_BASE;
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
			datalib->getData(datapath + std::string("/Toughness"), attrval);
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

AttackInfo BattleSquad::getAttackRolls(bool rangedattack,bool asdefender, int d)
{
	DataLibrary *datalib = DataLibrary::getSingletonPtr();
	AttackInfo attackinfo;
	int soildernum = getUnitNum();
	int atktime =  floor((-0.010907f) * soildernum * soildernum  + 1.37256f * soildernum+ 8.638347f + 0.5f);
	if(asdefender)
	{
		attackinfo.AtkTime = atktime * getAttr(ATTR_CONTER,ATTRCALC_FULL) / 10.0f;
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
		int formtype = getFormation();
		int mydir = getDirection();
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

void BattleSquad::applyAttackRolls(bool rangedattack, int d, AttackInfo &attackinfo)
{
	DataLibrary *datalib = DataLibrary::getSingletonPtr();

	int soildernum = getUnitNum();
	float deff;
	if(rangedattack)
	{
		deff = getAttr(ATTR_RANGEDDEFENCE, ATTRCALC_FULL);
		deff += RANGEDDEFENCEBONUS;
		float formation;
		formation = getAttr(ATTR_FORM, ATTRCALC_FULL);
		formation = formation * soildernum / 50.0f;
		switch(getFormation())
		{
		case Line:
			formation *= FORMBONSE_LINE_RANGED;
			break;
		case Circular:
			formation *= FORMBONSE_CIRC_RANGED;
			break;
		default:
			formation *= FORMBONSE_LOOS_RANGED;
			break;
		}
		deff -= formation;
	}
	else
	{
		deff = getAttr(ATTR_DEFENCE, ATTRCALC_FULL);
		float formation;
		formation = getAttr(ATTR_FORM, ATTRCALC_FULL);
		formation = formation * soildernum / 50.0f;
		int formtype = getFormation();
		int mydir = getDirection();
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
	maxnum -= kill * (1.0f - getAttr(ATTR_TOUGHNESS, ATTRCALC_FULL) / 10.0f);
	setUnitMaxNum(maxnum);
}

bool BattleSquad::changeFormation(int formation, bool costap)
{
	if(canChangeFormation(formation) != SKILLSTATE_AVAILABLE)
		return false;
	setFormation(formation);
	if(costap)
	{
		float ap = getActionPoint();
		float apcost = getAPTypeCostModify(SKILLAPTYPE_SETUP);
		ap -= apcost;
		setAPTypeCostModify(SKILLAPTYPE_SETUP, apcost + 1.0f);
		setActionPoint(ap);
	}
	return true;
}

bool BattleSquad::useSkillOn(BattleSquad* targetsquad, std::string skillid)
{
	if(canUseSkill(skillid) != SKILLSTATE_AVAILABLE)
		return false;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string skillpath = getPath() + std::string("/Skill/") + skillid;
	std::string skillinfopath = std::string("StaticData/SkillData/")+ skillid;
	std::string skillscript;
	datalib->getData(skillinfopath + std::string("/Script"),skillscript);
	LuaTempContext* context = new LuaTempContext;
	context->strMap.insert(std::make_pair("squadid", getSquadId()));
	context->strMap.insert(std::make_pair("targetsquadid", targetsquad->getSquadId()));
	context->intMap.insert(std::make_pair("castsuccess", 0));
	bool re = LuaSystem::getSingleton().executeFunction(skillscript, "useskill" , skillpath + std::string("/ScriptContext"), context);
	if(re)
	{
		if(context->intMap["castsuccess"] == 1)
		{
			float apcost = getSkillApCost(skillid);
			float apleft = getActionPoint() - apcost;
			setActionPoint(apleft);
			int aptype = SKILLAPTYPE_BATTLE;
			datalib->getData(skillinfopath + "/APType", aptype);
			if(aptype != SKILLAPTYPE_DEFENCE)
			{
				apcost = getAPTypeCostModify(aptype);
				apcost += 1.0f;
				setAPTypeCostModify(aptype, apcost);
			}
			datalib->getData(skillinfopath + "/CoolDown", apcost);
			datalib->setData(skillpath + "/CoolDown", apcost);
		}
	}
	delete context;
	return re;
}

bool BattleSquad::useSkillAt(int x, int y, std::string skillid)
{
	if(canUseSkill(skillid) != SKILLSTATE_AVAILABLE)
		return false;
		DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string skillpath = getPath() + std::string("/Skill/") + skillid;
	std::string skillinfopath = std::string("StaticData/SkillData/")+ skillid;
	std::string skillscript;
	datalib->getData(skillinfopath + std::string("/Script"),skillscript);
	LuaTempContext* context = new LuaTempContext;
	context->strMap.insert(std::make_pair("squadid", getSquadId()));
	context->intMap.insert(std::make_pair("targetx", x));
	context->intMap.insert(std::make_pair("targety", y));
	context->intMap.insert(std::make_pair("castsuccess", 0));
	bool re = LuaSystem::getSingleton().executeFunction(skillscript, "useskill" , skillpath + std::string("/ScriptContext"), context);
	if(re)
	{
		if(context->intMap["castsuccess"] == 1)
		{
			float apcost = getSkillApCost(skillid);
			float apleft = getActionPoint() - apcost;
			setActionPoint(apleft);
			int aptype = SKILLAPTYPE_BATTLE;
			datalib->getData(skillinfopath + "/APType", aptype);
			if(aptype != SKILLAPTYPE_DEFENCE)
			{
				apcost = getAPTypeCostModify(aptype);
				apcost += 1.0f;
				setAPTypeCostModify(aptype, apcost);
			}
			datalib->getData(skillinfopath + "/CoolDown", apcost);
			datalib->setData(skillpath + "/CoolDown", apcost);
		}
	}
	delete context;
	return false;
}

bool BattleSquad::tryMove(int srcx, int srcy, int tgx, int tgy, float &apleft, unsigned int &eventflag)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	if(mapdatamanager->getPassable(tgx, tgy, getFaction()))
	{
		float mapapcost = 0.0f;
		if(getHorseId() != "none")
			mapapcost = mapdatamanager->getCavApCost(tgx, tgy, getFaction());
		else
			mapapcost = mapdatamanager->getInfApCost(tgx, tgy, getFaction());
		if(mapapcost <= apleft)
		{
			apleft -= mapapcost;
			if(mapapcost <= 2)
			{
				eventflag |= MOVEEVENT_CHARGE;
				int curdir = GetDirection(srcx, srcy, tgx, tgy);
				eventflag |= SetChargeDir(curdir);
			}
			else
			{
				eventflag &= ~MOVEEVENT_CHARGE;
			}
			return true;
		}
	}
	eventflag |= MOVEEVENT_WRONG;
	return false;
}


bool BattleSquad::move(int tgx, int tgy, unsigned int &eventflag)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	if(mapdatamanager->getPassable(tgx, tgy, getFaction()))
	{
		float mapapcost = 0.0f;
		if(getHorseId() != "none")
			mapapcost = mapdatamanager->getCavApCost(tgx, tgy, getFaction());
		else
			mapapcost = mapdatamanager->getInfApCost(tgx, tgy, getFaction());
		float ap = getActionPoint();
		if(mapapcost <= ap)
		{
			ap -= mapapcost;
			setActionPoint(ap);
			if(mapapcost <= 2)
			{
				eventflag |= MOVEEVENT_CHARGE;
				int curdir = GetDirection(getGridX(), getGridY(), tgx, tgy);
				eventflag |= SetChargeDir(curdir);
			}
			else
			{
				eventflag &= ~MOVEEVENT_CHARGE;
			}
			return true;
		}
	}
	eventflag |= MOVEEVENT_WRONG;
	return false;
}

bool BattleSquad::addParticle(std::string particlename, int object, std::string &particleid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string distpath = mPath + std::string("/ParticleList");
	std::vector<std::string> particlelist = datalib->getChildList(distpath);
	int x = 0;
	particleid = std::string("p") + Ogre::StringConverter::toString(x);
	std::vector<std::string>::iterator ite = std::find(particlelist.begin(), particlelist.end(),particleid);
	while(ite != particlelist.end())
	{
		x = x + 1;
		particleid = std::string("p") + Ogre::StringConverter::toString(x);
		ite = std::find(particlelist.begin(), particlelist.end(),particleid);
	}
	distpath = distpath + std::string("/") + particleid;
	datalib->setData(distpath + std::string("/ParticleName"), particlename, true);
	datalib->setData(distpath + std::string("/AffectUnit"), object, true);
	return true;
}

void BattleSquad::removeParticle(std::string particleid)
{
	std::string particlepath = mPath + std::string("/ParticleList/") + particleid;
	DataLibrary::getSingleton().delNode(particlepath);
}

void BattleSquad::turnStart()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	float ap = getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL);
	setActionPoint(ap);
	setAPSetup(0.0f);
	setAPBattle(0.0f);
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	Trigger("TurnStart", luatempcontext);
	delete luatempcontext;
}

void BattleSquad::turnEnd()
{
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	Trigger("TurnEnd", luatempcontext);
	delete luatempcontext;

	setAmbushPlayer(0);
	setAmbushEnemy1(0);
	setAmbushEnemy2(0);
	setAmbushEnemy3(0);
}

void BattleSquad::onMeleeAttack(BattleSquad* targetsquad, bool asdefender)
{
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	luatempcontext->strMap["targetsquadid"] = targetsquad->getSquadId();
	luatempcontext->intMap["asdefender"] = asdefender?1:0;
	Trigger("OnMeleeAttack", luatempcontext);
	delete luatempcontext;
}

void BattleSquad::afterMeleeAttack(BattleSquad* targetsquad, bool asdefender)
{
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	luatempcontext->strMap["targetsquadid"] = targetsquad->getSquadId();
	luatempcontext->intMap["asdefender"] = asdefender?1:0;
	Trigger("AfterMeleeAttack", luatempcontext);
	delete luatempcontext;
}

void BattleSquad::onCharge()
{
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	Trigger("OnCharge", luatempcontext);
	delete luatempcontext;
}

void BattleSquad::afterCharge()
{
	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	Trigger("AfterCharge", luatempcontext);
	delete luatempcontext;
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

bool BattleSquad::getViewByFaction(int faction)
{
	switch(faction)
	{
	case 0:
		return getViewbyPlayer();
	case 1:
		return getViewbyEnemy1();
	case 2:
		return getViewbyEnemy2();
	case 3:
		return getViewbyEnemy3();
	}
	return false;
}

void BattleSquad::setViewByFaction(int faction, bool view)
{
	int iview = view?1:0;
	switch(faction)
	{
	case 0:
		setViewbyPlayer(iview);
		break;
	case 1:
		setViewbyEnemy1(iview);
		break;
	case 2:
		setViewbyEnemy2(iview);
		break;
	case 3:
		setViewbyEnemy3(iview);
		break;
	}
}

bool BattleSquad::getAmbushFaction(int faction)
{
	switch(faction)
	{
	case 0:
		return getAmbushPlayer();
	case 1:
		return getAmbushEnemy1();
	case 2:
		return getAmbushEnemy2();
	case 3:
		return getAmbushEnemy3();
	}
	return false;
}

void BattleSquad::setAmbushFaction(int faction, bool ambush)
{
	int iambush = ambush?1:0;
	switch(faction)
	{
	case 0:
		setAmbushPlayer(iambush);
		break;
	case 1:
		setAmbushEnemy1(iambush);
		break;
	case 2:
		setAmbushEnemy2(iambush);
		break;
	case 3:
		setAmbushEnemy3(iambush);
		break;
	}
}

int BattleSquad::getUnitGrapNum()
{
	int squadtype = getType();
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

float BattleSquad::getSquadStrength()
{
	int squadtype = getType();
	int unitnum = getUnitNum();
	int level = getLevel();
	if(squadtype == SQUAD_NORMAL)
	{
		return unitnum * level;
	}
	else
	{
		return unitnum * 3.125f * level;
	}
}

std::vector<BattleSquad::ActiveSkillInfo> BattleSquad::GetActiveSkillList()
{
	std::vector<ActiveSkillInfo> skilllist;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	ActiveSkillInfo skillinfo;
	//判断移动
	if(canMove() == SKILLSTATE_AVAILABLE)
	{
		skillinfo.skillid = "move";
		skillinfo.apcost = 0;
		skillinfo.available = true;
		skilllist.push_back(skillinfo);
		skillinfo.skillid = "turn";
		skillinfo.apcost = 0;
		skillinfo.available = true;
		skilllist.push_back(skillinfo);
	}
	else if(canMove() == SKILLSTATE_NOTAVAILABLE)
	{
		skillinfo.skillid = "move";
		skillinfo.apcost = 0;
		skillinfo.available = false;
		skilllist.push_back(skillinfo);
	}
	
	//判断阵型
	switch(canChangeFormation(Loose))
	{
	case SKILLSTATE_AVAILABLE:
		skillinfo.skillid = "looseformation";
		skillinfo.apcost = getChangeFormationApCost(Loose);
		skillinfo.available = true;
		skilllist.push_back(skillinfo);
		break;
	case SKILLSTATE_NOTAVAILABLE:
		skillinfo.skillid = "looseformation";
		skillinfo.apcost = getChangeFormationApCost(Loose);
		skillinfo.available = false;
		skilllist.push_back(skillinfo);
		break;
	}
	switch(canChangeFormation(Line))
	{
	case SKILLSTATE_AVAILABLE:
		skillinfo.skillid = "lineformation";
		skillinfo.apcost = getChangeFormationApCost(Line);
		skillinfo.available = true;
		skilllist.push_back(skillinfo);
		break;
	case SKILLSTATE_NOTAVAILABLE:
		skillinfo.skillid = "lineformation";
		skillinfo.apcost = getChangeFormationApCost(Line);
		skillinfo.available = false;
		skilllist.push_back(skillinfo);
		break;
	}
	switch(canChangeFormation(Circular))
	{
	case SKILLSTATE_AVAILABLE:
		skillinfo.skillid = "circularformation";
		skillinfo.apcost = getChangeFormationApCost(Circular);
		skillinfo.available = true;
		skilllist.push_back(skillinfo);
		break;
	case SKILLSTATE_NOTAVAILABLE:
		skillinfo.skillid = "circularformation";
		skillinfo.apcost = getChangeFormationApCost(Circular);
		skillinfo.available = false;
		skilllist.push_back(skillinfo);
		break;
	}
	//判断主动技能
	std::vector<std::string> activeskills;
	activeskills = datalib->getChildList(mPath + "/Skill");
	std::vector<std::string>::iterator ite;
	for(ite = activeskills.begin(); ite != activeskills.end(); ite++)
	{
		switch(canUseSkill(*ite))
		{
		case SKILLSTATE_AVAILABLE:
			skillinfo.skillid = (*ite);
			skillinfo.apcost = getSkillApCost(*ite);
			skillinfo.available = true;
			skilllist.push_back(skillinfo);
			break;
		case SKILLSTATE_NOTAVAILABLE:
			skillinfo.skillid = (*ite);
			skillinfo.apcost = getSkillApCost(*ite);
			skillinfo.available = false;
			skilllist.push_back(skillinfo);
			break;
		}
	}
	return skilllist;
}

BattleSquad::SkillState BattleSquad::canMove()
{
	return SKILLSTATE_AVAILABLE;
}

BattleSquad::SkillState BattleSquad::canChangeFormation(int formation)
{
	if(getType() != SQUAD_NORMAL)
		return SKILLSTATE_NOSKILL;
	if(getFormation() == formation)
		return SKILLSTATE_NOSKILL;
	if(getActionPoint() >= getChangeFormationApCost(formation))
		return SKILLSTATE_AVAILABLE;
	return SKILLSTATE_NOTAVAILABLE;
}

BattleSquad::SkillState BattleSquad::canUseSkill(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> activeskills;
	activeskills = datalib->getChildList(mPath + "/Skill");
	std::vector<std::string>::iterator ite;
	ite = std::find(activeskills.begin(), activeskills.end(), skillid);
	if(ite == activeskills.end())
		return SKILLSTATE_NOSKILL;
	if(getActionPoint() >= getSkillApCost(skillid))
		return SKILLSTATE_AVAILABLE;
	return SKILLSTATE_NOTAVAILABLE;
}

float BattleSquad::getChangeFormationApCost(int formation)
{
	return getAPTypeCostModify(SKILLAPTYPE_SETUP);
}

float BattleSquad::getSkillApCost(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> skilllist;
	skilllist = datalib->getChildList("StaticData/SkillData");
	std::vector<std::string>::iterator ite;
	ite = std::find(skilllist.begin(), skilllist.end(), skillid);
	if(ite == skilllist.end())
		return 0.0f;
	int skillaptype;
	float skillapcost;
	datalib->getData(str(boost::format("StaticData/SkillData/%1%/APType")%skillid),skillaptype);
	datalib->getData(str(boost::format("StaticData/SkillData/%1%/APCost")%skillid),skillapcost);
	switch(skillaptype)
	{
	case SKILLAPTYPE_SETUP:
	case SKILLAPTYPE_BATTLE:
		return getAPTypeCostModify(skillaptype) + skillapcost;
	case SKILLAPTYPE_DEFENCE:
		{
			float ap = getActionPoint();
			return (ap > skillapcost)?ap:skillapcost;
		}
	}
	return 0.0f;
}


float BattleSquad::getAPTypeCostModify(int aptype)
{
	switch(aptype)
	{
	case SKILLAPTYPE_SETUP:
		return getAPSetup();
	case SKILLAPTYPE_BATTLE:
		return getAPBattle();
	}
	return 0.0f;
}

void BattleSquad::setAPTypeCostModify(int aptype, float val)
{
	switch(aptype)
	{
	case SKILLAPTYPE_SETUP:
		setAPSetup(val);
		break;
	case SKILLAPTYPE_BATTLE:
		setAPBattle(val);
		break;
	}
}

void BattleSquad::setUnitNum(int val)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();

	datalib->setData(getPath() + "/UnitNum", val);

	LuaTempContext* luatempcontext = new LuaTempContext();
	luatempcontext->strMap["squadid"] = getSquadId();
	Trigger("UnitNumChange", luatempcontext);
	delete luatempcontext;

	if(getUnitNum() <= 0)
	{
		LuaTempContext* luatempcontext = new LuaTempContext();
		luatempcontext->strMap["squadid"] = getSquadId();
		MapDataManager::getSingleton().Trigger("SquadAnnihilated", luatempcontext);
		delete luatempcontext;
	}
}