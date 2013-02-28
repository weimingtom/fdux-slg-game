#pragma once

enum EquipmentType
{
	EQUIP_SOILDER = 0,
	EQUIP_HORSE = 1,
	EQUIP_ARMOR = 2,
	EQUIP_SHIELD = 3,
	EQUIP_PWEAPON = 4,
	EQUIP_SWEAPON = 5,
	EQUIP_RETAINER = 6
};

enum PweaponType
{
	EQUIP_PWEAPON_ONEHANDSWORD = 0,
	EQUIP_PWEAPON_ONEHANDBLUNT = 1,
	EQUIP_PWEAPON_TWOHANDSWORD = 2,
	EQUIP_PWEAPON_TWOHANDBLUNT = 3,
	EQUIP_PWEAPON_SHORTSPEAR = 4,
	EQUIP_PWEAPON_LONG = 5,
	EQUIP_PWEAPON_STAVES = 6
};

enum SweaponType
{
	EQUIP_SWEAPON_BOW = 0,
	EQUIP_SWEAPON_XBOW = 1
};

enum ArmorType
{
	EQUIP_ARMOR_LIGHT = 0,
	EQUIP_ARMOR_MIDDLE = 1,
	EQUIP_ARMOR_HEAVY = 2
};

enum HorseType
{
	EQUIP_HORSE_LIGHT = 0,
	EQUIP_HORSE_HEAVY = 1
};

enum AttrModifierType
{
	ATTRMODIFIER_BASE = 0,
	ATTRMODIFIER_MAGIC = 1,
	ATTRMODIFIER_COMMAND = 2,
	ATTRMODIFIER_RESISTANCE = 3
};

enum AttrType
{
	ATTR_ATTACK = 0,
	ATTR_RANGEDATTACK = 1,
	ATTR_DEFENCE = 2,
	ATTR_FORM = 3,
	ATTR_INITIATIVE = 4,
	ATTR_ACTIONPOINT = 5,
	ATTR_DETECTION = 6,
	ATTR_COVERT = 7,
	ATTR_TOUGHNESS = 8,
	ATTR_CONTER = 9,
	ATTR_RANGEDDEFENCE = 10
};


struct AttrModifier
{
	int Type;
	float	Attack;
	float	RangedAttack;
	float	Defence;
	float	Form;
	float	Initiative;
	float	ActionPoint;
	float	Detection;
	float	Covert;
	float	Toughness;
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
		Toughness = 0.0f;
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

enum  Formation
{
	Line = 0,
	Circular = 1,
	Loose = 2
};

enum AttrCalcType
{
	ATTRCALC_FULL = 0,
	ATTRCALC_ONLYBASE = 1,
	ATTRCALC_ONLYBONUS = 2,
	ATTRCALC_RESISTLEFT = 3
};


const float FORMBONSE_LINE_FRONT = 1.0f;
const float FORMBONSE_LINE_SIDE = 0.6f;
const float FORMBONSE_LINE_BACK = 0.0f;
const float FORMBONSE_LINE_RANGED = 0.8f;
const float FORMBONSE_CIRC_FRONT = 0.8f;
const float FORMBONSE_CIRC_SIDE = 0.8f;
const float FORMBONSE_CIRC_BACK = 0.8f;
const float FORMBONSE_CIRC_RANGED = 1.6f;
const float FORMBONSE_LOOS_FRONT = 0.0f;
const float FORMBONSE_LOOS_SIDE = 0.0f;
const float FORMBONSE_LOOS_BACK = 0.0f;
const float FORMBONSE_LOOS_RANGED = 0.0f;

const float RANGEDDEFENCEBONUS = 4.0f;

const int MOVEEVENT_WRONG = 1;
const int MOVEEVENT_CHARGE = 2;
const int MOVEEVENT_SPOT = 4;
const int MOVEEVENT_AMBUSH = 8;
const int MOVEEVENT_MAPEVENT = 16;
const int MOVEEVENT_CHARGE_DIR_1 = 32; //冲锋方向位1
const int MOVEEVENT_CHARGE_DIR_2 = 64; //冲锋方向位2
const int MOVEEVENT_SPOTBYPLAYER = 128;

#define SetChargeDir(d) (d << 6)
#define GetChargeDir(f) ((f >> 6) && 0x03)

enum SkillType
{
	SKILLTYPE_PASSIVE = 0,
	SKILLTYPE_ACTIVE = 1,
	SKILLTYPE_EQUIP = 2
};


enum SkillTargetType
{
	SKILLTARGETTYPE_TARGETSQUAD = 0,
	SKILLTARGETTYPE_TARGETAREA = 1,
	SKILLTARGETTYPE_TARGETLINE = 2,
	SKILLTARGETTYPE_RANGED = 3,
	SKILLTARGETTYPE_MELEE = 4
};

enum SkillApType
{
	SKILLAPTYPE_SETUP = 0,
	SKILLAPTYPE_BATTLE = 1,
	SKILLAPTYPE_DEFENCE = 2
};

enum EffectType
{
	EFFECTTYPE_NORMAL = 0,
	EFFECTTYPE_INDEPENDENT = 1,
	EFFECTTYPE_UNIQUE = 2
};

enum SquadType2
{
	SQUAD_NORMAL = 0,
	SQUAD_SPECIAL
};

enum SquadType
{
	SQUADTYPE_INFANTRY = 0,
	SQUADTYPE_MISSILEINFANTRY = 1,
	SQUADTYPE_CAVALRY = 2,
	SQUADTYPE_MISSILECAVALRY = 3,
	SQUADTYPE_SAINT = 4,
	SQUADTYPE_BATTLEMAGE = 5,
	SQUADTYPE_ARCANEMAGE = 6
};

enum UnitType
{
	UNITTYPE_LEADER = 1,
	UNITTYPE_SOLIDER = 2,
	UNITTYPE_ALL = 3
};

enum SquadIconType
{
	SQUADTYPE_LightInf = 0,
	SQUADTYPE_HeavyInf = 1,
	SQUADTYPE_Bowman = 2,
	SQUADTYPE_Saint = 3
};

struct AttackInfo
{
	int AtkTime;
	float Atk;
	int Randomness;
	AttackInfo()
	{
		AtkTime = 0;
		Atk = 0.0f;
		Randomness = 0;
	}
};

enum RoleType
{
	ROLETYPE_MAINFORCE = 0x0001,
	ROLETYPE_SUPPORT_RANGE = 0x0002,
	ROLETYPE_SUPPORT_CLOSE = 0x0004,
	ROLETYPE_ANTI_HIGHFORM = 0x0008,
	ROLETYPE_ANTI_HIGHARMOR = 0x0010,
	ROLETYPE_ANTI_CAV = 0x0020,
	ROLETYPE_ANTI_MAGE = 0x0040,
	ROLETYPE_SUPPORT_WOUND = 0x0080,
	ROLETYPE_SUPPORT_WAVER = 0x0100,
	ROLETYPE_SUPPORT_DEF = 0x0200,
	ROLETYPE_SUPPORT_AP = 0x0400
};