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