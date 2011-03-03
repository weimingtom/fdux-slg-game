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

		return 1;
	}

	static int BattleState(lua_State* L)
	{
		std::string arg(luaL_checkstring(L, 1));

		StateManager::getSingletonPtr()->changeState(arg,StateManager::Battle);

		return 1;
	}

	static int SupplyState(lua_State* L)
	{
		std::string arg(luaL_checkstring(L, 1));

		StateManager::getSingletonPtr()->changeState(arg,StateManager::Supply);

		return 1;
	}

	static const struct luaL_Reg StateLib[] =
	{
		{"AvgState",AvgState},
		{"BattleState",BattleState},
		{"SupplyState",SupplyState},

		{NULL,NULL}
	};

}