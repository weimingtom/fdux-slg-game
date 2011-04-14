#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <vector>

#include "squaddefine.h"

class BattleSquadManager:public IISingleton<BattleSquadManager>
{
public:
	BattleSquadManager();
	~BattleSquadManager();

	void initBattleSquad(bool loadfrommap);
private:
	int mCurid;
	void creatSquadGrapAtPath(std::string path);
};