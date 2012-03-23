#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "SquadDefine.h"
#include "BattleSquadManager.h"

static const struct luaL_Reg SkillLib[] =
{
	{NULL,NULL}
};