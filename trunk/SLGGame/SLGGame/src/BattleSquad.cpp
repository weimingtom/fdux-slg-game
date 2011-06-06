#include "BattleSquad.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AVGSquadManager.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h" 

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
		side = 0;
		if(direction != mydirection)
		{
			switch(direction)
			{
			case North:
				if(mydirection != South)
					side = 1;
				else
					side = 2;
				break;
			case South:
				if(mydirection != North)
					side = 1;
				else
					side = 2;
				break;
			case West:
				if(mydirection != East)
					side = 1;
				else
					side = 2;
				break;
			case East:
				if(mydirection != West)
					side = 1;
				else
					side = 2;
				break;
			}
		}
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
		case 2:
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
		}
		attr = attr + form;
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
			form *= FORMBONSE_LINE_FRONT;
			break;
		case Circular:
			form *= FORMBONSE_CIRC_FRONT;
			break;
		case Loose:
			form *= FORMBONSE_LOOS_FRONT;
			break;
		}
		attr = attr + RANGEDDEFENCEBONUS - form;
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

bool BattleSquad::applyModifier(AttrModifier* modifier,std::string &id)
{
	return AVGSquadManager::getSingleton().applyModifer(getPath(), modifier, id);
}

bool BattleSquad::clearModifier(std::string id)
{
	return false;
}

int BattleSquad::getUnitGrapNum()
{
	SquadType squadtype;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Type"),squadtype);
	int unitnum;
	DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),unitnum);
	if(squadtype == SQUAD_NORMAL)
	{
		return unitnum/10; 
	}
	else
	{
		return unitnum/10 + 1;
	}
	
}

void BattleSquad::newTurn()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	float ap;
	AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_ACTIONPOINT,ATTRCALC_FULL ,ap);
	datalib->setData(getPath() + std::string("/ActionPoint"),ap);
	datalib->setData(getPath() + std::string("/APSetup"),0.0f);
	datalib->setData(getPath() + std::string("/APBattle"),0.0f);
	//计算隐藏

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
	return mViewbyFaction[team];
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
	float apcost;
	if(type == SKILLAPTYPE_SETUP)
		DataLibrary::getSingleton().getData(getPath() + std::string("/APSetup"),apcost);
	else
		DataLibrary::getSingleton().getData(getPath() + std::string("/APBattle"),apcost);
	return apcost;
}