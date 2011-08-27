#include "BattleAIState.h"

#include "BattleState.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "squaddefine.h"
#include "Core.h"
#include "DataLibrary.h"
#include "Terrain.h"
#include "SquadGraphics.h"
#include "SquadGrapManager.h"
#include "cutscenediretor.h"
#include "FormationCutScence.h"
#include "MapDataManager.h"
#include "MoveCutScene.h"
#include "DirectionCutScene.h"

#include <boost/format.hpp>
//SquadGroup-----------------------
SquadGroup::SquadGroup(BattleSquad* squad)
{
	mSquadList.push_back(squad);
	squad->getCrood(&mMidX,&mMidY);
}
SquadGroup::~SquadGroup()
{

}

bool SquadGroup::addSquad(BattleSquad* squad)
{
	bool added = false;
	int xx = 0, yy = 0;
	int nx,ny;
	squad->getCrood(&nx,&ny);
	int x,y;
	SquadIte ite = mSquadList.begin();
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		(*ite)->getCrood(&x,&y);
		if(!added)
		{
			if(abs(nx -x) + abs(ny -y) < 4)
				added = true;
		}
		xx += x;
		yy += y;
	}
	if(added)
	{
		mSquadList.push_back(squad);
		xx += nx;
		yy += ny;
	}
	 mMidX = xx / mSquadList.size();
	 mMidY = yy / mSquadList.size();
	 return added;
}

bool SquadGroup::IsInGroup(BattleSquad* squad)
{
	SquadIte ite = mSquadList.begin();
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		if((*ite) == squad)
			return true;
	}
	return false;
}

bool SquadGroup::updateSquad()
{
	SquadIte ite = mSquadList.begin();
	int xx = 0, yy = 0;
	for(ite = mSquadList.begin(); ite != mSquadList.end();)
	{
		if((*ite)->IsEliminated())
		{
			ite = mSquadList.erase(ite);
			continue;
		}
		int x,y;
		(*ite)->getCrood(&x,&y);
		xx += x;
		yy += y;
		ite++;
	}
	if(mSquadList.size() == 0)
		return false;
	mMidX = xx / mSquadList.size();
	mMidY = yy / mSquadList.size();
	return true;
}

unsigned int SquadGroup::getGroupSize()
{
	return mSquadList.size();
}

BattleSquad* SquadGroup::GetNearestFrom(int x, int y)
{
	SquadIte ite = mSquadList.begin();
	BattleSquad* squad = (*ite);
	int xx,yy;
	squad->getCrood(&xx,&yy);
	ite++;
	for(; ite != mSquadList.end(); ite++)
	{
		int xxx,yyy;
		(*ite)->getCrood(&xxx,&yyy);
		if(abs(xxx - x) + abs(yyy - y) < abs(xx - x) + abs(yy - y))
		{
			squad = (*ite);
			squad->getCrood(&xx,&yy);
		}
	}
	return squad;
}
BattleSquad* SquadGroup::GetFurthestFrom(int x, int y)
{
	SquadIte ite = mSquadList.begin();
	BattleSquad* squad = (*ite);
	int xx,yy;
	squad->getCrood(&xx,&yy);
	ite++;
	for(; ite != mSquadList.end(); ite++)
	{
		int xxx,yyy;
		(*ite)->getCrood(&xxx,&yyy);
		if(abs(xxx - x) + abs(yyy - y) > abs(xx - x) + abs(yy - y))
		{
			squad = (*ite);
			squad->getCrood(&xx,&yy);
		}
	}
	return squad;
}

float SquadGroup::getLowestAp()
{
	float ap;
	SquadIte ite = mSquadList.begin();
	ap = (*ite)->getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL,North);
	for(; ite != mSquadList.end(); ite++)
	{
		if((*ite)->getActionPoint() < ap)
			ap = (*ite)->getAttr(ATTR_ACTIONPOINT,ATTRCALC_FULL,North);
	}
	return ap;
}

SquadGroup::SquadVector SquadGroup::getSquadList()
{
	return mSquadList;
}

void SquadGroup::getMidPoint(int &x, int &y)
{
	x = mMidX;
	y = mMidY;
}

//BattleAIState--------------------
BattleAIState::BattleAIState(int team)
{
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mTeam = team;
	mMissionId = 1;
}
BattleAIState::~BattleAIState()
{
	clearSquadGroup();
	MissionIte ite;
	for(ite= mMissionMap.begin(); ite != mMissionMap.end(); ite ++)
	{
		delete ite->second;
	}
}

void BattleAIState::update(unsigned int deltaTime)
{
	updateSquadGroup();
	if(!executeStrategy())
		mMainState->PopState();
}

