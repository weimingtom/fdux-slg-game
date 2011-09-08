#pragma once

typedef int EquipmentType;
const EquipmentType EQUIP_SOILDER = 0;
const EquipmentType EQUIP_HORSE = 1;
const EquipmentType EQUIP_ARMOR = 2;
const EquipmentType EQUIP_SHIELD = 3;
const EquipmentType EQUIP_PWEAPON = 4;
const EquipmentType EQUIP_SWEAPON = 5;

typedef int PweaponType;
const PweaponType EQUIP_PWEAPON_ONEHANDSWORD = 1;
const PweaponType EQUIP_PWEAPON_LONG = 5;

typedef int SweaponType;
const PweaponType EQUIP_SWEAPON_BOW = 0;
const PweaponType EQUIP_SWEAPON_XBOW = 1;

typedef int ArmorType;
const ArmorType EQUIP_ARMOR_LIGHT = 0;
const ArmorType EQUIP_ARMOR_HEAVY = 1;

typedef int AttrModifierType;
const AttrModifierType ATTRMODIFIER_BASE = 0;
const AttrModifierType ATTRMODIFIER_MAGIC = 1;
const AttrModifierType ATTRMODIFIER_COMMAND = 2;
const AttrModifierType ATTRMODIFIER_RESISTANCE = 3;

typedef int AttrType;
const AttrType ATTR_ATTACK = 0;
const AttrType ATTR_RANGEDATTACK = 1;
const AttrType ATTR_DEFENCE = 2;
const AttrType ATTR_FORM = 3;
const AttrType ATTR_INITIATIVE = 4;
const AttrType ATTR_ACTIONPOINT = 5;
const AttrType ATTR_DETECTION = 6;
const AttrType ATTR_COVERT = 7;
const AttrType ATTR_INJURY = 8;
const AttrType ATTR_CONTER = 9;
const AttrType ATTR_RANGEDDEFENCE = 10;


struct AttrModifier
{
	AttrModifierType Type;
	float	Attack;
	float	RangedAttack;
	float	Defence;
	float	Form;
	float	Initiative;
	float	ActionPoint;
	float	Detection;
	float	Covert;
	float	Injury;
	float	Conter;
	AttrModifier()
	{
		Type = ATTRMODIFIER_BASE;
		Attack = 0.0f;
		RangedAttack = 0.0f;
		Defence = 0.0f;
		Form = 0.0f;
		Initiative = 0.0f;
		ActionPoint = 0.0f;
		Detection = 0.0f;
		Covert = 0.0f;
		Injury = 0.0f;
		Conter = 0.0f;
	}
};

typedef int Direction;
const Direction North = 0;
const Direction South = 1;
const Direction West = 2;
const Direction East = 3;
const Direction NorthEast=4;
const Direction EastSouth=5;
const Direction SouthWest=6;
const Direction WestNorth=7;

typedef int  Formation;
const Formation Line = 0;
const Formation Circular = 1;
const Formation Loose = 2;

const int StroySquad = 0;
const int MapSquad = 1;

typedef int AttrCalcType;
const AttrCalcType ATTRCALC_FULL = 0;
const AttrCalcType ATTRCALC_ONLYBASE = 1;
const AttrCalcType ATTRCALC_ONLYBONUS = 2;
const AttrCalcType ATTRCALC_RESISTLEFT = 3;

const float FORMBONSE_LINE_FRONT = 1.0f;
const float FORMBONSE_LINE_SIDE = 0.4f;
const float FORMBONSE_LINE_BACK = 0.0f;
const float FORMBONSE_LINE_RANGED = 1.0f;
const float FORMBONSE_CIRC_FRONT = 0.6f;
const float FORMBONSE_CIRC_SIDE = 0.6f;
const float FORMBONSE_CIRC_BACK = 0.6f;
const float FORMBONSE_CIRC_RANGED = 2.0f;
const float FORMBONSE_LOOS_FRONT = 0.0f;
const float FORMBONSE_LOOS_SIDE = 0.0f;
const float FORMBONSE_LOOS_BACK = 0.0f;
const float FORMBONSE_LOOS_RANGED = 0.0f;

const float RANGEDDEFENCEBONUS = 10.0f;

typedef int SquadType;
const SquadType SQUAD_NORMAL = 0;
const SquadType SQUAD_SPECIAL = 1;

const int MOVEEVENT_WRONG = 1;
const int MOVEEVENT_CHARGE = 2;
const int MOVEEVENT_SPOT = 4;
const int MOVEEVENT_AMBUSH = 8;
const int MOVEEVENT_MAPEVENT = 16;
const int MOVEEVENT_CHARGE_DIR_1 = 32; //冲锋方向位1
const int MOVEEVENT_CHARGE_DIR_2 = 64; //冲锋方向位2
const int MOVEEVENT_SPOTBYPLAYER = 128;

typedef int SkillType;
const SkillType SKILLTYPE_PASSIVE = 0;
const SkillType SKILLTYPE_TARGETSELF = 1;
const SkillType SKILLTYPE_TARGETENEMY = 2;
const SkillType SKILLTYPE_TARGETFRIEND = 3;
const SkillType SKILLTYPE_TARGETALL = 4;
const SkillType SKILLTYPE_TARGETAREA = 5;
const SkillType SKILLTYPE_TARGETLINE = 6;
const SkillType SKILLTYPE_RANGED = 7;

const int SKILLAPTYPE_SETUP = 0;
const int SKILLAPTYPE_BATTLE = 1;
const int SKILLAPTYPE_DEFENCE = 2;

const int ATKROLL = 20;
const int DEFBOUSE = 15;


typedef int UnitType;
const UnitType UNITTYPE_ALL = 3;
const UnitType UNITTYPE_LEADER = 1;
const UnitType UNITTYPE_SOLIDER = 2;

typedef int SquadType;
const SquadType SQUADTYPE_LightInf=0;
const SquadType SQUADTYPE_HeavyInf=1;
const SquadType SQUADTYPE_Bowman=2;
const SquadType SQUADTYPE_Saint=3;

struct AttackInfo
{
	int AtkTime;
	float Atk;
	int Fluctuate;
	AttackInfo()
	{
		AtkTime = 0;
		Atk = 0.0f;
		Fluctuate = 0;
	}
};

const int DEADTOMORALE[10] = {0,2,6,12,20,30,42,50,50,50}; 