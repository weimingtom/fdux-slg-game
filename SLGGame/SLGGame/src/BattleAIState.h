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
	void clearSquadGroup();
	void updateSquadGroup();

	typedef std::vector<BattleSquad*> SquadVector;
	typedef std::vector<BattleSquad*>::iterator SquadIte;
	
	int mTeam;

	enum MissionType
	{
		MISSION_RALLY = 0,	//¾Û¼¯
		MISSION_ATTACK = 1,	//·¢¶¯¹¥»÷
		MISSION_ASSIST = 2, //Ö§Ô®Ä³×é
		MISSION_ASSAULT = 3 //Í»Ï®Ä³×é
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

	//¸¨Öúº¯Êý
	Direction getDirection(int sx, int sy, int x, int y);
	bool getAssigedMission(bool isenemy,unsigned short id);
};