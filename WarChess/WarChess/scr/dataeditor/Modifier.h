#pragma once

#include <vector>

enum BasicAttr
{
	ATTR_ATTACK = 0, //近战攻击值
	ATTR_RANGEDATTACK =1, //远程攻击值
	ATTR_DEFENSE = 2, //防御值
	ATTR_FORMATION = 3, //阵列值
	ATTR_INITIATIVE = 4, //先攻值
	ATTR_ACTIONPOINT = 5, //行动值
	ATTR_DETECTION = 6, //侦查值
	ATTR_COVERT = 7,  //隐蔽值
	ATTR_INJURY = 8,  //伤者能力系数
	ATTR_COUNTER = 9,	//反击系数
	ATTR_MAX = 10
};

typedef std::vector<int> AttrVector[ATTR_MAX];

enum ModifyType
{
	MODIFIER_BASIC = 0, //基础修正，直接叠加
	MODIFIER_RESISTANCE = 1, //抵抗修正，用于消除减值，最高修正量不会超过减值本身
};

struct AttrModifier
{
	AttrVector attr;
	ModifyType type;
};
