#include "BattleAIState.h"

#include "BattleState.h"

#include <boost/format.hpp>

#include "DataLibrary.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CommonFunction.h"

BattleAIState::BattleAIState(int team)
:mTeam(team),mState(AISTATE_INIT)
{

}
BattleAIState::~BattleAIState()
{
	std::map<int, MapArea*>::iterator ite = mAreaVec.begin();
	for(; ite != mAreaVec.end(); ite++)
	{
		delete ite->second;
	}
	mAreaVec.clear();

	std::map<int, SquadGroup*>::iterator ite1 = mSquadGroupVec.begin();
	for(; ite1 != mSquadGroupVec.end(); ite1++)
	{
		delete ite1->second;
	}
	mSquadGroupVec.clear();
}

void BattleAIState::update(unsigned int deltaTime)
{
	switch(mState)
	{
	case AISTATE_INIT:
		if(!AnalyzeMap())
		{
			mMainState->PopState();
			return;
		}

		AnalyzeOtherTeam();

		mState = AISTATE_EXECUTE;
		break;
	case AISTATE_EXECUTE:

		SaveOtherTeamInfo();

		mMainState->PopState();
		mState = AISTATE_SHUTDOWN;
		break;
	case AISTATE_SHUTDOWN:
		break;
	}
}
	

BattleAIState::MapArea::MapArea()
{
	mType = AreaType_Plane;
}

BattleAIState::MapArea::~MapArea()
{

}

void BattleAIState::MapArea::AddCrood(int x, int y)
{
	mArea.push_back(MapCrood(x, y));
}

bool BattleAIState::AnalyzeMap()
{
	if(!ReadMap())
	{
		return CreateMap();
	}
	return true;
}

