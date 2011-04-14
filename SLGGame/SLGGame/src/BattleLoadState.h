#pragma once

#include "SubBattleState.h"

#include <string>
class MapDataManager;
class LoadScene;

const int LOADSCENE = 0;
const int LOADTERRAIN = 1;
const int LOADOBJECT = 2;
const int LOADUNIT = 3;
const int LOADGRID = 4;

class BattleLoadState: public SubBattleState
{
public:
	BattleLoadState(BattleState* mainSate, std::string arg);
	~BattleLoadState();

	virtual void update(unsigned int deltaTime);
private:
	MapDataManager *mMapDataManager;
	LoadScene* mLoadScene;
	bool mLoadFromMap;
	std::string mMapFile;
	int mState;
};