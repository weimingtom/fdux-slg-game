#include "BattleSquad.h"

#include <math.h>
#include <stdio.h>

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AVGSquadManager.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h" 
#include "LuaSystem.h"
#include "TriggerManager.h"
#include "CommonFunction.h"

BattleSquad::BattleSquad(std::string id, int grapid ,int x, int y)
:mId(id),mGrapId(grapid)
{
	setCrood(x,y);
	std::string team;
	DataLibrary::getSingleton().getData(getPath() + std::string("/TeamId"),team);
	if(team == "Team1")
		mTeam = 1;
	else if(team == "Team2")
		mTeam = 2;
	else if(team == "Team3")
		mTeam = 3;
	else if(team == "Team4")
		mTeam = 4;

	mCovert = getAttr(ATTR_COVERT,ATTRCALC_FULL,getDirection());
	mDetection = getAttr(ATTR_DETECTION,ATTRCALC_FULL,getDirection());

	int view;
	bool re = DataLibrary::getSingleton().getData(getPath() + std::string("/ViewbyPlayer"),view);
	if(!re)
	{
		std::string temppath,tempstr;
		temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(mTeam) + std::string("/Relation");
		DataLibrary::getSingleton().getData(temppath,tempstr);
		if(tempstr == "none")
		{
			mViewbyFaction[0] = mViewbyFaction[1] = mViewbyFaction[2] = mViewbyFaction[3] = true;
			DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),1);
			DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),1);
			DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),1);
			DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),1);
		}
		else
		{
			//计算初始隐藏
			if(mCovert > 0.0f)
			{
				if(tempstr == "alliance")
				{
					mViewbyFaction[0] = true;
					mViewbyFaction[1] = mViewbyFaction[2] = mViewbyFaction[3] = false;
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),1);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),0);
				}
				else if(tempstr == "player")
				{
					mViewbyFaction[0] = true;
					mViewbyFaction[1] = mViewbyFaction[2] = mViewbyFaction[3] = false;
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),1);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),0);
				}
				else if(tempstr == "enemy1")
				{
					mViewbyFaction[1] = true;
					mViewbyFaction[0] = mViewbyFaction[2] = mViewbyFaction[3] = false;
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),1);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),0);
				}
				else if(tempstr == "enemy2")
				{
					mViewbyFaction[2] = true;
					mViewbyFaction[1] = mViewbyFaction[0] = mViewbyFaction[3] = false;
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),1);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),0);
				}
				else if(tempstr == "enemy3")
				{
					mViewbyFaction[3] = true;
					mViewbyFaction[1] = mViewbyFaction[2] = mViewbyFaction[0] = false;
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),0);
					DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),1);
				}
			}
			else
			{
				mViewbyFaction[0] = mViewbyFaction[1] = mViewbyFaction[2] = mViewbyFaction[3] = true;
				DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),1);
				DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),1);
				DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),1);
				DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),1);
			}
		}
	}
	else
	{
		//读取隐藏
		int view = 0;
		DataLibrary::getSingleton().getData(getPath() + std::string("/ViewbyPlayer"),view);
		mViewbyFaction[0] = (view == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/ViewbyEnemy1"),view);
		mViewbyFaction[1] = (view == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/ViewbyEnemy2"),view);
		mViewbyFaction[2] = (view == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/ViewbyEnemy3"),view);
		mViewbyFaction[3] = (view == 1);
	}

	re = DataLibrary::getSingleton().getData(getPath() + std::string("/AmbushPlayer"),view);
	if(!re)
	{
		mAmbushFaction[0] = mAmbushFaction[1] = mAmbushFaction[2] = mAmbushFaction[3] = false;
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushPlayer"),0);
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy1"),0);
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy2"),0);
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy3"),0);
	}
	else
	{
		//读取突袭
		int ambush = 0;
		DataLibrary::getSingleton().getData(getPath() + std::string("/AmbushPlayer"),ambush);
		mAmbushFaction[0] = (ambush == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/AmbushEnemy1"),ambush);
		mAmbushFaction[1] = (ambush == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/AmbushEnemy2"),ambush);
		mAmbushFaction[2] = (ambush == 1);
		DataLibrary::getSingleton().getData(getPath() + std::string("/AmbushEnemy3"),ambush);
		mAmbushFaction[3] = (ambush == 1);
	}
	if(getUnitRealNum() > 0)
		mIsEliminated = false;
	else
		mIsEliminated = true;
}
BattleSquad::~BattleSquad()
{

}

std::string BattleSquad::getPath()
{
	return std::string("GameData/BattleData/SquadList/") + mId;
}

void BattleSquad::setCrood(int x, int y)
{
	mX = x;
	mY = y;
	std::string datapath = getPath();
	DataLibrary::getSingleton().setData(datapath + std::string("/GridX"),mX);
	DataLibrary::getSingleton().setData(datapath + std::string("/GridY"),mY);
}

void BattleSquad::setDirection(Direction d)
{
	DataLibrary::getSingleton().setData(getPath() + std::string("/Direction"),d);
}

void BattleSquad::getCrood(int* x, int* y)
{
	if(x != NULL)
		(*x) = mX;
	if(y != NULL)
		(*y) = mY;
}

Direction BattleSquad::getDirection()
{
	Direction d;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Direction"),d);
	return d;
}

void BattleSquad::setFormation(Formation f)
{
	DataLibrary::getSingleton().setData(getPath() + std::string("/Formation"),f);
}
Formation BattleSquad::getFormation()
{
	Formation f;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Formation"),f);
	return f;
}

std::string BattleSquad::getSquadName()
{
	std::string name;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Name"),name);
	return name;
}

std::string BattleSquad::getFactionId()
{
	std::string temppath,tempstr;
	temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(mTeam) + std::string("/FactionId");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	return tempstr;
}

float BattleSquad::getAttr(AttrType attrtype, AttrCalcType calctype, Direction direction)
{
	if(attrtype > ATTR_RANGEDDEFENCE || attrtype < ATTR_ATTACK)
		return 0.0f;
	float attr = 0.0f;
	AttrType tempattrtype = attrtype;
	if( attrtype == ATTR_RANGEDDEFENCE)
		tempattrtype = ATTR_DEFENCE;
	bool re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),tempattrtype,calctype ,attr);
	if(calctype != ATTRCALC_FULL)
		return attr;
	float form;
	float resist;
	float trrainmodi;
	int unitnum;
	Direction mydirection;
	Formation formation;
	int side = 0;
	switch(attrtype)
	{
	case ATTR_ATTACK:
	case ATTR_DEFENCE:
		re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_FORM,calctype ,form);
		re = DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),unitnum);
		form *= unitnum;
		mydirection = getDirection();
		formation = getFormation();
		side = GetSide(mydirection,direction);
		switch(side)
		{
		case 0:
			switch(formation)
			{
			case Line:
				form *= FORMBONSE_LINE_FRONT;
				break;
			case Circular:
				form *= FORMBONSE_CIRC_FRONT;
				break;
			case Loose:
				form *= FORMBONSE_LOOS_FRONT;
				break;
			}
			break;
		case 1:
			switch(formation)
			{
			case Line:
				form *= FORMBONSE_LINE_SIDE;
				break;
			case Circular:
				form *= FORMBONSE_CIRC_SIDE;
				break;
			case Loose:
				form *= FORMBONSE_LOOS_SIDE;
				break;
			}
			break;
		case 2:
			switch(formation)
			{
			case Line:
				form *= FORMBONSE_LINE_BACK;
				break;
			case Circular:
				form *= FORMBONSE_CIRC_BACK;
				break;
			case Loose:
				form *= FORMBONSE_LOOS_BACK;
				break;
			}
			break;
		}
		attr = attr + form;
		attr *= getMoraleBonse();
		if(attrtype==ATTR_DEFENCE)
		{
			trrainmodi = MapDataManager::getSingleton().getDefModify(mX,mY,mTeam);
			if(trrainmodi < 0.0f)
			{
				re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_DEFENCE,ATTRCALC_RESISTLEFT ,resist);
				trrainmodi += resist;
				trrainmodi = (trrainmodi > 0.0f)? 0.0f:trrainmodi;
			}
			attr += trrainmodi;
		}
		break;
	case ATTR_RANGEDDEFENCE:
		re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_FORM,calctype ,form);
		re = DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),unitnum);
		form *= unitnum;
		formation = getFormation();
		switch(formation)
		{
		case Line:
			form *= FORMBONSE_LINE_RANGED;
			break;
		case Circular:
			form *= FORMBONSE_CIRC_RANGED;
			break;
		case Loose:
			form *= FORMBONSE_LOOS_RANGED;
			break;
		}
		attr = attr + RANGEDDEFENCEBONUS - form;
		attr *= getMoraleBonse();
		trrainmodi = MapDataManager::getSingleton().getDefModify(mX,mY,mTeam);
		if(trrainmodi < 0.0f)
		{
			re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_DEFENCE,ATTRCALC_RESISTLEFT ,resist);
			trrainmodi += resist;
			trrainmodi = (trrainmodi > 0.0f)? 0.0f:trrainmodi;
		}
		attr += trrainmodi;
		break;
	case ATTR_COVERT:
		trrainmodi = MapDataManager::getSingleton().getCovert(mX,mY,mTeam);
		if(trrainmodi < 0.0f)
		{
			re = AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_COVERT,ATTRCALC_RESISTLEFT ,resist);
			trrainmodi += resist;
			trrainmodi = (trrainmodi > 0.0f)? 0.0f:trrainmodi;
		}
		attr += trrainmodi;
		break;
	default:
		break;
	}
	return attr;
}

