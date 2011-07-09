#pragma once

#include <string>

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
	void creatSquadGrapAtPath(std::string path);
};