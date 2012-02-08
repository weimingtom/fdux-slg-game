#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <map>
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

	typedef std::map<std::string, BattleSquad*>::iterator BattleSquadIte;
	std::map<std::string, BattleSquad*> mSquadList;

	bool allDeployed();

	BattleSquad* getBattleSquad(std::string id);
	BattleSquad* getBattleSquadAt(int x, int y, bool visibleonly);

	void moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype);

	bool useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid);
	bool useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid);

	//½Å±¾µ÷ÓÃ
	bool dealMeleeDamage(BattleSquad* attacksquad, BattleSquad* defenesquad);
	
	bool dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk, int fluctuate);

	bool dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad);
};