float BattleSquad::getMoraleBonse()
{
	int morale = 0;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Morale"),morale);
	return 0.6f +  0.006f * morale;
}

void BattleSquad::modifyMorale(int m)
{
	int morale = 0;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Morale"),morale);
	float moralequotiety = getAttr(ATTR_INJURY, ATTRCALC_FULL, North);
	moralequotiety *= m;
	m = floor(moralequotiety + 0.5f);
	morale += m;
	morale = (morale > 100)? 100: morale;
	morale = (morale < 0)? 0: morale;
	DataLibrary::getSingleton().setData(getPath() + std::string("/Morale"),morale);
}

int BattleSquad::getUnitRealNum()
{
	int unitnum;
	DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),unitnum);
	return unitnum;
}

int BattleSquad::getUnitGrapNum()
{
	SquadType squadtype;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Type"),squadtype);
	int unitnum=getUnitRealNum();
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

void BattleSquad::newTurn()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	float ap = getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL,North);
	datalib->setData(getPath() + std::string("/ActionPoint"),ap);
	datalib->setData(getPath() + std::string("/APSetup"),0.0f);
	datalib->setData(getPath() + std::string("/APBattle"),0.0f);
	//触发回合开始
// 	std::vector<std::string> triggerlist;
// 	triggerlist = datalib->getChildList(getPath() + std::string("/Trigger"));
// 	if(triggerlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
// 		{
// 			std::string datapath = getPath() + std::string("/Trigger/") + (*ite);
// 			int active;
// 			datalib->getData(datapath ,active);
// 			if(!active)
// 				continue;
// 			std::string type;
// 			datalib->getData(datapath + std::string("/type"),type);
// 			if(type != "TurnStart")
// 				continue;
// 			std::string context,filename,funcname;
// 			datalib->getData(datapath + std::string("/file"),filename);
// 			datalib->getData(datapath + std::string("/func"),funcname);
// 			datalib->getData(datapath + std::string("/context"),context);
// 			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
// 		}
// 	}
	TriggerContext* trigger = new TriggerContext("TurnStart");
	TriggerManager::getSingleton().Trigger(getPath(),trigger);
	
	//计算技能
	std::vector<std::string>::iterator ite;
	std::vector<std::string> skilllist = datalib->getChildList(getPath() + std::string("/SkillTable"));
	for(ite = skilllist.begin(); ite != skilllist.end(); ite++)
	{
		std::string skillpath = getPath() + std::string("/SkillTable/") + (*ite);
		int cooldown;
		bool re = datalib->getData(skillpath + std::string("/CoolDown"),cooldown,true);
		if(re)
		{
			if(cooldown > 0)
				datalib->setData(skillpath + std::string("/CoolDown"),cooldown - 1);
		}
		else
			datalib->setData(skillpath + std::string("/CoolDown"),0);
	}
}

