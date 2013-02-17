#include "BattleAIState.h"

#include "BattleState.h"

#include <boost/format.hpp>

#include "DataLibrary.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CommonFunction.h"
#include "DecisionMap.h"
#include "SquadRoleFactor.h"
#include "SquadMoveFactor.h"
#include "SquadSkillFactor.h"

#include "GUIInfoWindow.h"
#include "GUIBattle.h"

BattleAIState::BattleAIState(int team)
:mTeam(team),mState(AISTATE_INIT)
{
	GUIBattle* mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUIInfoWindow* infoWindow=(GUIInfoWindow*)mGUIBattle->getSubWindow("InfoWindow");
	infoWindow->setCaption("EnemyTurn.png",MyGUI::Colour::White);
	infoWindow->showScene("");
}
BattleAIState::~BattleAIState()
{
	std::map<std::string, MissionCommander*>::iterator mcmdite = mMissionCmdMap.begin();
	for( ;mcmdite != mMissionCmdMap.end(); mcmdite++)
	{
		delete mcmdite->second;
	}
	mMissionCmdMap.clear();
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
		createMissionCommanders();
		findOtherSquadGroup();

		mState = AISTATE_EXECUTE;
		break;
	case AISTATE_EXECUTE:
		{
			std::map<std::string, MissionCommander*>::iterator mcmdite = mMissionCmdMap.begin();
			for( ; mcmdite != mMissionCmdMap.end(); mcmdite++)
			{
				if(mcmdite->second->update(mOtherSquadGroupVec))
					return;
			}
			mState = AISTATE_SHUTDOWN;
		}
		break;
	case AISTATE_SHUTDOWN:
		saveOtherSquadGroup();
		writeMissionCommanders();

		mMainState->PopState();
		break;
	}
}

BattleAIState::MapArea::MapArea(std::string path)
:mArea(path + "/Area")
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->getData(path, mType, true);
	std::vector<std::string> connectedVec = 
			datalib->getChildList(str(boost::format("%1%/ConnectedArea")%path));
	std::vector<std::string>::iterator ite;
	for(ite = connectedVec.begin(); ite != connectedVec.end(); ite++)
	{
		int connectedareaid;
		datalib->getData(str(boost::format("%1%/ConnectedArea/%2%")%path%(*ite)),connectedareaid);
		mConnectedArea.push_back(connectedareaid);
	}
}

BattleAIState::MapArea::MapArea(int areatype, std::vector<Crood> croodVec)
:mType(areatype), mArea(croodVec)
{

}

