#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include "CameraContral.h"
#include "Terrain.h"
#include "MapDataManager.h"
#include "CutSceneBuilder.h"
#include "CameraCutScene.h"

static int SetCamera(lua_State* L)
{
	int x =  luaL_checknumber(L,1);
	int y =  luaL_checknumber(L,2);
	float xx,yy;
	Terrain::getSingleton().getWorldCoords(x,y,xx,yy);
	CameraContral::getSingleton().moveCameraTo(xx,yy);
	return 0;
}

static int MoveCameraTo(lua_State* L)
{
	int x =  luaL_checknumber(L,1);
	int y =  luaL_checknumber(L,2);

	CutSceneBuilder::getSingletonPtr()->addCutScene(new CameraCutScene(x,y,true));
	
	return 0;
}

static int AddMapTrigger(lua_State* L)
{
	std::string trigertype(luaL_checkstring(L, 1));
	std::string trigerfunc(luaL_checkstring(L, 2));
	std::string filename = LuaSystem::getSingleton().getFileName();
	std::string context = LuaSystem::getSingleton().getContext();
	std::string id = MapDataManager::getSingleton().addTrigger(trigertype,filename,trigerfunc, context);
	lua_pushstring(L,id.c_str());
	return 1;
}

static int RemoveMapTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	MapDataManager::getSingleton().removeTrigger(id);
	return 0;
}

static int ActiveMapTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	MapDataManager::getSingleton().activeTrigger(id);
	return 0;
}

static int DisableMapTrigger(lua_State* L)
{
	std::string id(luaL_checkstring(L, 1));
	MapDataManager::getSingleton().disableTrigger(id);
	return 0;
}

static const struct luaL_Reg MapLib[] =
{
	{"SetCamera",SetCamera},
	{"MoveCameraTo",MoveCameraTo},
	{"AddMapTrigger",AddMapTrigger},
	{"RemoveMapTrigger",RemoveMapTrigger},
	{"ActiveMapTrigger",ActiveMapTrigger},
	{"DisableMapTrigger",DisableMapTrigger},
	{NULL,NULL}
};