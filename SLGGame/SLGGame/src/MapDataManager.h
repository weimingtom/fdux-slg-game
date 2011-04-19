#pragma once

#include <string>
#include "iisingleton.hpp"
using namespace izayoi;

typedef int GroundType;
static const int	GreenLand = 0;
static const int	Desert = 1;
static const int	Swamp = 2;
static const int	Snow = 3;

typedef int TerrainType;
static const int	Water = 0;
static const int	LowGround = 1;
static const int	HighGround = 2;
static const int	Cliff = 3;
static const int	Ramp = 4;

class Terrain;

class MapDataManager: public IISingleton<MapDataManager>
{
public:
	MapDataManager();
	~MapDataManager();

	bool loadMapFormFile(std::string mapname);
	void loadMapObj();

	GroundType getGroundType(int x, int y);
	TerrainType getTerrainType(int x, int y);
	int getMapSize() {return mMapSize;}
	bool getPassable(int x, int y, int team);
	int getInfApCost(int x, int y, int team);
	int getCavApCost(int x, int y, int team);
	int getDefModify(int x, int y, int team);
private:
	int mMapSize;
};