void BattleAIState::newTurn()
{
	unsigned short mySquadGroupId = 0;
	mEnmeySquadGroupId = 1;
	for(int n = 0; n < mSquadManager->mSquadList.size(); n++)
	{
		if(mSquadManager->mSquadList[n]->getTeam() == mTeam)
			mSquadManager->mSquadList[n]->newTurn();
	}

	SquadIte ite;
	for(ite = mSquadManager->mSquadList.begin(); ite != mSquadManager->mSquadList.end(); ite++)
	{
		if((*ite)->IsEliminated())
			continue;
		if((*ite)->getTeam() == mTeam)
		{
			bool added = false;
			SquadGroupIte sgite;
			for(sgite = mMySquadGroup.begin();sgite!= mMySquadGroup.end();sgite++)
			{
				if(sgite->second->addSquad((*ite)))
				{
					added = true;
					break;
				}
			}
			if(!added)
			{
				SquadGroup* squadgroup = new SquadGroup((*ite));
				mMySquadGroup.insert(SquadGroupMap::value_type(++mySquadGroupId,squadgroup));
			}
		}
		else if(BattleSquad::getTeamFaction(mTeam) != BattleSquad::getTeamFaction((*ite)->getTeam()) && (*ite)->viewbyTeam(mTeam) == true)
		{
			bool added = false;
			SquadGroupIte sgite;
			for(sgite = mEnemySquadGroup.begin();sgite!= mEnemySquadGroup.end();sgite++)
			{
				if(sgite->second->addSquad((*ite)))
				{
					added = true;
					break;
				}
			}
			if(!added)
			{
				SquadGroup* squadgroup = new SquadGroup((*ite));
				mEnemySquadGroup.insert(SquadGroupMap::value_type(mEnmeySquadGroupId++,squadgroup));
			}
		}
	}
}

void BattleAIState::clearSquadGroup()
{
	SquadGroupIte ite;
	for(ite= mMySquadGroup.begin(); ite != mMySquadGroup.end(); ite++)
		delete ite->second;
	mMySquadGroup.clear();
	for(ite= mEnemySquadGroup.begin(); ite != mEnemySquadGroup.end(); ite++)
		delete ite->second;
	mEnemySquadGroup.clear();
}

void BattleAIState::updateSquadGroup()
{
	SquadGroupIte ite;
	for(ite= mMySquadGroup.begin(); ite != mMySquadGroup.end();)
	{
		if(ite->second->updateSquad())
			ite++;
		else
		{
			delete ite->second;
			ite = mMySquadGroup.erase(ite);
		}
	}
	for(ite= mEnemySquadGroup.begin(); ite != mEnemySquadGroup.end();)
	{
		if(ite->second->updateSquad())
			ite++;
		else
		{
			delete ite->second;
			ite = mEnemySquadGroup.erase(ite);
		}
	}
	//寻找未加入的小队
	SquadIte sqdite;
	for(sqdite = mSquadManager->mSquadList.begin(); sqdite != mSquadManager->mSquadList.end(); sqdite++)
	{
		if((*sqdite)->IsEliminated())
			continue;
		int xxx = 0,yyy = 0;
		(*sqdite)->getCrood(&xxx,&yyy);
		Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:SquadPos,%1%,%2%,%3%")%(*sqdite)->getId()%xxx%yyy),Ogre::LML_NORMAL);
		if((*sqdite)->getTeam() == mTeam)
			continue;
		if(BattleSquad::getTeamFaction(mTeam) != BattleSquad::getTeamFaction((*sqdite)->getTeam()) && (*sqdite)->viewbyTeam(mTeam) == true)
		{
			bool added = false;
			SquadGroupIte sgite;
			for(sgite = mEnemySquadGroup.begin();sgite!= mEnemySquadGroup.end();sgite++)
			{
				if(sgite->second->IsInGroup((*sqdite)))
				{
					added = true;
					break;
				}
			}
			if(!added)
			{
				for(sgite = mEnemySquadGroup.begin();sgite!= mEnemySquadGroup.end();sgite++)
				{
					if(sgite->second->addSquad((*sqdite)))
					{
						added = true;
						break;
					}
				}
				if(!added)
				{
					SquadGroup* squadgroup = new SquadGroup((*sqdite));
					mEnemySquadGroup.insert(SquadGroupMap::value_type(mEnmeySquadGroupId++,squadgroup));
				}
			}
		}
	}
}

bool BattleAIState::executeStrategy()
{
	updateMission();
	assignMission();
	return executeGroupAI();
}