bool BattleAIState::ReadMap()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapanalyzed = 0;
	if(!datalib->getData("GameData/BattleData/AIData/MapAnalyze", mapanalyzed, true))
	{
		return false;
	}
	std::vector<std::string> arealist = datalib->getChildList("GameData/BattleData/AIData/MapAnalyze");
	std::vector<std::string>::iterator areaite = arealist.begin();
	int areaid = 0;
	for(;areaite != arealist.end(); areaite++)
	{
		MapArea* maparea = new MapArea;
		datalib->getData(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%")%(*areaite)), maparea->mType);
		std::vector<std::string> croodlist = 
			datalib->getChildList(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%/Area")%(*areaite)));
		std::vector<std::string>::iterator croodite = croodlist.begin();
		for(;croodite != croodlist.end(); croodite++)
		{
			int x,y,croodid;
			datalib->getData(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%/Area/%2%")%(*areaite)%(*croodite)),croodid);
			mapdata->getCrood(croodid, x, y);
			maparea->AddCrood(x, y);
		}
		croodlist = 
			datalib->getChildList(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%/ConnectedArea")%(*areaite)));
		for(croodite = croodlist.begin(); croodite != croodlist.end(); croodite++)
		{
			int connectedareaid;
			datalib->getData(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%/ConnectedArea/%2%")%(*areaite)%(*croodite)),connectedareaid);
			maparea->mConnectedArea.push_back(connectedareaid);
		}
		mAreaVec.insert(std::make_pair(areaid++, maparea));
	}
	return true;
}

bool BattleAIState::CreateMap()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();

	int mapsize = mapdata->getMapSize();
	std::map<int, bool> passablemap;
	std::map<int, bool> areamap1;
	std::map<int, bool> areamap2;
	for(int x = 0; x < mapsize; x++)
	{
		for(int y = 0; y < mapsize; y++)
		{
			passablemap.insert(std::make_pair(mapdata->getGridId(x, y), mapdata->getPassable(x, y, -1)));
			areamap2.insert(std::make_pair(mapdata->getGridId(x, y), false));
		}
	}
	//扩张不可通过区域
	std::map<int, bool>::iterator ite = passablemap.begin();
	for(; ite != passablemap.end(); ite++)
	{
		if(ite->second)
		{
			int px,py;
			mapdata->getCrood(ite->first, px, py);
			for(int x = px - 2; x <= px + 2; x++)
			{
				for(int y = py - 2; y <= py + 2; y++)
				{
					if(!mapdata->getPassable(x, y, -1))
					{
						ite->second = false;
						break;
					}
				}
				if(!ite->second)
					break;
			}
		}
	}
	//扩张剩余的可通过区域
	for(ite = passablemap.begin(); ite != passablemap.end(); ite++)
	{
		if(ite->second)
		{
			areamap1.insert(std::make_pair(ite->first, true));
		}
		else
		{
			int px,py;
			mapdata->getCrood(ite->first, px, py);
			bool added = false;
			for(int x = (px - 2 < 0)?0:px - 2; x <= ((px + 2 > mapsize - 1)?(mapsize - 1):(px + 2)); x++)
			{
				for(int y = (py - 2 < 0)?0:py - 2; y <= ((py + 2 > mapsize - 1)?(mapsize - 1):(py + 2)); y++)
				{
					std::map<int, bool>::iterator ite2 = passablemap.find(mapdata->getGridId(x, y));
					if(ite2->second)
					{
						areamap1.insert(std::make_pair(ite->first, true));
						added = true;
						break;
					}
				}
				if(added)
					break;
			}
			if(!added)
				areamap1.insert(std::make_pair(ite->first, false));
		}
	}
	//区域划分
	int areaid = 0;
	while(1)
	{
		ite = areamap2.begin();
		while(ite != areamap2.end() && ite->second == true)
		{
			ite++;
		}
		if(ite != areamap2.end())
		{
			int px,py;
			mapdata->getCrood(ite->first, px, py);
			if(!mapdata->getPassable(px, py, -1))
			{
				ite->second = true;	
			}
			else
			{
				MapArea* maparea = new MapArea;
				if(areamap1[ite->first] == true)
					maparea->mType = AreaType_Plane;
				else
					maparea->mType = AreaType_DeadCorner;
				MapCrood openlist[1024];
				openlist[0].x = px;
				openlist[0].y = py;
				unsigned int maxopen = 1;
				unsigned int curopen = 0;
				while(curopen < maxopen)
				{
					ite = areamap2.find(mapdata->getGridId(openlist[curopen].x,openlist[curopen].y));
					if(!mapdata->getPassable(openlist[curopen].x,openlist[curopen].y, -1))
					{
						curopen++;
						continue;
					}
					if((maparea->mType == AreaType_Plane && areamap1[ite->first] == true) ||
						(maparea->mType == AreaType_DeadCorner && areamap1[ite->first] == false))
					{
						ite->second = true;
						maparea->AddCrood(openlist[curopen].x,openlist[curopen].y);

						if(openlist[curopen].x > 0)
						{
							px = openlist[curopen].x - 1;
							py = openlist[curopen].y;
							unsigned int n = 0;
							for(; n < maxopen ; n++)
							{
								if(px == openlist[n].x && py == openlist[n].y)
									break;
							}
							if(n == maxopen)
							{
								openlist[maxopen].x = px;
								openlist[maxopen].y = py;								
								maxopen++;
							}
						}

						if(openlist[curopen].y > 0)
						{
							px = openlist[curopen].x;
							py = openlist[curopen].y - 1;
							unsigned int n = 0;
							for(; n < maxopen ; n++)
							{
								if(px == openlist[n].x && py == openlist[n].y)
									break;
							}
							if(n == maxopen)
							{
								openlist[maxopen].x = px;
								openlist[maxopen].y = py;								
								maxopen++;
							}
						}

						if(openlist[curopen].x < mapsize - 1)
						{
							px = openlist[curopen].x + 1;
							py = openlist[curopen].y;
							unsigned int n = 0;
							for(; n < maxopen ; n++)
							{
								if(px == openlist[n].x && py == openlist[n].y)
									break;
							}
							if(n == maxopen)
							{
								openlist[maxopen].x = px;
								openlist[maxopen].y = py;								
								maxopen++;
							}
						}

						if(openlist[curopen].y < mapsize - 1)
						{
							px = openlist[curopen].x;
							py = openlist[curopen].y + 1;
							unsigned int n = 0;
							for(; n < maxopen ; n++)
							{
								if(px == openlist[n].x && py == openlist[n].y)
									break;
							}
							if(n == maxopen)
							{
								openlist[maxopen].x = px;
								openlist[maxopen].y = py;								
								maxopen++;
							}
						}
					}	
					curopen++;
				}

				mAreaVec.insert(std::make_pair(areaid++, maparea));
			}
		}
		else
			break;
	}
	//区域链接
	std::map<int, MapArea*>::iterator areaite1 = mAreaVec.begin();
	for(;areaite1 != mAreaVec.end(); areaite1++)
	{
		std::map<int, MapArea*>::iterator areaite2 = mAreaVec.begin();
		for(;areaite2 != mAreaVec.end(); areaite2++)
		{
			if(areaite1 == areaite2)
				continue;
			bool connected = false;
			for(unsigned int n = 0; n < areaite1->second->mConnectedArea.size(); n++)
			{
				if(areaite1->second->mConnectedArea[n] == areaite2->first)
				{
					connected = true;
					break;
				}
			}
			if(connected)
				continue;

			std::vector<MapCrood>::iterator croodite1 = areaite1->second->mArea.begin();
			for(; croodite1 != areaite1->second->mArea.end(); croodite1++)
			{
				std::vector<MapCrood>::iterator croodite2 = areaite2->second->mArea.begin();
				for(; croodite2 != areaite2->second->mArea.end(); croodite2++)
				{
					if((abs((*croodite1).x - (*croodite2).x) == 1 && abs((*croodite1).y - (*croodite2).y) == 0) ||
						(abs((*croodite1).y - (*croodite2).y) == 1 && abs((*croodite1).x - (*croodite2).x) == 0) )
					{
						connected = true;
						areaite1->second->mConnectedArea.push_back(areaite2->first);
						areaite2->second->mConnectedArea.push_back(areaite1->first);
						break;
					}
				}
				if(connected)
					break;
			}
		}
		if(areaite1->second->mType == AreaType_DeadCorner&& areaite1->second->mConnectedArea.size() > 1)
			areaite1->second->mType = AreaType_Narrow;
	}

	//区域信息保存
	for(areaite1 = mAreaVec.begin(); areaite1 != mAreaVec.end(); areaite1++)
	{
		datalib->setData(str(boost::format("GameData/BattleData/AIData/MapAnalyze/Area%1%")%areaite1->first),(int)areaite1->second->mType);
		for(unsigned int n = 0; n < areaite1->second->mArea.size(); n++)
		{
			datalib->setData(
				str(boost::format("GameData/BattleData/AIData/MapAnalyze/Area%1%/Area/c%2%")%areaite1->first%n),
				mapdata->getGridId(areaite1->second->mArea[n].x,areaite1->second->mArea[n].y));
		}
		for(unsigned int n = 0; n < areaite1->second->mConnectedArea.size(); n++)
		{
			datalib->setData(
				str(boost::format("GameData/BattleData/AIData/MapAnalyze/Area%1%/ConnectedArea/a%2%")%areaite1->first%n),
				areaite1->second->mConnectedArea[n]);
		}
	}

	datalib->setData("GameData/BattleData/AIData/MapAnalyze", 1);
	return true;
}

int BattleAIState::SquadGroup::ReCalcStrength()
{
	mStrength = mSquadList.size();
	return mStrength;
}

BattleAIState::MapCrood BattleAIState::SquadGroup::ReCalcCenterCrood()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();

	int num = 0;
	mCenterCrood.x = 0;
	mCenterCrood.y = 0;
	for(unsigned int n = 0; n < mSquadList.size(); n++)
	{
		BattleSquad* squad1 = squadmgr->getBattleSquad(mSquadList[n]);
		if(squad1 && squad1->getUnitNum() > 0)
		{
			mCenterCrood.x += squad1->getGridX();
			mCenterCrood.y += squad1->getGridY();
			num++;
		}
	}
	mCenterCrood.x /= num;
	mCenterCrood.y /= num;

	return mCenterCrood;
}

void BattleAIState::AnalyzeOtherTeam()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();

	//读取队伍信息
	std::map<int, SquadGroup*> lastSquadGroupVec;
	std::vector<std::string> squadgrouplist = datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze")%mTeam));
	std::vector<std::string>::iterator datalibite = squadgrouplist.begin();
	for(; datalibite != squadgrouplist.end(); datalibite++)
	{
		int index;
		datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/%2%/Index")%mTeam%(*datalibite)), index);
		SquadGroup* squadgroup = new SquadGroup;
		datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/%2%/Strength")%mTeam%(*datalibite)), squadgroup->mStrength);
		datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/%2%/mCenterX")%mTeam%(*datalibite)), squadgroup->mCenterCrood.x);
		datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/%2%/mCenterY")%mTeam%(*datalibite)), squadgroup->mCenterCrood.y);
		
		squadgroup->mSquadList = datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/%2%/SquadList")%mTeam%(*datalibite)));

		lastSquadGroupVec.insert(std::make_pair(index, squadgroup));
		SquadGroup* squadgroup1 = new SquadGroup;
		squadgroup1->mSquadList = squadgroup->mSquadList;
		squadgroup1->mStrength = squadgroup->mStrength;
		squadgroup1->mCenterCrood.x = squadgroup->mCenterCrood.x;
		squadgroup1->mCenterCrood.y = squadgroup->mCenterCrood.y;
		mSquadGroupVec.insert(std::make_pair(index, squadgroup1));
	}
	
	int vaildid = 0;
	datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/VaildId")%mTeam), vaildid);

	//验证队伍信息
	//  验证现有队伍
	//    验证脱队和歼灭
	std::map<int, SquadGroup*>::iterator ite = mSquadGroupVec.begin();
	for(; ite != mSquadGroupVec.end();)
	{
		for(unsigned int n = 0; n < ite->second->mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(ite->second->mSquadList[n]);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				bool separate = true;
				for(unsigned int m = 0; m < ite->second->mSquadList.size(); m++)
				{
					if(m == n)
						continue;
					BattleSquad* squad2 = squadmgr->getBattleSquad(ite->second->mSquadList[m]);
					if(squad2 && squad2->getUnitNum() > 0)
					{
						int x1,y1,x2,y2;
						x1 = squad1->getGridX();
						y1 = squad1->getGridY();
						x2 = squad2->getGridX();
						y2 = squad2->getGridY();
						if(GetDistance(x1, y1, x2, y2) < 3)
						{
							separate = false;
							break;
						}
					}
				}
				if(separate)
				{
					ite->second->mSquadList.erase(ite->second->mSquadList.begin() + n);
					n--;

				}
			}
			else
			{
				ite->second->mSquadList.erase(ite->second->mSquadList.begin() + n);
				n--;
			}
		}
		if(ite->second->mSquadList.size() > 0)
		{
			ite++;
		}
		else
		{
			delete ite->second;
			ite = mSquadGroupVec.erase(ite);
		}
	}
	//  组成新的队伍或添加到队伍
	BattleSquadManager::BattleSquadIte squadite = squadmgr->mSquadList.begin();
	for(; squadite != squadmgr->mSquadList.end(); squadite++)
	{
		BattleSquad* squad1 = squadite->second;
		if(squad1 && squad1->getUnitNum() > 0 && squad1->getTeam() != mTeam)
		{
			bool insquadgroup = false;
			std::map<int, SquadGroup*>::iterator closetosquadgroup = mSquadGroupVec.end();
			ite = mSquadGroupVec.begin();
			for(; ite != mSquadGroupVec.end(); ite++)
			{
				for(unsigned int n = 0; n < ite->second->mSquadList.size(); n++)
				{
					BattleSquad* squad2 = squadmgr->getBattleSquad(ite->second->mSquadList[n]);
					if(squad2 && squad2->getUnitNum() > 0)
					{
						if(squad2 == squad1)
						{
							insquadgroup = true;
							break;
						}
						else if(squad1->getTeam() != squad2->getTeam())
						{
							break;
						}
						else
						{
							int x1,y1,x2,y2;
							x1 = squad1->getGridX();
							y1 = squad1->getGridY();
							x2 = squad2->getGridX();
							y2 = squad2->getGridY();
							if(GetDistance(x1, y1, x2, y2) < 3)
							{
								closetosquadgroup = ite;
							}
						}
					}
				}
				if(insquadgroup)
				{
					break;
				}
			}
			if(!insquadgroup)
			{
				if(closetosquadgroup != mSquadGroupVec.end())
				{
					closetosquadgroup->second->mSquadList.push_back(squad1->getSquadId());
				}
				else
				{
					SquadGroup* squadgroup = new SquadGroup;
					squadgroup->mStrength = 0;
					squadgroup->mSquadList.push_back(squad1->getSquadId());
					mSquadGroupVec.insert(std::make_pair(vaildid++, squadgroup));
				}
			}
		}
	}
	datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/VaildId")%mTeam), vaildid);
	//  合并相邻队伍
	std::vector<int> connectvec;
	ite = mSquadGroupVec.begin();
	for(; ite != mSquadGroupVec.end(); ite++)
	{
		for(unsigned int n = 0; n < ite->second->mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(ite->second->mSquadList[n]);
			std::map<int, SquadGroup*>::iterator ite1 = mSquadGroupVec.begin();
			for(; ite1 != mSquadGroupVec.end(); ite1++)
			{
				if(ite1 == ite)
					continue;
				for(unsigned int m = 0; m < ite1->second->mSquadList.size(); m++)
				{
					BattleSquad* squad2 = squadmgr->getBattleSquad(ite1->second->mSquadList[m]);
					if(squad1->getTeam() != squad2->getTeam())
					{
						break;
					}
					int x1,y1,x2,y2;
					x1 = squad1->getGridX();
					y1 = squad1->getGridY();
					x2 = squad2->getGridX();
					y2 = squad2->getGridY();
					if(GetDistance(x1, y1, x2, y2) < 3)
					{
						connectvec.push_back(ite->first);
						connectvec.push_back(ite1->first);
						break;
					}
				}
			}
		}
	}
	for(unsigned int n = 0; n < connectvec.size(); n += 2)
	{
		if(connectvec[n] < 0)
			continue;
		std::vector<int> connectvect;
		connectvect.push_back(connectvec[n]);
		connectvect.push_back(connectvec[n+1]);
		for(unsigned int m = n + 2; m < connectvec.size(); n += 2)
		{
			if(connectvec[m] < 0)
				continue;
			if((connectvec[n] == connectvec[m] && connectvec[n + 1] == connectvec[m + 1]) ||
				(connectvec[n + 1] == connectvec[m] && connectvec[n] == connectvec[m + 1]))
			{
				connectvec[m] = -1;
				connectvec[m + 1] = -1;
			}
			else if(connectvec[n] == connectvec[m] || connectvec[n + 1] == connectvec[m])
			{
				connectvect.push_back(connectvec[m]);
				connectvec[m] = -1;
				connectvec[m + 1] = -1;
			}
			else if(connectvec[n] == connectvec[m + 1] || connectvec[n + 1] == connectvec[m + 1])
			{
				connectvect.push_back(connectvec[m + 1]);
				connectvec[m] = -1;
				connectvec[m + 1] = -1;
			}
		}
		int maxstrength = 0;
		int maxstrengthgroup = 0;
		for(unsigned int m = 0; m < connectvect.size(); m++)
		{
			std::map<int, SquadGroup*>::iterator tempite = mSquadGroupVec.find(connectvect[m]);
			if(tempite->second->ReCalcStrength() > maxstrength)
			{
				maxstrength = tempite->second->ReCalcStrength();
				maxstrengthgroup = m;
			}
		}
		for(unsigned int m = 0; m < connectvect.size(); m++)
		{
			if(maxstrengthgroup != m)
			{
				std::map<int, SquadGroup*>::iterator tempite = mSquadGroupVec.find(connectvect[m]);
				std::map<int, SquadGroup*>::iterator tempite1 = mSquadGroupVec.find(connectvect[maxstrengthgroup]);
				for(unsigned int l = 0; l < tempite->second->mSquadList.size(); l++)
				{
					tempite1->second->mSquadList.push_back(tempite->second->mSquadList[l]);
				}
				delete tempite->second;
				mSquadGroupVec.erase(tempite);
			}
		}
	}

	//验证新部队信息
	

	//分析队伍行动信息


	//删除旧队伍信息
	ite = lastSquadGroupVec.begin();
	for(; ite != lastSquadGroupVec.end(); ite++)
	{
		delete ite->second;
	}
	lastSquadGroupVec.clear();
}