void BattleAIState::MapArea::writeMapArea(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->setData(path, mType);
	mArea.writeArea(path + "/Area");
	for(unsigned int n = 0; n < mConnectedArea.size(); n++)
	{
		datalib->setData((str(boost::format("%1%/ConnectedArea/a%2%")%path%n)), mConnectedArea[n]);
	}
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
	for(;areaite != arealist.end(); areaite++)
	{
		int areaid = atoi((*areaite).substr(4, (*areaite).size() - 4).c_str());
		MapArea maparea(str(boost::format("GameData/BattleData/AIData/MapAnalyze/%1%")%(*areaite)));
		mAreaVec.insert(std::make_pair(areaid, maparea));
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
			for(int x = px - 1; x <= px + 1; x++)
			{
				for(int y = py - 1; y <= py + 1; y++)
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
			for(int x = (px - 1 < 0)?0:px - 1; x <= ((px + 1 > mapsize - 1)?(mapsize - 1):(px + 1)); x++)
			{
				for(int y = (py - 1 < 0)?0:py - 1; y <= ((py + 1 > mapsize - 1)?(mapsize - 1):(py + 1)); y++)
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
	ite = areamap2.end();
	while(1)
	{
		if(ite == areamap2.end() || ite->second == true)
		{
			ite = areamap2.begin();
			while(ite != areamap2.end() && ite->second == true)
			{
				ite++;
			}
		}
		if(ite != areamap2.end())
		{
			int px,py;
			mapdata->getCrood(ite->first, px, py);
			if(!mapdata->getPassable(px, py, -1))
			{
				ite->second = true;	
				ite++;
			}
			else
			{
				ite->second = true;	

				int areatype = AREATYPE_PLANE;
				if(areamap1[ite->first] == false)
					areatype = AREATYPE_DEADCRORNER;
				std::vector<Crood> croodVec;
				croodVec.push_back(Crood(px, py));

				for(unsigned int i = 0; i < croodVec.size(); i++)
				{
					Crood checkcrood[4];
					checkcrood[0].mX = croodVec[i].mX - 1;
					checkcrood[0].mY = croodVec[i].mY;
					checkcrood[1].mX = croodVec[i].mX;
					checkcrood[1].mY = croodVec[i].mY - 1;
					checkcrood[2].mX = croodVec[i].mX + 1;
					checkcrood[2].mY = croodVec[i].mY;
					checkcrood[3].mX = croodVec[i].mX;
					checkcrood[3].mY = croodVec[i].mY + 1;
					for(unsigned int n = 0; n < 4; n++)
					{
						std::map<int, bool>::iterator tempite = areamap2.find(mapdata->getGridId(checkcrood[n].mX,checkcrood[n].mY));
						if(tempite == areamap2.end() || tempite->second == true)
						{
							continue;
						}
						if(!mapdata->getPassable(checkcrood[n].mX,checkcrood[n].mY, -1))
						{
							tempite->second = true;
							continue;
						}
						if((areatype == AREATYPE_PLANE && areamap1[tempite->first] == true) ||
							(areatype == AREATYPE_DEADCRORNER && areamap1[tempite->first] == false))
						{
							tempite->second = true;
							croodVec.push_back(checkcrood[n]);
						}
						else
						{
							if(ite == areamap2.end() || ite->second == true)
								ite = tempite;
						}
					}
				}
				MapArea maparea(areatype, croodVec);
				mAreaVec.insert(std::make_pair(areaid++, maparea));
			}
		}
		else
		{
			break;
		}
	}
	//区域链接
	std::map<int, MapArea>::iterator areaite1 = mAreaVec.begin();
	for(;areaite1 != mAreaVec.end(); areaite1++)
	{
		std::map<int, MapArea>::iterator areaite2 = mAreaVec.begin();
		for(;areaite2 != mAreaVec.end(); areaite2++)
		{
			if(areaite1 == areaite2)
				continue;
			bool connected = false;
			for(unsigned int n = 0; n < areaite1->second.mConnectedArea.size(); n++)
			{
				if(areaite1->second.mConnectedArea[n] == areaite2->first)
				{
					connected = true;
					break;
				}
			}
			if(connected)
				continue;

			if(areaite1->second.mArea.crossed(areaite2->second.mArea))
			{
				areaite1->second.mConnectedArea.push_back(areaite2->first);
				areaite2->second.mConnectedArea.push_back(areaite1->first);
			}
		}
		if(areaite1->second.mType == AREATYPE_DEADCRORNER && areaite1->second.mConnectedArea.size() > 1)
			areaite1->second.mType = AREATYPE_NARROW;
	}

	//区域信息保存
	for(areaite1 = mAreaVec.begin(); areaite1 != mAreaVec.end(); areaite1++)
	{
		areaite1->second.writeMapArea(str(boost::format("GameData/BattleData/AIData/MapAnalyze/Area%1%")%areaite1->first));
	}

	datalib->setData("GameData/BattleData/AIData/MapAnalyze", 1);
	return true;
}

BattleAIState::OtherSquadGroupInfo::OtherSquadGroupInfo(std::string path)
:mCenterCrood(path + "/CenterCrood"), mLastCenterCrood(path + "/CenterCrood")
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int isEnemy = 1;
	datalib->getData(path + "/IsEnemy", isEnemy);
	mIsEnemy = (isEnemy == 1);
	mSquadList = datalib->getChildList(path + "/SquadList");

	datalib->getData(str(boost::format("%1%/CurMission/Type")%path),mCurMission.missionType);
	datalib->getData(str(boost::format("%1%/CurMission/Area")%path),mCurMission.missionArea);
	datalib->getData(str(boost::format("%1%/CurMission/Possibility")%path),mCurMission.possibility);
}

BattleAIState::OtherSquadGroupInfo::OtherSquadGroupInfo(bool isenemy)
:mIsEnemy(isenemy)
{
	mLastCenterCrood.mX = -2;
	mLastCenterCrood.mY = -2;
	mCurMission.missionType = OSGM_IDLE;
	mCurMission.possibility = 20.0f;
}

void BattleAIState::OtherSquadGroupInfo::writeOtherSquadGroupInfo(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	datalib->setData(path + "/IsEnemy", mIsEnemy?1:0);
	mCenterCrood.writeCrood(path + "/CenterCrood");
	for(unsigned int n = 0; n < mSquadList.size(); n++)
	{
		BattleSquad* squad1 = squadmgr->getBattleSquad(mSquadList[n]);
		if(squad1 && squad1->getUnitNum() > 0)
		{
			datalib->setData(str(boost::format("%1%/SquadList/%2%")%path%squad1->getSquadId()), 1);
		}
	}
	datalib->setData(str(boost::format("%1%/CurMission/Type")%path),mCurMission.missionType);
	datalib->setData(str(boost::format("%1%/CurMission/Area")%path),mCurMission.missionArea);
	datalib->setData(str(boost::format("%1%/CurMission/Possibility")%path),mCurMission.possibility);
}

float BattleAIState::OtherSquadGroupInfo::getSquadGroupStrength()
{
	float strength = 0.0f;
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	for(unsigned int n = 0; n < mSquadList.size(); n++)
	{
		BattleSquad* squad1 = squadmgr->getBattleSquad(mSquadList[n]);
		if(squad1 && squad1->getUnitNum() > 0)
		{
			strength += squad1->getSquadStrength();
		}
	}
	return strength;
}

void BattleAIState::findOtherSquadGroup()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string relation;
	datalib->getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%mTeam),relation);
	int faction = 0;
	if(relation == "enemy1")
		faction = 1;
	else if(relation == "enemy2")
		faction = 2;
	else if(relation == "enemy3")
		faction = 3;
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();

	//读取之前的队伍信息
	std::vector<std::string> squadgrouplist = datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherSquadGroup")%mTeam));
	std::vector<std::string>::iterator datalibite = squadgrouplist.begin();
	for(; datalibite != squadgrouplist.end(); datalibite++)
	{
		int index = atoi((*datalibite).substr(2, (*datalibite).size() - 2).c_str());
		OtherSquadGroupInfo squadgroup(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherSquadGroup/%2%")%mTeam%(*datalibite)));
		mOtherSquadGroupVec.insert(std::make_pair(index, squadgroup));
	}

	//验证之前的队伍信息（多队脱队未实现）
	int vaildid = 0;
	datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherSquadGroup")%mTeam), vaildid);
	std::map<int, OtherSquadGroupInfo>::iterator osgite = mOtherSquadGroupVec.begin();
	for(; osgite != mOtherSquadGroupVec.end(); )
	{
		for(unsigned int n = 0; n < osgite->second.mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(osgite->second.mSquadList[n]);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				if(osgite->second.mSquadList.size() > 1)
				{
					bool separate = true;
					for(unsigned int m = 0; m < osgite->second.mSquadList.size(); m++)
					{
						if(m == n)
							continue;
						BattleSquad* squad2 = squadmgr->getBattleSquad(osgite->second.mSquadList[m]);
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
						osgite->second.mSquadList.erase(osgite->second.mSquadList.begin() + n);
						n--;
					}
				}
			}
			else
			{
				osgite->second.mSquadList.erase(osgite->second.mSquadList.begin() + n);
				n--;
			}
		}
		if(osgite->second.mSquadList.size() > 0)
		{
			osgite++;
		}
		else
		{
			osgite = mOtherSquadGroupVec.erase(osgite);
		}
	}
	//组成新的队伍或添加到队伍
	BattleSquadManager::BattleSquadIte squadite = squadmgr->mSquadList.begin();
	for(; squadite != squadmgr->mSquadList.end(); squadite++)
	{
		BattleSquad* squad1 = squadite->second;
		if(squad1 && squad1->getUnitNum() > 0 && squad1->getTeam() != mTeam)
		{
			bool insquadgroup = false;
			std::map<int, OtherSquadGroupInfo>::iterator closetosquadgroup = mOtherSquadGroupVec.end();
			osgite = mOtherSquadGroupVec.begin();
			for(; osgite != mOtherSquadGroupVec.end(); osgite++)
			{
				for(unsigned int n = 0; n < osgite->second.mSquadList.size(); n++)
				{
					BattleSquad* squad2 = squadmgr->getBattleSquad(osgite->second.mSquadList[n]);
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
								closetosquadgroup = osgite;
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
				if(closetosquadgroup != mOtherSquadGroupVec.end())
				{
					closetosquadgroup->second.mSquadList.push_back(squad1->getSquadId());
				}
				else
				{
					OtherSquadGroupInfo squadgroup(squad1->getFaction() != faction);
					squadgroup.mSquadList.push_back(squad1->getSquadId());
					mOtherSquadGroupVec.insert(std::make_pair(vaildid++, squadgroup));
				}
			}
		}
	}
	datalib->setData(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherSquadGroup")%mTeam), vaildid);
	//合并相邻队伍
	std::vector<int> connectvec;
	osgite = mOtherSquadGroupVec.begin();
	for(; osgite != mOtherSquadGroupVec.end(); osgite++)
	{
		for(unsigned int n = 0; n < osgite->second.mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(osgite->second.mSquadList[n]);
			std::map<int, OtherSquadGroupInfo>::iterator testosqite = mOtherSquadGroupVec.begin();
			for(; testosqite != mOtherSquadGroupVec.end(); testosqite++)
			{
				if(testosqite == osgite)
					continue;
				for(unsigned int m = 0; m < testosqite->second.mSquadList.size(); m++)
				{
					BattleSquad* squad2 = squadmgr->getBattleSquad(testosqite->second.mSquadList[m]);
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
						connectvec.push_back(osgite->first);
						connectvec.push_back(testosqite->first);
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
		for(unsigned int m = n + 2; m < connectvec.size(); m += 2)
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
		unsigned int maxstrength = 0;
		int maxstrengthgroup = 0;
		for(unsigned int m = 0; m < connectvect.size(); m++)
		{
			std::map<int, OtherSquadGroupInfo>::iterator tempite = 
				mOtherSquadGroupVec.find(connectvect[m]);
			if(tempite->second.mSquadList.size() > maxstrength)
			{
				maxstrength = tempite->second.mSquadList.size();
				maxstrengthgroup = m;
			}
		}
		for(unsigned int m = 0; m < connectvect.size(); m++)
		{
			if(maxstrengthgroup != m)
			{
				std::map<int, OtherSquadGroupInfo>::iterator tempite = 
					mOtherSquadGroupVec.find(connectvect[m]);
				std::map<int, OtherSquadGroupInfo>::iterator tempite1 = 
					mOtherSquadGroupVec.find(connectvect[maxstrengthgroup]);
				for(unsigned int l = 0; l < tempite->second.mSquadList.size(); l++)
				{
					tempite1->second.mSquadList.push_back(tempite->second.mSquadList[l]);
				}
				mOtherSquadGroupVec.erase(tempite);
			}
		}
	}
	//计算队伍行动信息
	osgite = mOtherSquadGroupVec.begin();
	for(; osgite != mOtherSquadGroupVec.end(); osgite++)
	{
		//计算中心
		int num = 0;
		osgite->second.mCenterCrood.mX = 0;
		osgite->second.mCenterCrood.mY = 0;
		for(unsigned int n = 0; n < osgite->second.mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(osgite->second.mSquadList[n]);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				osgite->second.mCenterCrood.mX += squad1->getGridX();
				osgite->second.mCenterCrood.mY += squad1->getGridY();
				num++;
			}
		}
		osgite->second.mCenterCrood.mX  /= num;
		osgite->second.mCenterCrood.mY  /= num;

		if(osgite->second.mLastCenterCrood.mX == -2)
		{
			osgite->second.mLastCenterCrood.mX = osgite->second.mCenterCrood.mX;
			osgite->second.mLastCenterCrood.mY = osgite->second.mCenterCrood.mY;
		}

		//计算占据区域
		std::vector<Crood> squadCroodVec;
		for(unsigned int n = 0; n < osgite->second.mSquadList.size(); n++)
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(osgite->second.mSquadList[n]);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				squadCroodVec.push_back(Crood(squad1->getGridX(), squad1->getGridY()));
			}
		}
		osgite->second.mArea.calcConvexHull(squadCroodVec);

		//估计任务
		std::vector<OtherSquadGroupMission> missionlist;
		std::map<std::string, MissionCommander*>::iterator mcmdite = mMissionCmdMap.begin();
		for( ; mcmdite != mMissionCmdMap.end(); mcmdite++)
		{
			mcmdite->second->analyzeMission(osgite->second, missionlist);
		}
		std::vector<OtherSquadGroupMission>::iterator osgmite1 = missionlist.begin();
		if(osgmite1 == missionlist.end())
		{
			osgite->second.mCurMission.missionType = OSGM_IDLE;
			osgite->second.mCurMission.possibility = 20.0f;
		}
		else
		{
			if(osgite->second.mCurMission.missionType != OSGM_IDLE)
			{
				for(; osgmite1 != missionlist.end(); osgmite1++)
				{
					if((*osgmite1).missionType == osgite->second.mCurMission.missionType &&
						(*osgmite1).missionArea == osgite->second.mCurMission.missionArea)
					{
						(*osgmite1).possibility += 10.0f;
						break;
					}
				}
			}
			osgmite1 = missionlist.begin();
			osgite->second.mCurMission = (*osgmite1);
			for(; osgmite1 != missionlist.end(); osgmite1++)
			{
				if((*osgmite1).possibility > osgite->second.mCurMission.possibility)
				{
					osgite->second.mCurMission = (*osgmite1);
				}
			}
		}
	}
}

void BattleAIState::saveOtherSquadGroup()
{
	std::map<int, OtherSquadGroupInfo>::iterator osgite = mOtherSquadGroupVec.begin();
	for(; osgite != mOtherSquadGroupVec.end(); osgite++ )
	{
		osgite->second.writeOtherSquadGroupInfo(str(boost::format("GameData/BattleData/AIData/Team%1%/OtherSquadGroup/sg%2%")%mTeam%osgite->first));
	}
}
//DecisionMapFactors---------------------------------------------
//OSGStrengthFactor
BattleAIState::OSGStrengthFactor::OSGStrengthFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup)
:mOtherSquadGroup(othersquadgroup),mMaxStrength(1.0f)
{
	std::map<int, OtherSquadGroupInfo>::iterator ite = mOtherSquadGroup->begin();
	for( ; ite != mOtherSquadGroup->end(); ite++)
	{
		if(ite->second.getSquadGroupStrength() > mMaxStrength)
		{
			mMaxStrength = ite->second.getSquadGroupStrength();
		}
	}
}

