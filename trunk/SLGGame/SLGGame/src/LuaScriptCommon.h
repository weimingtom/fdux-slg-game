#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "LuaSystem.h"
#include "DataLibrary.h"
#include "AudioSystem.h"

static int SetInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	int val = luaL_checknumber(L, 2);
	std::string contextpath = LuaSystem::getSingleton().getContext();
	DataLibrary::getSingleton().setData(contextpath + std::string("/")+ id, val);
	return 0;
}

static int GetInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	int val;
	DataLibrary::getSingleton().getData(contextpath + std::string("/")+ id, val);
	lua_pushnumber(L,val);
	return 1;
}

static int GetString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	std::string val;
	DataLibrary::getSingleton().getData(contextpath + std::string("/")+ id, val);
	lua_pushstring(L,val.c_str());
	return 1;
}

static int SetString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string val(luaL_checkstring(L, 2));
	std::string contextpath = LuaSystem::getSingleton().getContext();
	DataLibrary::getSingleton().setData(contextpath + std::string("/")+ id, val);
	return 0;
}

static int GetTempInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	int val = 0;
	LuaTempContext* tempcontext = LuaSystem::getSingleton().getTempContext();
	if(tempcontext)
	{
		std::map<std::string, int>::iterator ite = tempcontext->intMap.find(id);
		if(ite != tempcontext->intMap.end())
			val = ite->second;
	}
	lua_pushnumber(L,val);
	return 1;
}

static int SetTempInt(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	int val = luaL_checkinteger(L, 2);
	LuaTempContext* tempcontext = LuaSystem::getSingleton().getTempContext();
	if(tempcontext)
	{
		tempcontext->intMap[id] = val;
	}
	return 0;
}


static int GetTempString(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	std::string val;
	LuaTempContext* tempcontext = LuaSystem::getSingleton().getTempContext();
	if(tempcontext)
	{
		std::map<std::string, std::string>::iterator ite = tempcontext->strMap.find(id);
		if(ite != tempcontext->strMap.end())
			val = ite->second;
	}
	lua_pushstring(L,val.c_str());
	return 1;
}

static int PlayMusic(lua_State* L)
{
	std::string music(luaL_checkstring(L, 1));
	DataLibrary::getSingleton().setData("GameData/StoryData/MusicName", music);
	AudioSystem::getSingleton().playStream(music,true,2000);
	return 0;
}

static int GetRand(lua_State* L)
{
	int min = luaL_checknumber(L,1);
	int max = luaL_checknumber(L,2);
	int re = min + (rand() % (max- min));
	lua_pushnumber(L,re);
	return 1;
}

static const struct luaL_Reg ScriptCommonLib[] =
{
	{"SetInt", SetInt},
	{"GetInt", GetInt},
	{"GetString", GetString},
	{"SetString", SetString},
	{"GetTempInt", GetTempInt},
	{"SetTempInt", SetTempInt},
	{"GetTempString", GetTempString},
	{"PlayMusic", PlayMusic},
	{"GetRand", GetRand},
	{NULL,NULL}
};