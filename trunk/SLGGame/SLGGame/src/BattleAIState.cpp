#include "BattleAIState.h"

#include "BattleState.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "squaddefine.h"
#include "Core.h"
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
	mMidX = xx / mSquadList.size();
	mMidY = yy / mSquadList.size();
	if(mSquadList.size()>0)
		return true;
	return false;
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
	ap = (*ite)->getActionPoint();
	for(; ite != mSquadList.end(); ite++)
	{
		if((*ite)->getActionPoint() < ap)
			ap = (*ite)->getActionPoint();
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
	mMissionId = 0;
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
	mEnmeySquadGroupId = 0;
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
				mEnemySquadGroup.insert(SquadGroupMap::value_type(++mEnmeySquadGroupId,squadgroup));
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
		if((*sqdite)->getTeam() == mTeam)
			continue;
		else if(BattleSquad::getTeamFaction(mTeam) != BattleSquad::getTeamFaction((*sqdite)->getTeam()) && (*sqdite)->viewbyTeam(mTeam) == true)
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
					mEnemySquadGroup.insert(SquadGroupMap::value_type(++mEnmeySquadGroupId,squadgroup));
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
		std::vector<int> nearsquadgroup;
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
		if(mysize > groupsize)
		{
			Mission* newmission = new Mission;
			newmission->mMisstionType = MISSION_ATTACK;
			newmission->mParaList[0] = ite->first;
			newmission->mParaList[1] = groupsize + 2;
			mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
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
			}
		}
		else if(groupsize <= lowestsize)
		{
			Mission* newmission = new Mission;
			newmission->mMisstionType = MISSION_ASSAULT;
			newmission->mParaList[0] = ite->first;
			newmission->mParaList[1] = groupsize;
			mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
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
			rallyx /= (*mostgroup).size();
			rallyy /= (*mostgroup).size();
			Ogre::Vector2 vec(rallyx - midx, rallyy - midy);
			vec.normalise();
			vec = vec * 6;
			Mission* newmission = new Mission;
			newmission->mMisstionType = MISSION_RALLY;
			newmission->mParaList[0] = ite->first;
			newmission->mParaList[1] = groupsize + 1;
			newmission->mParaList[2] = midx + vec.x;
			newmission->mParaList[3] = midy + vec.y;
			mMissionMap.insert(MissionMap::value_type(mMissionId++,newmission));
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
				interest -= getBlockSquadNum(mx,my,missionx,missiony,true, missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_RALLY:
				interest -= getDistance(mx,my,missionite->second->mParaList[2],missionite->second->mParaList[3]);
				interest -= getBlockSquadNum(mx,my,missionite->second->mParaList[2],missionite->second->mParaList[3],true, missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_ATTACK:
				tempsgite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
				if(tempsgite == mEnemySquadGroup.end())
					break;
				tempsgite->second->getMidPoint(missionx,missiony);
				interest -= getDistance(mx,my,missionx,missiony);
				interest -= getBlockSquadNum(mx,my,missionx,missiony,true, missionite->second->mParaList[0]);
				interest += 3 * (missionite->second->mParaList[1]  - getMissionStrength(missionite->first));
				interestmap.insert(std::map<unsigned short,unsigned short>::value_type(missionite->first,interest));
				break;
			case MISSION_ASSAULT:
				tempsgite = mEnemySquadGroup.find(missionite->second->mParaList[0]);
				if(tempsgite == mEnemySquadGroup.end())
					break;
				tempsgite->second->getMidPoint(missionx,missiony);
				interest -= getDistance(mx,my,missionx,missiony);
				interest -= getBlockSquadNum(mx,my,missionx,missiony,true, missionite->second->mParaList[0]);
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
	Direction d;
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
		if(isenemy && ite->second->mParaList[1] == id)
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

unsigned short BattleAIState::getBlockSquadNum(int x1, int y1, int x2, int y2, bool ignore,unsigned short ignoreid )
{
	unsigned short squadnum = 0;
	Ogre::Vector2 vec(x2 - x1, y2 - y1);
	SquadGroupIte ite;
	for(ite= mEnemySquadGroup.begin(); ite != mEnemySquadGroup.end();ite++)
	{
		if(ignore && ignoreid == ite->first)
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

bool BattleAIState::executeGroupAI()
{
	SquadGroupIte mygraoupite;
	for(mygraoupite = mMySquadGroup.begin(); mygraoupite != mMySquadGroup.end(); mygraoupite++)
	{
		SquadVector squadvec = mygraoupite->second->getSquadList();
	}
	return false;
}

bool BattleAIState::executeSquadAI(unsigned int missionid)
{

	return false;
}