void BattleAIState::SaveOtherTeamInfo()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();

	datalib->delNode(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze")%mTeam));
	std::map<int, SquadGroup*>::iterator ite = mSquadGroupVec.begin();
	for(; ite != mSquadGroupVec.end(); ite++)
	{
		int squadnum = 0;
		for(unsigned int n = 0; n < ite->second->mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(ite->second->mSquadList[n]);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				squadnum++;
			}
		}
		if(squadnum > 0)
		{
			datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/sg%2%/Index")%mTeam%ite->first), ite->first);
			datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/sg%2%/Strength")%mTeam%ite->first), ite->second->ReCalcStrength());
			ite->second->ReCalcCenterCrood();
			datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/sg%2%/mCenterX")%mTeam%ite->first), ite->second->mCenterCrood.x);
			datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/sg%2%/mCenterY")%mTeam%ite->first), ite->second->mCenterCrood.y);
			for(unsigned int n = 0; n < ite->second->mSquadList.size(); n++)
			{
				BattleSquad* squad1 = squadmgr->getBattleSquad(ite->second->mSquadList[n]);
				if(squad1 && squad1->getUnitNum() > 0)
				{
					datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherTeamAnalyze/sg%2%/SquadList/%3%")%mTeam%ite->first%squad1->getSquadId()), 1);
				}
			}
		}
	}
}