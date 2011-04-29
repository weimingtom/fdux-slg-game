#include "BattleSquad.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AVGSquadManager.h"
#include "MapDataManager.h"

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
	DataLibrary::getSingleton().setData(std::string("GameData/BattleData/SquadList/") + mId + std::string("/Direction"),d);
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
	int squadtype;
	DataLibrary::getSingleton().getData(getPath() + std::string("/Type"),squadtype);
	int unitnum;
	DataLibrary::getSingleton().getData(getPath() + std::string("/UnitNumber"),unitnum);
	if(squadtype == 1)
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
	float ap;
	AVGSquadManager::getSingleton().getSquadAttr(getPath(),ATTR_ACTIONPOINT,ATTRCALC_FULL ,ap);
	DataLibrary::getSingleton().setData(getPath() + std::string("/ActionPoint"),ap);
}

int BattleSquad::getTeam()
{
	return mTeam;
}