#pragma once

#include <vector>
#include <map>

#include "SubBattleState.h"

class BattleAIState:public SubBattleState
{
public:
	BattleAIState(int team);
	~BattleAIState();

	virtual void update(unsigned int deltaTime);
private:
	int mTeam;

	enum AIState
	{
		AISTATE_INIT,
		AISTATE_EXECUTE,
		AISTATE_SHUTDOWN
	};

	AIState mState;

	//地图区域信息
	struct MapCrood
	{
		int x;
		int y;
		MapCrood()
		:x(0),y(0)
		{
		}
		MapCrood(int inx, int iny)
		:x(inx),y(iny)
		{
		}
	};

	enum AreaType
	{	
		AreaType_Plane,
		AreaType_Narrow,
		AreaType_DeadCorner
	};

	class MapArea
	{
	public:
		MapArea();
		~MapArea();

		void AddCrood(int x, int y);

		int mType;
		std::vector<MapCrood> mArea;
		std::vector<int> mConnectedArea;
	private:

	};

	std::map<int, MapArea*> mAreaVec;

	bool AnalyzeMap();
	bool ReadMap();
	bool CreateMap();
	
	//他队活动信息
	enum TargetType
	{
		TargetType_Move,
		TargetType_Attack,
		TargetType_Defence,
		TargetType_Flank,
		TargetType_Contain,
		TargetType_PassThrough,
		TargetType_Scout,
		TargetType_Join	
	};

	struct SquadGroupTarget
	{
		int type;
		int areaId;
		int groupId;
		MapCrood targetPos;
		int possibility;
	};

	class SquadGroup
	{
	public:
		std::vector<std::string> mSquadList;
		std::vector<SquadGroupTarget> mTargetList;
		
		MapCrood mCenterCrood;
		int mStrength;

		int ReCalcStrength();
		MapCrood  ReCalcCenterCrood();
	private:

	};

	std::map<int, SquadGroup*> mSquadGroupVec;

	void AnalyzeOtherTeam();
	void SaveOtherTeamInfo();

	//己队任务分配
};