void BattleAIState::updateMission()
{
	//删除被删除的小队组相关的任务
	MissionIte missionite;
	for(missionite= mMissionMap.begin(); missionite != mMissionMap.end();)
	{
		SquadGroupIte squadgroupite;
		squadgroupite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
		if(squadgroupite == mEnemySquadGroup.end())
		{
			delete missionite->second;
			missionite = mMissionMap.erase(missionite);
			continue;
		}
		if(missionite->second->mMisstionType == MISSION_ASSIST )
		{
			squadgroupite = mMySquadGroup.find(missionite->second->mParaList[2]);
			if(squadgroupite == mMySquadGroup.end())
			{
				delete missionite->second;
				missionite = mMissionMap.erase(missionite);
				continue;
			}
		}
		missionite ++;
	}
	
	
	//规划新的任务
	SquadGroupIte ite;
	for(ite= mEnemySquadGroup.begin(); ite != mEnemySquadGroup.end();ite++)
	{
		//如果已被指定任务，跳过
		if(getAssigedMission(true,ite->first))
			continue;
		//制定相应任务
		int midx,midy;
		ite->second->getMidPoint(midx,midy);
		unsigned int groupsize = ite->second->getGroupSize();
		SquadGroupIte mysquadite;
		unsigned int mysize = 0;
		std::vector<unsigned short> nearsquadgroup;
		unsigned int lowestsize = 0;
		for(mysquadite= mMySquadGroup.begin(); mysquadite != mMySquadGroup.end();mysquadite++)
		{
			int mymidx,mymidy;
			mysquadite->second->getMidPoint(mymidx,mymidy);
			if(lowestsize == 0 || mysquadite->second->getGroupSize() < lowestsize)
				lowestsize = mysquadite->second->getGroupSize();
			if(abs(midx - mymidx) + abs(midy - mymidy) < 6)
			{
				mysize += mysquadite->second->getGroupSize();
				if(mysize < groupsize && (mysquadite->second->getLowestAp() < 4.0f || abs(midx - mymidx) + abs(midy - mymidy) < 3))
					nearsquadgroup.push_back(mysquadite->first);
			}
		}
		if(mysize >= groupsize)
		{
			Mission* newmission = new Mission;
			newmission->mMisstionType = MISSION_ATTACK;
			newmission->mParaList[0] = ite->first;
			newmission->mParaList[1] = groupsize + 2;
			mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
			Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:Mission%1%,Attack,%2%,%3%")%(mMissionId-1)%newmission->mParaList[0]%newmission->mParaList[1]),Ogre::LML_NORMAL);
		}
		else if(nearsquadgroup.size() > 0)
		{
			for(unsigned int n = 0; n < nearsquadgroup.size(); n++)
			{
				Mission* newmission = new Mission;
				newmission->mMisstionType = MISSION_ASSIST;
				newmission->mParaList[2] = nearsquadgroup[n];
				newmission->mParaList[1] = groupsize;
				newmission->mParaList[0] = ite->first;
				mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
				Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:Mission%1%,Assist,%2%,%3%,%4%")%(mMissionId-1)%newmission->mParaList[0]%newmission->mParaList[1]%newmission->mParaList[2]),Ogre::LML_NORMAL);
			}
		}
		else if(groupsize <= lowestsize)
		{
			Mission* newmission = new Mission;
			newmission->mMisstionType = MISSION_ASSAULT;
			newmission->mParaList[0] = ite->first;
			newmission->mParaList[1] = groupsize;
			mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
			Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:Mission%1%,Assault,%2%")%(mMissionId-1)%newmission->mParaList[0]),Ogre::LML_NORMAL);
		}
		else
		{
			std::vector<int> southgroup;
			std::vector<int> northgroup;
			std::vector<int> westgroup;
			std::vector<int> easthgroup;
			for(mysquadite= mMySquadGroup.begin(); mysquadite != mMySquadGroup.end();mysquadite++)
			{
				if(getAssigedMission(false,mysquadite->first))
					continue;
				int mymidx,mymidy;
				mysquadite->second->getMidPoint(mymidx,mymidy);
				Direction d = getDirection(midx,midy,mymidx,mymidy);
				switch(d)
				{
				case South:
					southgroup.push_back(mysquadite->first);
					break;
				case North:
					northgroup.push_back(mysquadite->first);
					break;
				case West:
					westgroup.push_back(mysquadite->first);
					break;
				case East:
					easthgroup.push_back(mysquadite->first);
					break;
				}
			}
			//判断哪个方向队伍最多
			std::vector<int> *mostgroup;
			mostgroup = &southgroup;
			if(northgroup.size() > (*mostgroup).size())
				mostgroup = &northgroup;
			if(westgroup.size() > (*mostgroup).size())
				mostgroup = &westgroup;
			if(easthgroup.size() > (*mostgroup).size())
				mostgroup = &easthgroup;
			//计算集结点
			int rallyx = 0,rallyy = 0;
			for(unsigned int n= 0; n < (*mostgroup).size(); n++)
			{
				mysquadite = mMySquadGroup.find((*mostgroup)[n]);
				int myx,myy;
				mysquadite->second->getMidPoint(myx,myy);
				rallyx += myx;
				rallyy += myy;
			}
			if((*mostgroup).size() == 0)
			{
				Mission* newmission = new Mission;
				newmission->mMisstionType = MISSION_ATTACK;
				newmission->mParaList[0] = ite->first;
				newmission->mParaList[1] = groupsize + 2;
				mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
				Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:Mission%1%,Attack,%2%,%3%")%(mMissionId-1)%newmission->mParaList[0]%newmission->mParaList[1]),Ogre::LML_NORMAL);
			}
			else
			{
				rallyx /= (*mostgroup).size();
				rallyy /= (*mostgroup).size();
				Ogre::Vector2 vec(rallyx - midx, rallyy - midy);
				vec.normalise();
				vec = vec * 4;
				Mission* newmission = new Mission;
				newmission->mMisstionType = MISSION_RALLY;
				newmission->mParaList[0] = ite->first;
				newmission->mParaList[1] = groupsize + 1;
				newmission->mParaList[2] = midx + vec.x;
				newmission->mParaList[3] = midy + vec.y;
				mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
				Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:Mission%1%,Rally,%2%,%3%,%4%,%5%")%(mMissionId-1)%newmission->mParaList[0]%newmission->mParaList[1]%newmission->mParaList[2]%newmission->mParaList[3]),Ogre::LML_NORMAL);
			}
		}
	}
}

