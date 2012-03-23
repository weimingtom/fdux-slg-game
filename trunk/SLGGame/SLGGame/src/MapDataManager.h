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

class MapLoader;
struct LuaTempContext;

class MapDataManager: public IISingleton<MapDataManager>
{
public:
	friend MapLoader;

	MapDataManager();
	~MapDataManager();

	GroundType getGroundType(int x, int y);
	TerrainType getTerrainType(int x, int y);
	int getMapSize() {return mMapSize;}
	bool getPassable(int x, int y, int team);
	float getInfApCost(int x, int y, int team);
	float getCavApCost(int x, int y, int team);
	float getCovert(int x, int y, int team);
	float getDefModify(int x, int y, int team);
	
//´¥·¢Æ÷
public:
	std::string addTrigger(std::string trigertype, std::string file ,std::string func, std::string context);
	void removeTrigger(std::string tid);

	void activeTrigger(std::string tid);
	void disableTrigger(std::string tid);

	void Trigger(std::string triggertype, LuaTempContext * tempcontext);
private:
	int mMapSize;
};