int BattleSquad::getTeam()
{
	return mTeam;
}

bool BattleSquad::viewbyTeam(int team)
{
	int faction = getTeamFaction(team);
	return mViewbyFaction[faction];
}

void BattleSquad::setViewbyTeam(int team, bool view)
{
	int faction = getTeamFaction(team);
	mViewbyFaction[faction] = view;
	switch(faction)
	{
	case 0:
		DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyPlayer"),view);
		break;
	case 1:
		DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy1"),view);
		break;
	case 2:
		DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy2"),view);
		break;
	case 3:
		DataLibrary::getSingleton().setData(getPath() + std::string("/ViewbyEnemy3"),view);
		break;
	}

}

bool BattleSquad::ambushTeam(int team)
{
	int faction = getTeamFaction(team);
	return mAmbushFaction[faction];
}
void BattleSquad::setAmbushTeam(int team, bool ambush)
{
	int faction = getTeamFaction(team);
	switch(faction)
	{
	case 0:
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushPlayer"),ambush);
		break;
	case 1:
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy1"),ambush);
		break;
	case 2:
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy2"),ambush);
		break;
	case 3:
		DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy3"),ambush);
		break;
	}
}

float BattleSquad::getActionPoint()
{
	float ap = 0.0f;
	DataLibrary::getSingleton().getData(getPath() + std::string("/ActionPoint"),ap);
	return ap;
}

