#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <vector>

#include "squaddefine.h"

class Squad;

class AVGSquadManager:public IISingleton<AVGSquadManager>
{
public:
	AVGSquadManager();
	~AVGSquadManager();

public:
	bool addNewSquad(std::string squadid, std::string suqadtypeid);

	void dumpSquad(Squad* squad);
};