float BattleAIState::OSGStrengthFactor::calcDecision(int &decision)
{
	std::map<int, OtherSquadGroupInfo>::iterator osgite = mOtherSquadGroup->find(decision);
	if(osgite != mOtherSquadGroup->end())
	{
		float strength = osgite->second.getSquadGroupStrength();
		if(strength > 0.0f)
		{
			return strength / mMaxStrength * 100.0f;
		}
	}
	return 0.0f;
}
//OSGCloseToAreaFactor
BattleAIState::OSGCloseToAreaFactor::OSGCloseToAreaFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup, Area* area)
:mOtherSquadGroup(othersquadgroup),mArea(area)
{

}

float BattleAIState::OSGCloseToAreaFactor::calcDecision(int &decision)
{
	std::map<int, OtherSquadGroupInfo>::iterator osgite = mOtherSquadGroup->find(decision);
	if(osgite != mOtherSquadGroup->end())
	{
		float strength = 100.0f;
		Crood crood1 = mArea->getCenter();
		int rad1 = mArea->getRadius();
		Crood crood2 = osgite->second.mArea.getCenter();
		int rad2 = osgite->second.mArea.getRadius();
		float rad = sqrt(pow(float(crood1.mX - crood2.mX), 2) + pow(float(crood1.mY - crood2.mY), 2));
		if(rad -  rad1 - rad2 > 0.0f)
		{
			strength -= 10.0f * (rad -  rad1 - rad2);
		}
		return strength;
	}
	return 0.0f;
}

