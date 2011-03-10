#pragma once

#include "SquadGraphics.h"

class UnitAnimationControl
{
public:
	UnitAnimationControl(void);
	~UnitAnimationControl(void);

	void moveUnit(SquadGraphics* unit,int x,int y);

	void useSkill(SquadGraphics* srcUnit,SquadGraphics* destUnit,std::string name);
};