void BattleAIState::assignMission()
{
	SquadGroupIte ite;
	for(ite= mMySquadGroup.begin(); ite != mMySquadGroup.end();ite++)
	{
		if(getAssigedMission(false,ite->first))
			continue;
		std::map<unsigned short,unsigned short> interestmap;
		MissionIte missionite;
		for(missionite= mMissionMap.begin(); missionite != mMissionMap.end(); missionite ++)
		{
			if(missionite->second->mMisstionType == MISSION_ASSIST && missionite->second->mParaList[2] == ite->first)
			{
				interestmap.clear();
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,100));
				break;
			}
			unsigned short interest = 50;
			SquadGroupIte tempsgite;
			int my,mx;
			ite->second->getMidPoint(mx,my);
			int missionx,missiony;
			switch(missionite->second->mMisstionType)
			{
			case MISSION_ASSIST:
				tempsgite = mMySquadGroup.find(missionite->second->mParaList[2]);
				if(tempsgite == mMySquadGroup.end())
					break;
				tempsgite->second->getMidPoint(missionx,missiony);
				interest -= getDistance(mx,my,missionx,missiony);
				interest -= getBlockSquadNum(mx,my,missionx,missiony,missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_RALLY:
				interest -= getDistance(mx,my,missionite->second->mParaList[2],missionite->second->mParaList[3]);
				interest -= getBlockSquadNum(mx,my,missionite->second->mParaList[2],missionite->second->mParaList[3], 0);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_ATTACK:
				tempsgite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
				if(tempsgite == mEnemySquadGroup.end())
					break;
				tempsgite->second->getMidPoint(missionx,missiony);
				interest -= getDistance(mx,my,missionx,missiony);
				interest -= getBlockSquadNum(mx,my,missionx,missiony, missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_ASSAULT:
				tempsgite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
				if(tempsgite == mEnemySquadGroup.end())
					break;
				tempsgite->second->getMidPoint(missionx,missiony);
				interest -= getDistance(mx,my,missionx,missiony);
				interest -= getBlockSquadNum(mx,my,missionx,missiony, missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interest -= 2 * (int)abs((int)tempsgite->second->getGroupSize() - (int)ite->second->getGroupSize());
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			}

		}
		unsigned short mostinterest;
		unsigned short mostinterestid;
		if(interestmap.size() > 0)
		{
			std::map<unsigned short,unsigned short>::iterator intite = interestmap.begin();
			mostinterest = intite->second;
			mostinterestid = intite->first;
			for(;intite != interestmap.end(); intite++)
			{
				if(mostinterest < intite->second)
				{
					mostinterest = intite->second;
					mostinterestid = intite->first;
				}
			}
			missionite = mMissionMap.find(mostinterestid);
			if(missionite != mMissionMap.end())
				missionite->second->mAssigedGroup.push_back(ite->first);
		}
	}
}

Direction BattleAIState::getDirection(int sx, int sy, int x, int y)
{
	Direction d = North;
	if(!(sx == x && sy == y))
	{
		float k;
		if(y-sy == 0)
			k = 2.0f;
		else
			k = abs(x -sx)/ abs(y - sy);
		if( y > sy && k <= 1.0f)
			d = South;
		else if( y < sy && k <= 1.0f)
			d = North;
		else if( x > sx )
			d = East;
		else
			d = West;
	}
	return d;
}
bool BattleAIState::getAssigedMission(bool isenemy,unsigned short id)
{
	MissionIte ite;
	for(ite= mMissionMap.begin(); ite != mMissionMap.end(); ite ++)
	{
		if(isenemy && ite->second->mParaList[0] == id)
			return true;
		else
		{
			for(unsigned int n = 0;  n < ite->second->mAssigedGroup.size(); n++)
			{
				if(ite->second->mAssigedGroup[n] == id)
					return true;
			}
		}
	}
	return false;
}

int BattleAIState::getDistance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

unsigned short BattleAIState::getMissionStrength(unsigned short id)
{
	MissionIte ite;
	ite = mMissionMap.find(id);
	if(ite == mMissionMap.end())
		return 0;
	unsigned short s = 0;
	SquadGroupIte sqdite;
	for(int n = 0; n < ite->second->mAssigedGroup.size(); n++)
	{
		sqdite = mMySquadGroup.find(ite->second->mAssigedGroup[n]);
		if(sqdite == mMySquadGroup.end())
			continue;
		s += sqdite->second->getGroupSize();
	}
	return s;
}

unsigned short BattleAIState::getBlockSquadNum(int x1, int y1, int x2, int y2,unsigned short ignoreid )
{
	unsigned short squadnum = 0;
	Ogre::Vector2 vec(x2 - x1, y2 - y1);
	SquadGroupIte ite;
	for(ite= mEnemySquadGroup.begin(); ite != mEnemySquadGroup.end();ite++)
	{
		if( ignoreid == 0 || ignoreid == ite->first)
			continue;
		int x,y;
		ite->second->getMidPoint(x,y);
		Ogre::Vector2 vec2(x - x1, y - y1);
		if(vec2.length() > vec.length())
			continue;
		Ogre::Vector2 vec3 = vec;
		vec3.normalise();
		vec2.normalise();
		if(vec2.dotProduct(vec3)  > 0.5f)
			squadnum += ite->second->getGroupSize();
	}
	return squadnum;
}

unsigned short BattleAIState::getMission(unsigned short groupid)
{
	MissionIte ite;
	for(ite= mMissionMap.begin(); ite != mMissionMap.end(); ite ++)
	{
		for(unsigned int n = 0;  n < ite->second->mAssigedGroup.size(); n++)
		{
			if(ite->second->mAssigedGroup[n] == groupid)
				return ite->first;
		}
	}
	return 0;
}

float BattleAIState::getSkillAPCost(BattleSquad* squad, std::string skillname)
{
	if(squad == NULL)
		return -1.0f;
	if(skillname == "line" || skillname == "circular" || skillname == "loose")
	{
		return 2.0f + squad->getActionPointCost(0);
	}
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string skilltablepath = squad->getPath() + std::string("/SkillTable");
	std::vector<std::string> skilllist = datalib->getChildList(skilltablepath);
	std::vector<std::string>::iterator ite;
	ite = std::find(skilllist.begin(),skilllist.end(),skillname);
	if(ite == skilllist.end())
		return -1.0f;
	SkillType skilltype;
	bool re = datalib->getData(std::string("StaticData/SkillData/")+ skillname + std::string("/Type"),skilltype);
	if(skilltype == SKILLTYPE_PASSIVE)
		return -1.0f;
	int cooldown;
	datalib->getData(squad->getPath() + std::string("/SkillTable/") + skillname + std::string("/CoolDown"),cooldown);
	if(cooldown > 0)
		return -1.0f;
	int aptype ;
	datalib->getData(std::string("StaticData/SkillData/")+ skillname+ std::string("/APType"),aptype);
	float apcost;
	datalib->getData(std::string("StaticData/SkillData/")+ skillname+ std::string("/APCost"),apcost);
	
	apcost += squad->getActionPointCost(aptype);

	return apcost;
}

bool BattleAIState::executeGroupAI()
{
	SquadGroupIte mygraoupite;
	for(mygraoupite = mMySquadGroup.begin(); mygraoupite != mMySquadGroup.end(); mygraoupite++)
	{
		SquadVector squadvec = mygraoupite->second->getSquadList();
		SquadIte squadite;
		for(squadite = squadvec.begin(); squadite != squadvec.end(); squadite++)
		{
			if(executeSquadAI((*squadite),getMission(mygraoupite->first)))
				return true;
		}
	}
	return false;
}

bool BattleAIState::executeSquadAI(BattleSquad* squad,unsigned int missionid)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,APLeft,%2%")%squad->getId()%squad->getActionPoint()),Ogre::LML_NORMAL);
	if(squad->getActionPoint() < 2.0f)
	{
		MissionIte missionite = mMissionMap.find(missionid);
		if(missionite == mMissionMap.end())
			return false;
		SquadGroupIte sgite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
		if(sgite == mEnemySquadGroup.end())
			return false;
		int x1,y1,x2,y2;
		squad->getCrood(&x1,&y1);
		BattleSquad* squad1 = sgite->second->GetNearestFrom(x1,y1);
		squad1->getCrood(&x2,&y2);
		Direction d1 = squad->getDirection();
		Direction d2 = getDirection(x1,y1,x2,y2);
		if(d1 == d2)
			return false;
		Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,ChangeDirection,%2%")%squad->getId()%d2),Ogre::LML_NORMAL);
		squad->setDirection(d2);
		CutSceneDirector* cutscenedirector = new CutSceneDirector;
		DirectionCutScene* directioncutscene = new DirectionCutScene(squad->getGrapId(), d2);
		cutscenedirector->addCutScene(directioncutscene);
		mMainState->PushState(cutscenedirector);
		return true;
	}
	int wondnum = 0;
	int unitnum = squad->getUnitRealNum();
	DataLibrary::getSingleton().getData(squad->getPath() + std::string("/WoundNum"),wondnum);
	if(squad->getFormation() != Line && squad->getActionPoint() >= getSkillAPCost(squad, "line"))
	{
		//切换阵形
		Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,ChangeFormation,%2%")%squad->getId()%Line),Ogre::LML_NORMAL);
		float apcost = getSkillAPCost(squad, "line");
		float apleft = squad->getActionPoint();
		DataLibrary::getSingleton().setData(squad->getPath() + std::string("/ActionPoint"),apleft);
		DataLibrary::getSingleton().setData(squad->getPath() + std::string("/APSetup"),apcost);
		squad->setFormation(Line);
		CutSceneDirector* cutscenedirector = new CutSceneDirector;
		FormationCutScene* formcutscene = new FormationCutScene(squad->getGrapId(), Line);
		cutscenedirector->addCutScene(formcutscene);
		mMainState->PushState(cutscenedirector);
		return true;
	}
	createMoveArea(squad);
	int myx,myy;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	squad->getCrood(&myx,&myy);
	MoveNode* startnode = new MoveNode;
	startnode -> x = myx;
	startnode -> y = myy;
	startnode->mAPleft = squad->getActionPoint();
	mMoveMap.insert(MapNodeType(myx + mapsize * myy,startnode));
	bool action = false;
	//计算移动点移动偏好
	if(wondnum > std::min(15,unitnum/2) && unitnum > 10)
	{
		//避战休息
		calcAwayFromSquad(squad);
		calcAPointLeft(squad);
	}
	else
	{
		//执行任务
		MissionIte missionite = mMissionMap.find(missionid);
		if(missionite != mMissionMap.end())
		{
			switch(missionite->second->mMisstionType)
			{
			case MISSION_ASSIST:
				calcAwayFromSquad(squad, missionite->second->mParaList[0]);
				calcAPointLeft(squad);
				calcBattlePos(squad,missionite->second->mParaList[0]);
				calcClosetoMissionPoint(squad,missionid);
				break;
			case MISSION_ATTACK:
				calcAwayFromSquad(squad, missionite->second->mParaList[0]);
				calcAPointLeft(squad);
				calcBattlePos(squad,missionite->second->mParaList[0]);
				calcClosetoMissionPoint(squad,missionid);
				break;
			case MISSION_RALLY:
				calcAwayFromSquad(squad);
				calcAPointLeft(squad);
				calcClosetoMissionPoint(squad,missionid);
				break;
			case MISSION_ASSAULT:
				calcAwayFromSquad(squad, missionite->second->mParaList[0]);
				calcAPointLeft(squad);
				calcBattlePos(squad,missionite->second->mParaList[0]);
				calcClosetoMissionPoint(squad,missionid);
				break;
			}
		}
		else
		{
			clearMoveArea();
			return false;
		}
	}
	//寻找最偏好移动点移动
	MoveNode* ilovethisnode;
	MapNodeIte movenodeite= mMoveMap.begin();
	ilovethisnode = movenodeite->second;
	for(; movenodeite != mMoveMap.end(); movenodeite++)
	{
		if(movenodeite->second->mInterest > ilovethisnode->mInterest)
			ilovethisnode = movenodeite->second;
	}
	if(ilovethisnode->x != myx || ilovethisnode->y != myy)
	{
		int xx = ilovethisnode->x,yy = ilovethisnode->y;
		std::vector<int> croodlistrev;
		while(xx != myx || yy !=myy)
		{
			MapNodeIte ite;
			ite = mMoveMap.find(xx + yy * mapsize);
			croodlistrev.push_back(xx);
			croodlistrev.push_back(yy);
			Direction d = ite->second->mDirectionToPrev;
			switch(d)
			{
			case North:
				yy -= 1;
				break;
			case South:
				yy += 1;
				break;
			case East:
				xx += 1;
				break;
			case West:
				xx -= 1;
				break;
			}
		}
		std::vector<int> croodlist;
		int xxx,yyy;
		while(croodlistrev.size()>0)
		{
			yyy = croodlistrev.back();
			croodlistrev.pop_back();
			xxx = croodlistrev.back();
			croodlistrev.pop_back();
			croodlist.push_back(xxx);
			croodlist.push_back(yyy);
		}
		int stoppoint;
		int evt = 0;
		std::vector<Ogre::Vector2> movepath;
		BattleSquadManager::getSingleton().moveSquad(squad, croodlist, stoppoint, evt);
		Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,Move,%2%,%3%")%squad->getId()%myx%myy),Ogre::LML_NORMAL);
		int n;
		for(n = 0; n *2 < croodlist.size(); n++)
		{
			if(stoppoint > n)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,%2%")%croodlist[n*2]%croodlist[n*2+1]),Ogre::LML_NORMAL);
				movepath.push_back(Ogre::Vector2(croodlist[n*2],croodlist[n*2+1]));
			}
		}
		CutScene* eventcutscene = mSquadManager->getCutScene();
		MoveCutScene* movecutscene = new MoveCutScene(squad->getGrapId(),movepath,Ogre::Vector2(myx,myy));
		mSquadManager->setCutScene(movecutscene);
		DirectionCutScene* dircutscene = new DirectionCutScene(squad->getGrapId(),squad->getDirection());
		mSquadManager->setCutScene(dircutscene);
		mSquadManager->setCutScene(eventcutscene);
		if(stoppoint != n )
			action = false;
		else
			action = true;

	}
	else
		action = true;
	clearMoveArea();
	//执行行为
	if(action == false)
	{
		CutScene* catscene = mSquadManager->getCutScene();
		if(catscene != NULL)
		{
			CutSceneDirector* director  = new CutSceneDirector;
			director->addCutScene(catscene);
			mMainState->PushState(director);
			return true;
		}
		return false;
	}
	else
	{
		CutScene* catscene = NULL;
		if(squad->getActionPoint() >= 2.0f)
		{
			SquadVector vec = getAroundSquad(squad);
			if(vec.size() == 0 || squad->getActionPoint() <= getSkillAPCost(squad,"Attack"))
			{
				if(wondnum > std::min(15,unitnum/2) && unitnum > 10)
				{
					Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,Rest")%squad->getId()),Ogre::LML_NORMAL);
					catscene = mSquadManager->useSkillOn(squad,squad,"Rest");
				}
				else
				{
					Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,Defence")%squad->getId()),Ogre::LML_NORMAL);
					catscene = mSquadManager->useSkillOn(squad,squad,"Defence");
				}
			}
			else
			{
				SquadIte sqdite = vec.begin();
				BattleSquad* attack = (*sqdite);
				for(; sqdite != vec.end(); sqdite++)
				{
					if(attack->getUnitRealNum() > (*sqdite)->getUnitRealNum())
						attack = (*sqdite);
				}
				Ogre::LogManager::getSingletonPtr()->logMessage(str(boost::format("AI:%1%,Attack,%2%")%squad->getId()%attack->getId()),Ogre::LML_NORMAL);
				catscene = mSquadManager->useSkillOn(squad,attack,"Attack");
			}
			
		}
		else
			catscene = mSquadManager->getCutScene();
		if(catscene != NULL)
		{
			CutSceneDirector* director  = new CutSceneDirector;
			director->addCutScene(catscene);
			mMainState->PushState(director);
			return true;
		}
		return false;
	}
	return false;
}

