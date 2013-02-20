#pragma once

#include <vector>
#include <map>

#include "SubBattleState.h"

#include "Area.h"

#include "DecisionMapFactor.h"

class BattleSquad;

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
	enum AreaType
	{	
		AREATYPE_PLANE,
		AREATYPE_NARROW,
		AREATYPE_DEADCRORNER
	};

	class MapArea
	{
	public:
		MapArea(std::string path);
		MapArea(int areatype, std::vector<Crood> croodVec);

		void writeMapArea(std::string path);

		int mType;
		Area mArea;
		std::vector<int> mConnectedArea;
	private:

	};

	std::map<int, MapArea> mAreaVec;

	bool AnalyzeMap();
	bool ReadMap();
	bool CreateMap();
	
	//他队活动信息
	enum OtherSquadGroupMissionType
	{
		OSGM_IDLE,
		OSGM_ATTACK,
		OSGM_MOVE_ATTACK,
		OSGM_DEFEND,
		OSGM_MOVE_DEFEND
	};

	struct OtherSquadGroupMission
	{
		int missionType;
		std::string missionArea;
		float possibility;
	};

	class OtherSquadGroupInfo
	{
	public:
		OtherSquadGroupInfo(std::string path);
		OtherSquadGroupInfo(bool isenemy);

		void writeOtherSquadGroupInfo(std::string path);

		float getSquadGroupStrength();

		bool mIsEnemy;
		std::vector<std::string> mSquadList;

		OtherSquadGroupMission mCurMission;

		Crood mCenterCrood;
		Crood mLastCenterCrood;
		Area mArea;
	private:

	};
	std::map<int, OtherSquadGroupInfo> mOtherSquadGroupVec;

	void findOtherSquadGroup();
	void saveOtherSquadGroup();
	
	//DecisionMapFactors
	class OSGStrengthFactor : public DecisionMapFactor<int>
	{
	public:	
		OSGStrengthFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup);

		virtual float calcDecision(int &decision);
	private:
		std::map<int, OtherSquadGroupInfo>* mOtherSquadGroup;
		float mMaxStrength;
	};

	class OSGCloseToAreaFactor : public DecisionMapFactor<int>
	{
	public:	
		OSGCloseToAreaFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup, Area* area);

		virtual float calcDecision(int &decision);
	private:
		std::map<int, OtherSquadGroupInfo>* mOtherSquadGroup;
		Area* mArea;
	};

	class OSGMoveToAreaFactor : public DecisionMapFactor<int>
	{
	public:	
		OSGMoveToAreaFactor(std::map<int, OtherSquadGroupInfo>* othersquadgroup, Area* area);

		virtual float calcDecision(int &decision);
	private:
		std::map<int, OtherSquadGroupInfo>* mOtherSquadGroup;
		Area* mArea;
	};

	//部队AI
	enum SquadGroupMissionType
	{
		SGM_WAIT,
		SGM_MOVE,
		SGM_RALLY,
		SGM_DEFEND,
		SGM_ATTACK,
		SGM_SUPPORT_RANGE,
		SGM_SUPPORT_CLOSE
	};

	class SquadAI
	{
	public:
		SquadAI(BattleSquad* squad);

		bool update();
		void setTarget(int targettype, Crood tragetcrood);

		BattleSquad* mSquad;
	private:
		enum SquadAIState
		{
			SAS_MOVE,
			SAS_FORMATION,
			SAS_SKILL,
			SAS_DIRECTION,
			SAS_WAIT
		};
		SquadAIState mState;

		int mTargetType;
		Crood mTargetCrood;

		float mLastActiveAP;

		void updateMove();
		void updateFormation();
		void updateSkill();
		void updateDirection();
	};

	//分组指挥
	enum SquadGroupType
	{
		SG_MAIN,
		SG_SUPPORT_RANGE,
		SG_SUPPORT_CLOSE
	};

	class SquadGroupCommander
	{
	public:
		SquadGroupCommander(std::string path, std::vector<std::string> squadlist);
		SquadGroupCommander(int type, std::vector<BattleSquad*> squadlist);

		bool update();
		void setTarget(int targettype, Crood tragetcrood);
		void getTarget(int &targettype, Crood &tragetcrood);
		
		void writeSquadGroupCommander(std::string path);

		float getSquadGroupStrength();
		bool isRallied();

		int mType;
		std::vector<SquadAI> mSquadList;
	private:
		int mTargetType;
		Crood mTargetCrood;
	};

	//任务指挥
	enum MissionType
	{
		MISSIONTYPE_DEFEND,
		MISSIONTYPE_ATTACK,
		MISSIONTYPE_MOVE
	};

	class MissionCommander
	{
	public:
		MissionCommander(std::string path, std::vector<std::string> squadlist);

		bool update(std::map<int, OtherSquadGroupInfo>& othersquadgroup);
		virtual void analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist) = 0;

		void writeMissionCommander(std::string path);
	protected:
		std::vector<std::string> mSquadList;
		std::string mMissionAreaId;
		Area mMissionArea;
		int mVaildId;
		std::map<int, SquadGroupCommander> mSquadGroupList;

		enum MissionCommanderState
		{
			MCS_PLAN,
			MCS_EXECUTE
		};
		MissionCommanderState mState;

		std::vector<BattleSquad*> getFreeSquads();
		int createSquadGroup(int type, std::vector<BattleSquad*> squadlist);
	
		virtual void plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup) = 0;
		virtual void write(std::string path) = 0;

		//辅助函数
		void chooseSquads(std::vector<BattleSquad*>& choosefrom,
			std::vector<BattleSquad*>& choosed, 
			std::vector<BattleSquad*>::iterator& choosedends);
	};

	class DefendCommander: public MissionCommander
	{
	public:
		DefendCommander(std::string path, std::vector<std::string> squadlist);
		
		virtual void analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist);
	private:
		virtual void plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup);
		virtual void write(std::string path);

		struct Threaten
		{
			int otherSquadGroupIndex;
			std::vector<int> assignSquadGroupVec;
		};
		std::vector<Threaten> mThreatensVec;

		//辅助函数
		void rallySquadGroup(SquadGroupCommander& sg, int osgindex, 
			std::map<int, OtherSquadGroupInfo>& othersquadgroup);
		void updateMission(SquadGroupCommander& sg, int osgindex, 
			std::map<int, OtherSquadGroupInfo>& othersquadgroup);
	};
		
	class AttackCommander: public MissionCommander
	{
	public:
		AttackCommander(std::string path, std::vector<std::string> squadlist);

		virtual void analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist);
	private:
		virtual void plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup);
		virtual void write(std::string path);
	};
	
	class MoveCommander: public MissionCommander
	{
	public:
		MoveCommander(std::string path, std::vector<std::string> squadlist);

		virtual void analyzeMission(OtherSquadGroupInfo& othersquadgroup, 
			std::vector<OtherSquadGroupMission>& missionlist);
	private:
		virtual void plan(std::map<int, OtherSquadGroupInfo>& othersquadgroup);
		virtual void write(std::string path);
	};

	//总指挥
	void createMissionCommanders();
	void writeMissionCommanders();
	std::map<std::string, MissionCommander*> mMissionCmdMap;
};