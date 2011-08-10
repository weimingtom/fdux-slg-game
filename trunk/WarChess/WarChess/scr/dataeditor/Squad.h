#pragma once

#include "Modifier.h"



class Squad
{
public:
	Squad();
	~Squad();
private:

	AttrModifier mAttr;
	map<int, AttrModifier> mAttrModifierList;
};