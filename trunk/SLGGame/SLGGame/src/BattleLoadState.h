#pragma once

#include "SubBattleState.h"

#include <string>
class LoadScene;
class MapLoader;

const int LOADSCENE = 0;
const int LOADTERRAIN = 1;
const int LOADOBJECT = 2;
const int LOADUNIT = 3;
const int LOADGRID = 4;

class BattleLoadState: public SubBattleState
{
public:
	BattleLoadState(std::string arg);
	~BattleLoadState();

	virtual void update(unsigned int deltaTime);
private:
	MapLoader *mMapLoader;
	LoadScene* mLoadScene;
	bool mLoadFromMap;
	std::string mMapFile;
	int mState;
};