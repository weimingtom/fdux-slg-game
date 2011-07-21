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
	unsigned short enemySquadGroupId = 0;
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
				mEnemySquadGroup.insert(SquadGroupMap::value_type(++enemySquadGroupId,squadgroup));
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
}

bool BattleAIState::executeStrategy()
{
	updateMission();
	assignMission();
	return false;
}

void BattleAIState::updateMission()
{
	//删除被删除的小队组相关的任务
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