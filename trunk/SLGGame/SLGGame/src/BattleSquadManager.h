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

	BattleSquad* getBattleSquadAt(int x, int y, int team, bool visibleonly);

	void moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype);

	void meleeAttackSquad(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktype);

	void setCutScene(CutScene* cutscene);
	void playCutScene();
private:
	int mCurid;
	CutScene* mCutSceneQueue;
	CutScene* mLastCutScene;
};