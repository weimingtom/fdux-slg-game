#pragma once

#include <string>
#include <queue>

#include "squaddefine.h"

class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	bool loadMapFormFile(std::string mapname);
	bool loadMapFormSave();

	void loadMapObj();

	void initBattleSquad(bool loadfrommap);

	void initMapScript();
private:
	//void creatSquadGrapAtPath(std::string path);
	struct MapSquadInfo
	{
		std::string squadId;
		std::string squadTempId;
		int team;
		int x,y;
		int unitNum;
		int dir;
	};
	std::queue<MapSquadInfo> mMapSquadInfo;
};