//OSGCloseToAreaFactor
BattleAIState::OSGMoveToAreaFactor::OSGMoveToAreaFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup, Area* area)
:mOtherSquadGroup(othersquadgroup),mArea(area)
{

}

float BattleAIState::OSGMoveToAreaFactor::calcDecision(int &decision)
{
	std::map<int, OtherSquadGroupInfo>::iterator osgite = mOtherSquadGroup->find(decision);
	if(osgite != mOtherSquadGroup->end())
	{
		Ogre::Vector2 vec1(osgite->second.mCenterCrood.mX - osgite->second.mLastCenterCrood.mX,
			osgite->second.mCenterCrood.mY - osgite->second.mLastCenterCrood.mY);
		Ogre::Vector2 vec2(mArea->getCenter().mX - osgite->second.mCenterCrood.mX,
			mArea->getCenter().mY - osgite->second.mCenterCrood.mY);
		float strength = vec1.dotProduct(vec2) * 100.0f;
		return strength;
	}
	return 0.0f;
}


//SquadAI--------------------------------------------------------
BattleAIState::SquadAI::SquadAI(BattleSquad* squad)
:mSquad(squad),mState(SAS_MOVE),mTargetType(SGM_WAIT)
{

}

bool BattleAIState::SquadAI::update()
{
	switch(mState)
	{
	case SAS_MOVE:
		updateMove();
		return true;
	case SAS_FORMATION:
		updateFormation();
		return true;
	case SAS_SKILL:
		updateSkill();
		return true;
	case SAS_DIRECTION:
		updateDirection();
		return true;
	}
	if(mLastActiveAP <= mSquad->getActionPoint())
		return false;
	mState = SAS_MOVE;
	return true;
}
void BattleAIState::SquadAI::setTarget(int targettype, Crood tragetcrood)
{
	mState = SAS_MOVE;
	mTargetType = targettype;
	mTargetCrood = tragetcrood; 
}
void BattleAIState::SquadAI::updateMove()
{
	if(mSquad->getActionPoint() < 2.0f)
	{
		mState = SAS_FORMATION;
		return;
	}
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	std::map<int, BattleSquadManager::MoveNode> moveareaold = squadmgr->getMoveArea(mSquad);
	std::vector<Crood> croodlist;
	std::map<int, BattleSquadManager::MoveNode>::iterator movenodeite = moveareaold.begin();
	for( ; movenodeite != moveareaold.end(); movenodeite++)
	{
		croodlist.push_back(Crood(movenodeite->second.x, movenodeite->second.y));
	}
	std::map<int, BattleSquadManager::MoveNode> fullpath = squadmgr->getFullPath(mSquad, mTargetCrood);
	if(fullpath.size() == 0)
	{
		mState = SAS_FORMATION;
		return;
	}
	DecisionMap<Crood> targetdecision(croodlist);
	/*
	switch(mTargetType)
	{
	case SGM_WAIT:
		break;
	case SGM_MOVE:
		break;
	case SGM_RALLY:
		break;
	case SGM_DEFEND:
		break;
	case SGM_ATTACK:
		break;
	case SGM_SUPPORT_RANGE:
		break;
	case SGM_SUPPORT_CLOSE:
		break;
	}
	*/
	targetdecision.addFactor(new SquadMoveClosetoPathFactor(&moveareaold, &fullpath), 1.0f);
	targetdecision.calcDecision();
	Crood target = targetdecision.getHighest();

	if(target.mX == mSquad->getGridX() && target.mY == mSquad->getGridY())
	{
		mState = SAS_FORMATION;
		return;
	}
	std::vector<int> pathlist;
	std::vector<BattleSquadManager::MoveNode> path = squadmgr->getMovePath(mSquad, target.mX, target.mY);
	std::vector<BattleSquadManager::MoveNode>::reverse_iterator rite;
	for(rite = path.rbegin(); rite != path.rend(); rite++)
	{
		pathlist.push_back((*rite).x);
		pathlist.push_back((*rite).y);
	}
	unsigned int evt = 0;
	unsigned intstopindex = 0;
	squadmgr->moveSquad(mSquad, pathlist, intstopindex, evt);
	return;
}
void BattleAIState::SquadAI::updateFormation()
{
	mState = SAS_SKILL;
}
void BattleAIState::SquadAI::updateSkill()
{
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	std::vector<BattleSquad::ActiveSkillInfo> skilllist = mSquad->GetActiveSkillList();
	std::vector<BattleSquad::ActiveSkillInfo>::iterator ite = skilllist.begin();
	std::vector<UseSkillInfo> useskillvec;
	UseSkillInfo useskill;
	for( ; ite != skilllist.end(); ite++)
	{
		if((*ite).available == false)
			continue;
		if((*ite).skillid == "move" || 
			(*ite).skillid == "turn" || 
			(*ite).skillid == "looseformation" ||
			(*ite).skillid == "lineformation" ||
			(*ite).skillid == "circularformation")
		{
			continue;
		}
		std::vector<BattleSquadManager::SkillNode> skillnodes = squadmgr->getSkillArea(mSquad, (*ite).skillid);
		std::vector<BattleSquadManager::SkillNode>::iterator skillcroodite = skillnodes.begin();
		for(; skillcroodite != skillnodes.end(); skillcroodite++)
		{
			if((*skillcroodite).validTarget)
			{
				useskill.skillid = (*ite).skillid;
				useskill.targetCrood.mX = (*skillcroodite).x;
				useskill.targetCrood.mY = (*skillcroodite).y;
				useskillvec.push_back(useskill);
			}
		}
	}
	if(useskillvec.size() > 0)
	{
		useskill.skillid = "none";
		useskillvec.push_back(useskill);
		DecisionMap<UseSkillInfo> skilldecision(useskillvec);
		/*
		switch(mTargetType)
		{
		case SGM_WAIT:
			break;
		case SGM_MOVE:
			break;
		case SGM_RALLY:
			break;
		case SGM_DEFEND:
			break;
		case SGM_ATTACK:
			break;
		case SGM_SUPPORT_RANGE:
			break;
		case SGM_SUPPORT_CLOSE:
			break;
		}
		*/
		skilldecision.addFactor(new SquadSkillbyAtkEffectiveFactor(mSquad) , 1.0f);
		skilldecision.calcDecision();
		useskill = skilldecision.getHighest();
		if(useskill.skillid != "none")
		{
			unsigned int evt = 0;
			squadmgr->useSkill(mSquad, useskill.skillid, useskill.targetCrood.mX, useskill.targetCrood.mY, evt);
			return;
		}
	}
	mState = SAS_DIRECTION;
}
void BattleAIState::SquadAI::updateDirection()
{
	mLastActiveAP = mSquad->getActionPoint();
	mState = SAS_WAIT;
}

