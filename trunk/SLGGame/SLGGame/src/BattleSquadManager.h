#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <vector>

#include "squaddefine.h"

class BattleSquad;

class BattleSquadManager:public IISingleton<BattleSquadManager>
{
public:
	BattleSquadManager();
	~BattleSquadManager();

	void initBattleSquad(bool loadfrommap);

	typedef std::vector<BattleSquad*>::iterator BattleSquadIte;
	std::vector<BattleSquad*> mSquadList;
	std::vector<BattleSquad*> mDeployList;

	void deployConfirm();
	bool allDeployed();
private:
	int mCurid;
	void creatSquadGrapAtPath(std::string path);
};