void BattleAIState::createMoveArea(BattleSquad* squad)
{
	int startx,starty;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	squad->getCrood(&startx,&starty);
	std::vector<int> coordlist;
	coordlist.push_back(startx);
	coordlist.push_back(starty);
	//寻找可以移动的路径
	int n = 0;
	bool finding = true;
	while(finding)
	{
		if(n*2 < coordlist.size())
		{
			int x = coordlist[n*2];
			int y = coordlist[n*2 +1];
			float apleft;
			if(x == startx && y == starty)
				apleft = squad->getActionPoint();
			else
			{
				MapNodeIte ite;
				ite = mMoveMap.find(x + y * mapsize);
				if(ite == mMoveMap.end())
				{
					finding = false;
					break;
				}
				else
					apleft = ite->second->mAPleft;
			}
			int xx,yy;
			float apcost = apleft;
			xx = x - 1;
			yy = y;
			bool passable = canPass(squad,xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = East;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = East;
				}
			}
			xx = x + 1;
			yy = y;
			apcost = apleft;
			passable = canPass(squad,xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = West;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = West;
				}
			}
			xx = x;
			yy = y - 1;
			apcost = apleft;
			passable = canPass(squad,xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = South;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = South;
				}
			}
			xx = x;
			yy = y + 1;
			apcost = apleft;
			passable = canPass(squad,xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = North;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = North;
				}
			}
		}
		else
			finding = false;
		n++;
	}
}
bool BattleAIState::canPass(BattleSquad* squad,int x, int y, float &apcost)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	MapNodeIte ite;
	ite = mMoveMap.find(x + y * mapsize);
	if(ite != mMoveMap.end())
	{
		if(ite->second->mPrevApLeft >= apcost)
			return false;
	}
	else
	{
		if(!mapdata->getPassable(x,y,BattleSquad::getTeamFaction(mTeam)))
			return false;
		BattleSquad* blocksquad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,mTeam,true);
		if(blocksquad)
			return false;
	}
	std::string horse;
	DataLibrary::getSingleton().getData(squad->getPath() + std::string("/HorseId"),horse);
	float apleft = apcost;
	if(horse == "none")
		apcost = mapdata->getInfApCost(x,y,0);
	else
		apcost = mapdata->getCavApCost(x,y,0);
	if(apleft >= apcost)
		return true;
	return false;
}

