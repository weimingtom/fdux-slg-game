#pragma once

typedef int EquipmentType;
const EquipmentType EQUIP_SOILDER = 0;
const EquipmentType EQUIP_HORSE = 1;
const EquipmentType EQUIP_ARMOR = 2;
const EquipmentType EQUIP_SHIELD = 3;
const EquipmentType EQUIP_PWEAPON = 4;
const EquipmentType EQUIP_SWEAPON = 5;

typedef int AttrModifierType;
const AttrModifierType ATTRMODIFIER_BASE = 0;

struct AttrModifier
{
	AttrModifierType Type;
	int Attack;
	int RangedAttack;
	int Defence;
	float	Formation;
	int	Initiatice;
	int	ActionPoint;
	int	Detection;
	int	Covert;
	float Injury;
	float	Conter;
};

typedef int Direction;
const Direction North = 0;
const Direction South = 1;
const Direction West = 2;
const Direction East = 3;

typedef int  Formation;
const Direction Line = 0;
const Direction Circular = 1;
const Direction Loose = 2;

const int StroySquad = 0;
const int MapSquad = 1;