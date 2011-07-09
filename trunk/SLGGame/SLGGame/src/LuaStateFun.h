#pragma once

#include "StateManager.h"

extern "C"
{

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

	static int AvgState(lua_State* L)
	{
		std::string arg(luaL_checkstring(L, 1));
		
		StateManager::getSingletonPtr()->changeState(arg,StateManager::AVG);

		return 0;
	}

	static int BattleState1(lua_State* L)
	{
		std::string arg(luaL_checkstring(L, 1));

		StateManager::getSingletonPtr()->changeState(arg,StateManager::Battle);

		return 0;
	}

	static int SupplyState(lua_State* L)
	{
		std::string arg(luaL_checkstring(L, 1));

		StateManager::getSingletonPtr()->changeState(arg,StateManager::Supply);

		return 0;
	}

	static const struct luaL_Reg StateLib[] =
	{
		{"AvgState",AvgState},
		{"BattleState",BattleState1},
		{"SupplyState",SupplyState},

		{NULL,NULL}
	};

}