void BattleAIState::clearMoveArea()
{
	MapNodeIte movenodeite;
	for(movenodeite = mMoveMap.begin(); movenodeite != mMoveMap.end(); movenodeite++)
	{
		delete movenodeite->second;
	}
	mMoveMap.clear();
}

void BattleAIState::calcAwayFromSquad(BattleSquad* squad, unsigned short ignoreid)
{
	MapNodeIte nodeite;
	for(nodeite = mMoveMap.begin(); nodeite != mMoveMap.end(); nodeite++)
	{
		SquadGroupIte groupite;
		for(groupite = mEnemySquadGroup.begin(); groupite != mEnemySquadGroup.end(); groupite++)
		{
			if(groupite->first == ignoreid || groupite->second->getGroupSize() < 2)
				continue;
			int x,y;
			groupite->second->getMidPoint(x,y);
			int dist = getDistance(nodeite->second->x,nodeite->second->y,x,y);
			if(dist < 4)
				nodeite->second->mInterest -= dist;
		}
	}
}

void BattleAIState::calcClosetoMissionPoint(BattleSquad* squad, unsigned int missionid)
{
	MissionIte missionite = mMissionMap.find(missionid);
	if(missionite == mMissionMap.end())
		return;
	int myposx,myposy;
	squad->getCrood(&myposx,&myposy);
	int missionx = myposx,missiony = myposy;
	SquadGroupIte groupite;
	switch(missionite->second->mMisstionType)
	{
	case MISSION_ASSIST:
		groupite = mMySquadGroup.find(missionite->second->mParaList[2]);
		if(groupite == mMySquadGroup.end())
			return;
		groupite->second->getMidPoint(missionx,missiony);
		break;
	case MISSION_ATTACK:
	case MISSION_ASSAULT:
		groupite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
		if(groupite == mEnemySquadGroup.end())
			return;
		groupite->second->getMidPoint(missionx,missiony);
		break;
	case MISSION_RALLY:
		missionx = missionite->second->mParaList[2];
		missiony = missionite->second->mParaList[3];
		break;
	}
	int distomission = getDistance(myposx,myposy,missionx,missiony);
	MapNodeIte nodeite;
	for(nodeite = mMoveMap.begin(); nodeite != mMoveMap.end(); nodeite++)
	{
		int dist = getDistance(nodeite->second->x,nodeite->second->y,missionx,missiony);
		if(distomission - dist >= 0)
			nodeite->second->mInterest += (distomission - dist) * 2;
		else
			nodeite->second->mInterest -= (dist - distomission) * 2;
	}
}
void BattleAIState::calcAPointLeft(BattleSquad* squad)
{
	MapNodeIte nodeite;
	for(nodeite = mMoveMap.begin(); nodeite != mMoveMap.end(); nodeite++)
	{
		if(nodeite->second->mAPleft < 4.0f)
			nodeite->second->mInterest -= 2 * (4.0f - nodeite->second->mAPleft) ;
	}
}
void BattleAIState::calcBattlePos(BattleSquad* squad, unsigned squadgroupid)
{
	MapNodeIte nodeite;
	for(nodeite = mMoveMap.begin(); nodeite != mMoveMap.end(); nodeite++)
	{
		SquadGroupIte groupite;
		for(groupite = mEnemySquadGroup.begin(); groupite!= mEnemySquadGroup.end(); groupite++)
		{
			SquadIte sqdite;
			SquadVector quadvec = groupite->second->getSquadList();
			for(sqdite = quadvec.begin(); sqdite != quadvec.end(); sqdite++)
			{
				int dist,x,y;
				(*sqdite)->getCrood(&x,&y);
				dist = getDistance(x,y,nodeite->second->x,nodeite->second->y);
				if(dist > 1)
					continue;
				if(groupite->first == squadgroupid)
				{
					Direction d;
					d = (*sqdite)->getDirection();
					unsigned short p[4];
					switch(d)
					{
					case North:
						p[0] = 2;
						p[1] = 4;
						p[2] = 6;
						p[3] = 4;
						break;
					case South:
						p[0] = 6;
						p[1] = 4;
						p[2] = 2;
						p[3] = 4;
						break;
					case West:
						p[0] = 4;
						p[1] = 6;
						p[2] = 4;
						p[3] = 2;
						break;
					case East:
						p[0] = 4;
						p[1] = 2;
						p[2] = 4;
						p[3] = 6;
						break;
					}
					if(nodeite->second->x > x)
						nodeite->second->mInterest += p[1];
					else if(nodeite->second->x < x)
						nodeite->second->mInterest += p[3];
					else if(nodeite->second->y < y)
						nodeite->second->mInterest += p[0];
					else
						nodeite->second->mInterest += p[2];
				}
			}
		}
	}
}

BattleAIState::SquadVector BattleAIState::getAroundSquad(BattleSquad* squad)
{
	SquadVector vec;
	SquadIte sqdite;
	int myx,myy;
	squad->getCrood(&myx,&myy);
	for(sqdite = mSquadManager->mSquadList.begin(); sqdite != mSquadManager->mSquadList.end(); sqdite++)
	{
		if((*sqdite)->IsEliminated())
			continue;
		if(BattleSquad::getTeamFaction(mTeam) == BattleSquad::getTeamFaction((*sqdite)->getTeam()))
			continue;
		if((*sqdite)->viewbyTeam(mTeam) == false)
			continue;
		int x,y;
		(*sqdite)->getCrood(&x,&y);
		if(getDistance(myx,myy,x,y) == 1)
			vec.push_back((*sqdite));
	}
	return vec;
}