#pragma once

#include "Modifier.h"

class ScriptContext;

enum PWeaponType
{
	PWEAPON_NONE = 0,
	PWEAPON_MACE = 1,
};

enum SWeaponType
{
	SWEAPON_NONE = 0,
	SWEAPON_BOW = 1,
	SWEAPON_XBOW = 2,
};

enum ArmorType
{
	ARMOR_NONE = 0,
	ARMOR_MAIL = 1,
};

class SquadEquip
{
public:
	SquadEquip();
	~SquadEquip();
private:
	std::string mId;
	int mAttrModifierId;
	ScriptContext* mScriptContext;
};