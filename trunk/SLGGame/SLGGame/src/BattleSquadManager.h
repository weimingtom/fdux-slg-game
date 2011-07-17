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

	void clear();

	typedef std::vector<BattleSquad*>::iterator BattleSquadIte;
	std::vector<BattleSquad*> mSquadList;
	std::vector<BattleSquad*> mDeployList;

	void deployConfirm();
	bool allDeployed();

	int getTeamSquadLeft(int team);

	BattleSquad* getBattleSquad(std::string id);
	BattleSquad* getBattleSquadAt(int x, int y, int team, bool visibleonly);

	void moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype);

	CutScene* useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid);
	CutScene* useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid);

	//½Å±¾µ÷ÓÃ
	bool meleeAttackSquad(BattleSquad* attacksquad, BattleSquad* defenesquad);
	
	bool dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk);

	bool dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad);

	void rangedAttackCutScene(BattleSquad* attacksquad, int x, int y, UnitType castunit , std::string castparticle, std::string castaction, std::string castsound, int missiletype, std::string missileres, std::string hitparticle,std::string hitsound);

	void setCutScene(CutScene* cutscene);
	CutScene* getCutScene();
private:
	int mCurid;
	CutScene* mCutSceneQueue;
	CutScene* mLastCutScene;
};