SquadType BattleSquad::getType()
{
	SquadType type;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Type"),type);
	if(type!= SQUAD_NORMAL && type!= SQUAD_SPECIAL)
		type = SQUAD_NORMAL;
	return type;
}

float BattleSquad::getActionPointCost(int type)
{
	float apcost = 0;
	if(type == SKILLAPTYPE_SETUP)
		DataLibrary::getSingleton().getData(getPath() + std::string("/APSetup"),apcost);
	else if(type == SKILLAPTYPE_BATTLE)
		DataLibrary::getSingleton().getData(getPath() + std::string("/APBattle"),apcost);
	return apcost;
}

AttackInfo BattleSquad::getAttackRolls(bool rangedattack,bool asdefender, Direction d)
{
	AttackInfo attackinfo;
	float atkf;
	if(rangedattack)
		atkf = getAttr(ATTR_RANGEDATTACK, ATTRCALC_FULL, d);
	else
		atkf = getAttr(ATTR_ATTACK, ATTRCALC_FULL, d);
	int atk = floor(atkf + 0.5f);
 	int soildernum;
 	DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),soildernum);
// 	DataLibrary::getSingleton().getData(getPath() + std::string("/WoundNum"),woundnum);
// 	healthynum = soildernum - woundnum;
 	if(asdefender)
 		soildernum *= getAttr(ATTR_CONTER,ATTRCALC_FULL, d);
	std::string soilderid;
	int fluctuate;
	DataLibrary::getSingleton().getData(getPath() + std::string("/SoilderId"),soilderid);
	DataLibrary::getSingleton().getData(std::string("StaticData/SoilderData/") + soilderid + std::string("/Fluctuate"),fluctuate);
// 	int atknum = std::min(healthynum , soildernum);
// 	int n = 0;
// 	for(n = 0; n < atknum; n++)
// 	{
// 		int atkroll = rand()% ATKROLL;
// 		if(atkroll == ATKROLL -1)
// 			atkroll = 100;
// 		else if(atkroll == 0)
// 			atkroll = -100;
// 		attackrolls.push_back(atk + atkroll);
// 	}
// 	soildernum -= atknum;
// 	healthynum -= atknum;
// 	if(soildernum > 0)
// 	{
// 		atknum = std::min(woundnum , soildernum);
// 		atk *= getAttr(ATTR_INJURY,ATTRCALC_FULL, d);
// 		for(n = 0; n < atknum; n++)
// 		{
// 			int atkroll = rand()% ATKROLL;
// 			if(atkroll == ATKROLL -1)
// 				atkroll = 100;
// 			else if(atkroll == 0)
// 				atkroll = -100;
// 			attackrolls.push_back(atk +atkroll);
// 		}
// 	}
	attackinfo.AtkTime = soildernum;
	attackinfo.Atk = atkf;
	attackinfo.Fluctuate = fluctuate;
	return attackinfo;
}

void BattleSquad::applyAttackRolls(bool rangedattack, Direction d, AttackInfo &attackinfo)
{
	float deff;
	if(rangedattack)
		deff = getAttr(ATTR_RANGEDDEFENCE, ATTRCALC_FULL, d);
	else
		deff = getAttr(ATTR_DEFENCE, ATTRCALC_FULL, d);
	int def = floor(deff + 0.5f);
	//int wounddef = def * getAttr(ATTR_INJURY, ATTRCALC_FULL, d);
	int soildernum;
	DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),soildernum);
