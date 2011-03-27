#pragma once

#include "SubBattleState.h"

#include <string>
class MapDataManager;

const int LOADTERRAIN = 0;
const int LOADGRID = 1;

class BattleLoadState: public SubBattleState
{
public:
	BattleLoadState(BattleState* mainSate, std::string arg);
	~BattleLoadState();

	virtual void update(unsigned int deltaTime);
private:
	MapDataManager *mMapDataManager;
	int mState;
};