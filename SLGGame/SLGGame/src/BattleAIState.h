#pragma once

#include "SubBattleState.h"

#include "squaddefine.h"

#include <vector>
#include <map>

class BattleSquadManager;
class BattleSquad;

class SquadGroup
{
public:
	SquadGroup(BattleSquad* squad);
	~SquadGroup();

	typedef std::vector<BattleSquad*> SquadVector;
	typedef std::vector<BattleSquad*>::iterator SquadIte;

	bool addSquad(BattleSquad* squad);
	bool IsInGroup(BattleSquad* squad);

	bool updateSquad();

	unsigned int getGroupSize();

	BattleSquad* GetNearestFrom(int x, int y);
	BattleSquad* GetFurthestFrom(int x, int y);

	float getLowestAp();

	SquadVector getSquadList();

	void getMidPoint(int &x, int &y);
private:
	SquadVector mSquadList;

	int mMidX;
	int mMidY;
};


class BattleAIState:public SubBattleState
{
public:
	BattleAIState(int team);
	~BattleAIState();

	void newTurn();

	virtual void update(unsigned int deltaTime);
private:
	BattleSquadManager* mSquadManager;
	
	typedef std::map<unsigned short,SquadGroup*> SquadGroupMap;
	typedef std::map<unsigned short,SquadGroup*>::iterator SquadGroupIte;
	SquadGroupMap mMySquadGroup;
	SquadGroupMap mEnemySquadGroup;
	unsigned short mEnmeySquadGroupId;
	void clearSquadGroup();
	void updateSquadGroup();

	typedef std::vector<BattleSquad*> SquadVector;
	typedef std::vector<BattleSquad*>::iterator SquadIte;
	
	int mTeam;

	enum MissionType
	{
		MISSION_RALLY = 0,	//聚集
		MISSION_ATTACK = 1,	//发动攻击
		MISSION_ASSIST = 2, //支援某组
		MISSION_ASSAULT = 3 //突袭某组
	};
	struct Mission
	{
		MissionType mMisstionType;
		int mParaList[5];
		std::vector<unsigned short> mAssigedGroup;
	};
	typedef std::map<unsigned short,Mission*> MissionMap;
	typedef std::map<unsigned short,Mission*>::iterator MissionIte;
	MissionMap mMissionMap;
	int mMissionId;

	bool executeStrategy();
	void updateMission();
	void assignMission();
	bool executeGroupAI();
	bool executeSquadAI(BattleSquad* squad, unsigned int missionid);

	//辅助函数
	bool getAssigedMission(bool isenemy,unsigned short id);
	unsigned short getMissionStrength(unsigned short id);
	unsigned short getMission(unsigned short groupid);
	unsigned short getBlockSquadNum(int x1, int y1, int x2, int y2, unsigned short ignoreid = 0);
	float getSkillAPCost(BattleSquad* squad, std::string skillname);

	//移动点
	struct MoveNode
	{
		int x;
		int y;
		Direction mDirectionToPrev;
		float mPrevApLeft;
		float mAPleft;
		unsigned short mInterest;
		MoveNode()
		{
			x = -1;
			y = -1;
			mDirectionToPrev = 0;
			mPrevApLeft = 0.0f;
			mAPleft = 0.0f;
			mInterest = 100;
		}
	};
	std::map<int, MoveNode*> mMoveMap;
	typedef std::map<int, MoveNode*>::value_type MapNodeType;
	typedef std::map<int, MoveNode*>::iterator MapNodeIte;
	void createMoveArea(BattleSquad* squad);
	bool canPass(BattleSquad* squad,int x, int y, float &apcost);
	void clearMoveArea();

	void calcAwayFromSquad(BattleSquad* squad, unsigned short ignoreid = 0 );
	void calcClosetoMissionPoint(BattleSquad* squad, unsigned int missionid);
	void calcAPointLeft(BattleSquad* squad);
	void calcBattlePos(BattleSquad* squad, unsigned squadgroupid);

	SquadVector getAroundSquad(BattleSquad* squad);

};