// 	DataLibrary::getSingleton().getData(getPath() + std::string("/WoundNum"),woundnum);
// 	std::string soilderid;
// 	int inj;
// 	DataLibrary::getSingleton().getData(getPath() + std::string("/SoilderId"),soilderid);
// 	DataLibrary::getSingleton().getData(std::string("StaticData/SoilderData/") + soilderid + std::string("/Injury"),inj);
// 	healthynum = soildernum - woundnum;
// 	int atknum = 0;
// 	int unit = 1;
// 	int temphealth = 0, tempwound = 0;
// 	while(atknum < attackrolls.size())
// 	{
// 		if(unit > soildernum)
// 		{
// 			healthynum = temphealth;
// 			woundnum = tempwound;
// 			temphealth = 0;
// 			tempwound = 0;
// 			soildernum = healthynum + woundnum;
// 			unit = 1;
// 			if(soildernum == 0)
// 			{
// 				DataLibrary::getSingleton().setData(getPath() + std::string("/UnitNumber"),0);
// 				DataLibrary::getSingleton().setData(getPath() + std::string("/WoundNum"),0);
// 				OnDead();
// 				break;
// 			}
// 		}
// 		if(unit < healthynum)
// 		{
// 			if(attackrolls[atknum] > def + DEFBOUSE)
// 			{
// 				atknum++;
// 				if(inj != 0)
// 				{
// 					if(atknum< attackrolls.size())
// 					{
// 						if (attackrolls[atknum] <= def + DEFBOUSE)
// 						{
// 							tempwound++;
// 						}
// 						atknum++;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				atknum++;
// 				temphealth++;
// 			}
// 		}
// 		else
// 		{
// 			if(attackrolls[atknum] > wounddef + DEFBOUSE)
// 			{
// 				atknum++;
// 			}
// 			else
// 			{
// 				atknum++;
// 				tempwound++;
// 			}
// 		}
// 		unit++;
// 	}
// 	if(unit < healthynum)
// 	{
// 		temphealth += healthynum - unit + 1;
// 		tempwound += woundnum;
// 	}
// 	else
// 	{
// 		tempwound += woundnum - (unit - healthynum - 1);
// 	}
// 	soildernum = tempwound + temphealth;
	int atk = floor(attackinfo.Atk + 0.5f);
	float perc = (float)((atk - def) + ATKROLL - DEFBOUSE) / ATKROLL;
	perc = (perc < 0.0f)? 0.0f:perc;
	perc = (perc > 1.0f)? 1.0f:perc;
	float killf = perc * attackinfo.AtkTime;
	killf += killf * (rand() % (attackinfo.Fluctuate * 2 + 1) - attackinfo.Fluctuate) / 100.0f;
	int kill = floor(killf + 0.5f);
	if(kill == 0)
	{
		if(rand() % 100 < attackinfo.Fluctuate)
			kill = 1;
	}
	soildernum -= kill;
	soildernum  = (soildernum < 0)? 0: soildernum;
	DataLibrary::getSingleton().setData(getPath() + std::string("/UnitNumber"),soildernum);
	if(soildernum == 0)
		OnEliminated();
	//DataLibrary::getSingleton().setData(getPath() + std::string("/WoundNum"),tempwound);
}

void BattleSquad::OnEliminated()
{
	TriggerContext* trigger = new TriggerContext("OnEliminated");
	TriggerManager::getSingleton().Trigger(getPath(),trigger);
	if(getUnitRealNum() == 0)
		mIsEliminated = true;
}

void BattleSquad::OnTurnEnd()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	mAmbushFaction[0] = mAmbushFaction[1] = mAmbushFaction[2] = mAmbushFaction[3] = false;
	DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushPlayer"),0);
	DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy1"),0);
	DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy2"),0);
	DataLibrary::getSingleton().setData(getPath() + std::string("/AmbushEnemy3"),0);
// 	std::vector<std::string> triggerlist;
// 	triggerlist = datalib->getChildList(getPath() + std::string("/Trigger"));
// 	if(triggerlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
// 		{
// 			std::string datapath = getPath() + std::string("/Trigger/") + (*ite);
// 			int active;
// 			datalib->getData(datapath ,active);
// 			if(!active)
// 				continue;
// 			std::string type;
// 			datalib->getData(datapath + std::string("/type"),type);
// 			if(type != "TurnEnd")
// 				continue;
// 			std::string context,filename,funcname;
// 			datalib->getData(datapath + std::string("/file"),filename);
// 			datalib->getData(datapath + std::string("/func"),funcname);
// 			datalib->getData(datapath + std::string("/context"),context);
// 			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
// 		}
// 	}
	TriggerContext* trigger = new TriggerContext("TurnEnd");
	TriggerManager::getSingleton().Trigger(getPath(),trigger);
}

int BattleSquad::getTeamFaction(int team)
{
	std::string temppath,tempstr;
	temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(team) + std::string("/Relation");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	if(tempstr == "alliance")
		return 0;
	else if(tempstr == "player")
		return 0;
	else if(tempstr == "enemy1")
		return 1;
	else if(tempstr == "enemy2")
		return 2;
	else if(tempstr == "enemy3")
		return 3;
	return 0;
}