//SquadGroupCommander--------------------------------------------
BattleAIState::SquadGroupCommander::SquadGroupCommander(std::string path, std::vector<std::string> squadlist)
:mTargetCrood(path + "/TargetCrood")
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	datalib->getData(path + "/Type", mType);
	datalib->getData(path + "/TargetType", mTargetType);
	std::vector<std::string> slist = datalib->getChildList(path+ "/SquadList");
	std::vector<std::string>::iterator site = slist.begin();
	std::vector<std::string>::iterator site1 = squadlist.end();
	for( ; site != slist.end(); site++)
	{
		site1 = std::find(squadlist.begin(), squadlist.end(), (*site));
		if(site1 != squadlist.end())
		{
			BattleSquad* squad1 = squadmgr->getBattleSquad(*site);
			if(squad1 && squad1->getUnitNum() > 0)
			{
				mSquadList.push_back(SquadAI(squad1));
			}
		}
	}
	setTarget(mTargetType, mTargetCrood);
}

BattleAIState::SquadGroupCommander::SquadGroupCommander(int type, std::vector<BattleSquad*> squadlist)
:mType(type),mTargetType(SGM_WAIT)
{
	std::vector<BattleSquad*>::iterator site = squadlist.begin();
	for( ; site != squadlist.end(); site++)
	{
		mSquadList.push_back(SquadAI(*site));
	}
}

bool BattleAIState::SquadGroupCommander::update()
{
	std::vector<SquadAI>::iterator saite = mSquadList.begin();
	for(; saite != mSquadList.end(); )
	{
		if((*saite).mSquad->getUnitNum() > 0)
		{
			if((*saite).update())
				return true;
			saite++;
		}
		else
		{
			saite = mSquadList.erase(saite);
		}
	}
	return false;
}

void BattleAIState::SquadGroupCommander::setTarget(int targettype, Crood tragetcrood)
{
	mTargetType = targettype;
	mTargetCrood = tragetcrood;
	std::vector<SquadAI>::iterator saite = mSquadList.begin();
	for(; saite != mSquadList.end(); saite++)
	{
		(*saite).setTarget(targettype, tragetcrood);
	}
}
void BattleAIState::SquadGroupCommander::getTarget(int &targettype, Crood &tragetcrood)
{
	targettype = mTargetType;
	tragetcrood = mTargetCrood;
}
		
void BattleAIState::SquadGroupCommander::writeSquadGroupCommander(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->setData(path + "/Type", mType);
	datalib->setData(path + "/TargetType", mTargetType);
	mTargetCrood.writeCrood(path + "/TargetCrood");
	std::vector<SquadAI>::iterator saite = mSquadList.begin();
	for(; saite != mSquadList.end(); saite++)
	{
		datalib->setData(str(boost::format("%1%/SquadList/%2%")%path%(*saite).mSquad->getSquadId()), 1);
	}
}

float BattleAIState::SquadGroupCommander::getSquadGroupStrength()
{
	float strength = 0.0f;
	std::vector<SquadAI>::iterator saite = mSquadList.begin();
	for(; saite != mSquadList.end(); saite++)
	{
		strength += (*saite).mSquad->getSquadStrength();
	}
	return strength;
}

bool BattleAIState::SquadGroupCommander::isRallied()
{

	return false;
}

//MissionCommander-----------------------------------------------
BattleAIState::MissionCommander::MissionCommander(std::string path, std::vector<std::string> squadlist)
:mSquadList(squadlist),mState(MCS_PLAN),mVaildId(0)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->getData(path + "/AreaId", mMissionAreaId);
	mMissionArea.readArea(str(boost::format("GameData/BattleData/MapData/Area/%1%/CoordList")%mMissionAreaId));
	datalib->getData(path+ "/CommanderInfo/SquadGroupList", mVaildId);
	std::vector<std::string> sglist = datalib->getChildList(path+ "/CommanderInfo/SquadGroupList");
	std::vector<std::string>::iterator sgite = sglist.begin();
	for( ; sgite != sglist.end(); sgite++)
	{
		int index = atoi((*sgite).substr(2, (*sgite).size() - 2).c_str());
		SquadGroupCommander sgc(str(boost::format("%1%/CommanderInfo/SquadGroupList/%2%")%path%(*sgite)), mSquadList);
		if(sgc.mSquadList.size() > 0)
		{
			mSquadGroupList.insert(std::make_pair(index, sgc));
		}
	}
}

bool BattleAIState::MissionCommander::update(std::map<int, OtherSquadGroupInfo>& othersquadgroup)
{
	if(mState == MCS_PLAN)
	{
		plan(othersquadgroup);
		return true;
	}
	std::map<int, SquadGroupCommander>::iterator sgcite = mSquadGroupList.begin();
	for( ; sgcite != mSquadGroupList.end(); sgcite++)
	{
		if(sgcite->second.update())
		{
			return true;
		}
	}
	return false;
}

void BattleAIState::MissionCommander::writeMissionCommander(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->delNode(path + "/CommanderInfo");
	datalib->setData(path + "/CommanderInfo/SquadGroupList", mVaildId);
	std::map<int, SquadGroupCommander>::iterator sgcite = mSquadGroupList.begin();
	for( ; sgcite != mSquadGroupList.end(); sgcite++)
	{
		if(sgcite->second.mSquadList.size() > 0)
		{
			sgcite->second.writeSquadGroupCommander(str(boost::format("%1%/CommanderInfo/SquadGroupList/sg%2%")%path%sgcite->first));
		}
	}
	write(path);
}

