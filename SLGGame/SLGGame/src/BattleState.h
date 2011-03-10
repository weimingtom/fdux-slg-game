#pragma once
#include "gamestate.h"

class Terrain;
class CameraContral;
class MapDataManager;

class SquadGrapManager;

class BattleState :
	public GameState
{
public:
	BattleState(void);
	~BattleState(void);

	void initialize(std::string arg);

	void uninitialize();

	void update(unsigned int deltaTime);

private:

	MapDataManager *mMapDataManager; //管理地图数据
	Terrain *mTerrain; //地形试图
	CameraContral *mCameraContral; //摄像机管理

	SquadGrapManager* mUnitGrapManager;
};