#pragma once

#include "UnitGraphics.h"

#include <string>
#include <vector>

class UnitGrapManager
{
public:
	UnitGrapManager(void);
	~UnitGrapManager(void);

	UnitGraphics* createUnit(std::string unitName,int x,int y);
	void destoryUnit(UnitGraphics* unit);

	void update();

private:
	std::vector<UnitGraphics*> mUnitList;
};