std::vector<BattleSquad*> BattleAIState::MissionCommander::getFreeSquads()
{
	std::vector<BattleSquad*> freesquads;
	BattleSquadManager* squadmgr = BattleSquadManager::getSingletonPtr();
	std::vector<std::string>::iterator site = mSquadList.begin();
	for( ; site != mSquadList.end(); )
	{
		BattleSquad* squad1 = squadmgr->getBattleSquad(*site);
		if(squad1 && squad1->getUnitNum() > 0)
		{
			bool bInSquadGroup = false;
			std::map<int, SquadGroupCommander>::iterator sgcite = mSquadGroupList.begin();
			for( ; sgcite != mSquadGroupList.end(); sgcite++)
			{
				std::vector<SquadAI>::iterator saite = sgcite->second.mSquadList.begin();
				for( ; saite != sgcite->second.mSquadList.end(); saite++)
				{
					if((*saite).mSquad == squad1)
					{
						bInSquadGroup = true;
						break;
					}
				}
				if(bInSquadGroup)
					break;
			}
			if(!bInSquadGroup)
			{
				freesquads.push_back(squad1);
			}
			site++;
		}
		else
		{
			site =  mSquadList.erase(site);
		}
	}
	return freesquads;
}

int BattleAIState::MissionCommander::createSquadGroup(int type, std::vector<BattleSquad*> squadlist)
{
	int index = mVaildId++;
	SquadGroupCommander sgc(type, squadlist);
	mSquadGroupList.insert(std::make_pair(index, sgc));
	return index;
}

void BattleAIState::MissionCommander::chooseSquads(std::vector<BattleSquad*>& choosefrom,
													std::vector<BattleSquad*>& choosed, 
													std::vector<BattleSquad*>::iterator& choosedends)
{
	std::vector<BattleSquad*>::iterator ite1 = choosed.begin();
	std::vector<BattleSquad*>::iterator ite2 = choosefrom.end();
	for( ; ite1 != choosedends;  ite1++)
	{
		ite2 = std::find(choosefrom.begin(), choosefrom.end(), *ite1);
		choosefrom.erase(ite2);
	}
	while(choosedends != choosed.end())
	{
		choosed.pop_back();
	}
}

//DefendCommander------------------------------------------------
BattleAIState::DefendCommander::DefendCommander(std::string path, std::vector<std::string> squadlist)
:MissionCommander(path, squadlist)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> threatenlist = datalib->getChildList(path + "/CommanderInfo/Threatens");
	std::vector<std::string>::iterator tite = threatenlist.begin();
	for( ; tite != threatenlist.end(); tite++)
	{
		Threaten threaten;
		datalib->getData(str(boost::format("%1%/CommanderInfo/Threatens/%2%")%path%(*tite)), threaten.otherSquadGroupIndex);
		std::vector<std::string> assignsquadlist = datalib->getChildList(str(boost::format("%1%/CommanderInfo/Threatens/%2%")%path%(*tite)));
		std::vector<std::string>::iterator agite = assignsquadlist.begin();
		for( ; agite != assignsquadlist.end(); agite++)
		{
			int index = atoi((*agite).substr(2, (*agite).size() - 2).c_str());
			threaten.assignSquadGroupVec.push_back(index);
		}
		mThreatensVec.push_back(threaten);
	}
}

void BattleAIState::DefendCommander::analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist)
{
	std::map<int, OtherSquadGroupInfo> temposgmap;
	int decision = 1;
	temposgmap.insert(std::make_pair(decision, othersquadgroup));
	OSGCloseToAreaFactor osgclosetoarea(&temposgmap, &mMissionArea);
	OSGMoveToAreaFactor osgmovetoarea(&temposgmap, &mMissionArea);
	if(othersquadgroup.mIsEnemy)
	{
		OtherSquadGroupMission osgm;
		osgm.missionArea = mMissionAreaId;
		osgm.missionType = OSGM_ATTACK;
		osgm.possibility = osgclosetoarea.calcDecision(decision) * 0.5f + osgmovetoarea.calcDecision(decision) * 0.5f;
		std::vector<OtherSquadGroupMission>::iterator ite = missionlist.begin();
		for(; ite != missionlist.end(); ite++)
		{
			if((*ite).missionType == osgm.missionType &&
				(*ite).missionArea == osgm.missionArea)
			{
				(*ite).possibility *= 0.75f;
				(*ite).possibility += osgm.possibility;
				break;
			}
		}
		if(ite == missionlist.end())
		{
			missionlist.push_back(osgm);
		}
		osgm.missionType = OSGM_MOVE_ATTACK;
		osgm.possibility = osgclosetoarea.calcDecision(decision) * 0.25f + osgmovetoarea.calcDecision(decision) * 0.75f;
		ite = missionlist.begin();
		for(; ite != missionlist.end(); ite++)
		{
			if((*ite).missionType == osgm.missionType &&
				(*ite).missionArea == osgm.missionArea)
			{
				(*ite).possibility *= 0.75f;
				(*ite).possibility += osgm.possibility;
				break;
			}
		}
		if(ite == missionlist.end())
		{
			missionlist.push_back(osgm);
		}
	}
	else
	{
		OtherSquadGroupMission osgm;
		osgm.missionArea = mMissionAreaId;
		osgm.missionType = OSGM_DEFEND;
		osgm.possibility = osgclosetoarea.calcDecision(decision) * 0.5f + osgmovetoarea.calcDecision(decision) * 0.5f;
		std::vector<OtherSquadGroupMission>::iterator ite = missionlist.begin();
		for(; ite != missionlist.end(); ite++)
		{
			if((*ite).missionType == osgm.missionType &&
				(*ite).missionArea == osgm.missionArea)
			{
				(*ite).possibility *= 0.75f;
				(*ite).possibility += osgm.possibility;
				break;
			}
		}
		if(ite == missionlist.end())
		{
			missionlist.push_back(osgm);
		}
		osgm.missionType = OSGM_MOVE_DEFEND;
		osgm.possibility = osgclosetoarea.calcDecision(decision) * 0.25f + osgmovetoarea.calcDecision(decision) * 0.75f;
		ite = missionlist.begin();
		for(; ite != missionlist.end(); ite++)
		{
			if((*ite).missionType == osgm.missionType &&
				(*ite).missionArea == osgm.missionArea)
			{
				(*ite).possibility *= 0.75f;
				(*ite).possibility += osgm.possibility;
				break;
			}
		}
		if(ite == missionlist.end())
		{
			missionlist.push_back(osgm);
		}
	}
}

