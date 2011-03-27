#pragma once

#include <string>

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

class MapDataManager
{
public:
	MapDataManager();
	~MapDataManager();

	bool loadMap(std::string mapname);

	GroundType getGroundType(int x, int y);
	TerrainType getTerrainType(int x, int y);
	int getMapSize() {return mMapSize;}
private:
	int mMapSize;
};