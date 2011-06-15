#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <vector>

#include "squaddefine.h"

class BattleSquad;
class MapLoader;
class CutScene;

class BattleSquadManager:public IISingleton<BattleSquadManager>
{
public:
	friend MapLoader;

	BattleSquadManager();
	~BattleSquadManager();

	typedef std::vector<BattleSquad*>::iterator BattleSquadIte;
	std::vector<BattleSquad*> mSquadList;
	std::vector<BattleSquad*> mDeployList;

	void deployConfirm();
	bool allDeployed();
	int getTeamRelation(int team);

	BattleSquad* getBattleSquad(std::string id);
	BattleSquad* getBattleSquadAt(int x, int y, int team, bool visibleonly);

	void moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype);

	CutScene* useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid);
	CutScene* useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid);

	//½Å±¾µ÷ÓÃ
	bool meleeAttackSquad(BattleSquad* attacksquad, BattleSquad* defenesquad);
	void setCutScene(CutScene* cutscene);
private:
	int mCurid;
	CutScene* mCutSceneQueue;
	CutScene* mLastCutScene;
};