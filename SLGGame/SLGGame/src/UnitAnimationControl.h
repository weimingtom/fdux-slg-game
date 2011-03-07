#pragma once

#include "UnitGraphics.h"

class UnitAnimationControl
{
public:
	UnitAnimationControl(void);
	~UnitAnimationControl(void);

	void moveUnit(UnitGraphics* unit,int x,int y);

	void useSkill(UnitGraphics* srcUnit,UnitGraphics* destUnit,std::string name);
};