void BattleAIState::DefendCommander::plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup)
{
	//验证威胁是否存在
	std::vector<Threaten>::iterator tite = mThreatensVec.begin();
	std::map<int, OtherSquadGroupInfo>::iterator osgite = othersquadgroup.end();
	std::map<int, SquadGroupCommander>::iterator sgcite = mSquadGroupList.end();
	for( ; tite != mThreatensVec.end(); )
	{
		osgite = othersquadgroup.find((*tite).otherSquadGroupIndex);
		if(osgite != othersquadgroup.end())
		{
			if(osgite->second.getSquadGroupStrength() < 0.01f)
			{
				osgite = othersquadgroup.end();
			}
			else if(osgite->second.mCurMission.missionType == OSGM_IDLE ||
				osgite->second.mCurMission.missionArea != mMissionAreaId)
			{
				osgite = othersquadgroup.end();
			}
		}
		if(osgite == othersquadgroup.end())
		{
			for(unsigned int m = 0;  m < (*tite).assignSquadGroupVec.size(); m++)
			{
				sgcite = mSquadGroupList.find((*tite).assignSquadGroupVec[m]);
				if(sgcite != mSquadGroupList.end())
				{
					mSquadGroupList.erase(sgcite);
				}
			}
			tite = mThreatensVec.erase(tite);
		}
		else
		{
			//移除无人的分组
			for(unsigned int m = 0;  m < (*tite).assignSquadGroupVec.size(); m++)
			{
				sgcite = mSquadGroupList.find((*tite).assignSquadGroupVec[m]);
				if(sgcite != mSquadGroupList.end())
				{
					if(sgcite->second.getSquadGroupStrength() < 0.01f)
						mSquadGroupList.erase(sgcite);
				}
			}
			tite++;
		}
	}
	//添加新的威胁
	osgite = othersquadgroup.begin();
	for( ; osgite != othersquadgroup.end(); osgite++)
	{
		if(!osgite->second.mIsEnemy)
		{
			continue;
		}
		if(osgite->second.getSquadGroupStrength() < 0.01f)
		{
			continue;
		}
		else if(osgite->second.mCurMission.missionType == OSGM_IDLE ||
			osgite->second.mCurMission.missionArea != mMissionAreaId)
		{
			continue;
		}
		tite = mThreatensVec.begin();
		for( ; tite != mThreatensVec.end(); tite++)
		{
			if((*tite).otherSquadGroupIndex == osgite->first)
				break;
		}
		if(tite == mThreatensVec.end())
		{
			Threaten threaten;
			threaten.otherSquadGroupIndex = osgite->first;
			mThreatensVec.push_back(threaten);
		}
	}
	//对威胁排序
	std::vector<int> osgvec;
	tite = mThreatensVec.begin();
	for( ; tite != mThreatensVec.end(); tite++)
	{
		osgvec.push_back((*tite).otherSquadGroupIndex);
	}

	DecisionMap<int> threatendecision(osgvec);
	threatendecision.addFactor(new OSGStrengthFactor(&othersquadgroup), 0.25f);
	threatendecision.addFactor(new OSGMoveToAreaFactor(&othersquadgroup, &mMissionArea), 0.25f);
	threatendecision.addFactor(new OSGCloseToAreaFactor(&othersquadgroup, &mMissionArea), 0.5f);
	threatendecision.calcDecision();
	osgvec = threatendecision.getSortedDecisions();

	std::vector<Threaten> oldthreaten = mThreatensVec;
	mThreatensVec.clear();
	std::vector<int>::iterator soredosgite = osgvec.begin();
	for( ;soredosgite != osgvec.end(); soredosgite++)
	{
		tite = oldthreaten.begin();
		for( ; tite != oldthreaten.end(); tite++)
		{
			if((*tite).otherSquadGroupIndex == (*soredosgite))
			{
				mThreatensVec.push_back(*tite);
				oldthreaten.erase(tite);
				break;
			}
		}
	}

	//检查并重新指派现有部队任务
	tite = mThreatensVec.begin();
	for( ; tite != mThreatensVec.end(); tite++)
	{
		osgite = othersquadgroup.find((*tite).otherSquadGroupIndex);
		for(unsigned int m = 0;  m < (*tite).assignSquadGroupVec.size(); m++)
		{
			sgcite = mSquadGroupList.find((*tite).assignSquadGroupVec[m]);
			if(sgcite != mSquadGroupList.end())
			{
				int targettype = 0;
				Crood targetcrood;
				sgcite->second.getTarget(targettype, targetcrood);
				switch(targettype)
				{
				case SGM_RALLY:
					break;
				case SGM_ATTACK:
					break;
				case SGM_DEFEND:
					break;
				}
			}
		}
	}
	
	//寻找空闲的部队
	std::vector<BattleSquad*> freeSquads = getFreeSquads();
	if(freeSquads.size() > 0)
	{
		std::vector<BattleSquad*>::iterator squadsite = freeSquads.end();
		tite = mThreatensVec.begin();
		for( ; tite != mThreatensVec.end(); tite++)
		{
			if(freeSquads.size() == 0)
				break;
			osgite = othersquadgroup.find((*tite).otherSquadGroupIndex);
			float threatenstrength = osgite->second.getSquadGroupStrength();
			float curdefendstrength = 0.0f;
			float curmainstrength = 0.0f;
			float currangestrength = 0.0f;
			float curclosestrength = 0.0f;
			for(unsigned int m = 0;  m < (*tite).assignSquadGroupVec.size(); m++)
			{
				sgcite = mSquadGroupList.find((*tite).assignSquadGroupVec[m]);
				if(sgcite != mSquadGroupList.end())
				{
					curdefendstrength += sgcite->second.getSquadGroupStrength();
					switch(sgcite->second.mType)
					{
					case SG_SUPPORT_RANGE:
						currangestrength += sgcite->second.getSquadGroupStrength();
						break;
					case SG_SUPPORT_CLOSE:
						curclosestrength+= sgcite->second.getSquadGroupStrength();
						break;
					default:
						curmainstrength += sgcite->second.getSquadGroupStrength();
						break;
					}
				}
			}
			//创建新的分组并指派任务
			//创建主战分组
			if(freeSquads.size() > 0 && curmainstrength < threatenstrength * 0.5f)
			{
				DecisionMap<BattleSquad*> formgroupdecision(freeSquads);
				formgroupdecision.addFactor(new SquadRolebyTypeFactor(ROLETYPE_MAINFORCE), 1.0f);
				formgroupdecision.calcDecision();
				std::vector<BattleSquad*> choosesquads = formgroupdecision.getHigherThan(30.0f);
				squadsite = choosesquads.begin();
				for( ; squadsite != choosesquads.end(); squadsite++)
				{
					if(curmainstrength > threatenstrength * 0.5f)
						break;
					curmainstrength += (*squadsite)->getSquadStrength();
					curdefendstrength += (*squadsite)->getSquadStrength();
				}
				chooseSquads(freeSquads, choosesquads, squadsite);
				int createdsg = createSquadGroup(SG_MAIN, choosesquads);
				sgcite = mSquadGroupList.find(createdsg);
				if(sgcite != mSquadGroupList.end())
				{	
					//是否需要集合
					if(!sgcite->second.isRallied() &&
						osgite->second.mArea.crossed(mMissionArea))
					{
						Crood targetcrood = mMissionArea.getCenter();
						sgcite->second.setTarget(SGM_RALLY, targetcrood);						
					}
					else 
					{
						Crood targetcrood = mMissionArea.getCenter();
						sgcite->second.setTarget(SGM_ATTACK, targetcrood);
					}
					(*tite).assignSquadGroupVec.push_back(createdsg);
				}
			}
			//创建远程支援分组
			if(freeSquads.size() > 0 && currangestrength < threatenstrength * 0.4f)
			{
				DecisionMap<BattleSquad*> formgroupdecision(freeSquads);
				formgroupdecision.addFactor(new SquadRolebyTypeFactor(ROLETYPE_SUPPORT_RANGE), 1.0f);
				formgroupdecision.calcDecision();
				std::vector<BattleSquad*> choosesquads = formgroupdecision.getHigherThan(30.0f);
				squadsite = choosesquads.begin();
				for( ; squadsite != choosesquads.end(); squadsite++)
				{
					if(currangestrength > threatenstrength * 0.4f)
						break;
					curmainstrength += (*squadsite)->getSquadStrength();
					currangestrength += (*squadsite)->getSquadStrength();
				}
				chooseSquads(freeSquads, choosesquads, squadsite);
				int createdsg = createSquadGroup(SG_SUPPORT_RANGE, choosesquads);
				sgcite = mSquadGroupList.find(createdsg);
				if(sgcite != mSquadGroupList.end())
				{	
					//是否需要集合
					if(!sgcite->second.isRallied() &&
						!osgite->second.mArea.crossed(mMissionArea))
					{
						Crood targetcrood = mMissionArea.getCenter();
						sgcite->second.setTarget(SGM_RALLY, targetcrood);						
					}
					else 
					{
						Crood targetcrood = mMissionArea.getCenter();
						sgcite->second.setTarget(SGM_DEFEND, targetcrood);
					}
					(*tite).assignSquadGroupVec.push_back(createdsg);
				}
			}
			//创建应急分组
			/*
			while(freeSquads.size() > 0 && curdefendstrength <　threatenstrength * 0.75f)
			{

			}
			*/
		}
	}

	mState = MCS_EXECUTE;
}

void BattleAIState::DefendCommander::write(std::string path)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	for(unsigned int n = 0; n < mThreatensVec.size(); n++)
	{
		datalib->setData(str(boost::format("%1%/CommanderInfo/Threatens/t%2%")%path%n), mThreatensVec[n].otherSquadGroupIndex);
		for(unsigned int m = 0;  m < mThreatensVec[n].assignSquadGroupVec.size(); m++)
		{
			datalib->setData(str(boost::format("%1%/CommanderInfo/Threatens/t%2%/sg%3%")%path%n%mThreatensVec[n].assignSquadGroupVec[m]), 1);
		}
	}
}
//AttackCommander------------------------------------------------
BattleAIState::AttackCommander::AttackCommander(std::string path, std::vector<std::string> squadlist)
:MissionCommander(path, squadlist)
{

}

void BattleAIState::AttackCommander::analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist)
{

}

void BattleAIState::AttackCommander::plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup)
{
	mState = MCS_EXECUTE;
}

void BattleAIState::AttackCommander::write(std::string path)
{

}
//MoveCommander--------------------------------------------------
BattleAIState::MoveCommander::MoveCommander(std::string path, std::vector<std::string> squadlist)
:MissionCommander(path, squadlist)
{

}

void BattleAIState::MoveCommander::analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist)
{

}

void BattleAIState::MoveCommander::plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup)
{
	mState = MCS_EXECUTE;
}

void BattleAIState::MoveCommander::write(std::string path)
{

}
//---------------------------------------------------------------

void BattleAIState::createMissionCommanders()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> grouplist = 
		datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/Group")%mTeam));
	std::vector<std::string> missionlist = 
		datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission")%mTeam));
	std::vector<std::string>::iterator missionite = missionlist.begin();
	for( ; missionite != missionlist.end(); missionite++)
	{
		//寻找指派的部队
		std::vector<std::string> squadlist;
		std::vector<std::string>::iterator groupite = grouplist.begin();
		for( ; groupite != grouplist.end(); )
		{
			std::string missionid;
			datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/Group/%2%/Mission")%mTeam%(*groupite)),missionid);
			if(missionid == (*missionite))
			{
				std::vector<std::string> groupsquadlist = 
					datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/Group/%2%/SquadList")%mTeam%(*groupite)));
				squadlist.insert(squadlist.end(), groupsquadlist.begin(), groupsquadlist.end());
				groupite = grouplist.erase(groupite);
			}
			else
			{
				groupite++;
			}
		}

		//创建指挥官
		int missiontype = 0;
		datalib->getData(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%mTeam%(*missionite)),missiontype);
		MissionCommander *missioncommander;
		switch(missiontype)
		{
		case MISSIONTYPE_ATTACK:
			missioncommander = new AttackCommander(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%mTeam%(*missionite)) ,squadlist);
			break;
		case MISSIONTYPE_MOVE:
			missioncommander = new MoveCommander(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%mTeam%(*missionite)) ,squadlist);
			break;
		default:
			missioncommander = new DefendCommander(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%mTeam%(*missionite)) ,squadlist);
			break;
		}
		mMissionCmdMap.insert(std::make_pair(*missionite, missioncommander));
	}

}

void BattleAIState::writeMissionCommanders()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> missionlist = 
		datalib->getChildList(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission")%mTeam));
	std::vector<std::string>::iterator missionite = missionlist.begin();
	for( ; missionite != missionlist.end(); missionite++)
	{
		std::map<std::string, MissionCommander*>::iterator mcmdite = mMissionCmdMap.find(*missionite);
		if(mcmdite != mMissionCmdMap.end())
		{
			mcmdite->second->writeMissionCommander(str(boost::format("GameData/BattleData/AIData/Team%1%/Mission/%2%")%mTeam%mcmdite->first));
		}
	}
}