#pragma once

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

#include "CommonFunction.h"
#include "CameraContral.h"
#include "Terrain.h"
#include "MapDataManager.h"
#include "CutSceneBuilder.h"
#include "CameraCutScene.h"
#include "Area.h"

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

static int AddMapArea(lua_State* L)
{
	int x =  luaL_checknumber(L,1);
	int y =  luaL_checknumber(L,2);
	Crood crood(x, y);
	std::vector<Crood> croodvec;
	croodvec.push_back(Crood(x, y));
	std::string areaid = MapDataManager::getSingleton().createArea(croodvec);
	lua_pushstring(L,areaid.c_str());
	return 1;
}

static int RemoveMapArea(lua_State* L)
{
	std::string areaid(luaL_checkstring(L, 1));
	MapDataManager::getSingleton().removeArea(areaid);
	return 0;
}

static int LuaGetDirection(lua_State* L)
{
	int x1 =  luaL_checknumber(L,1);
	int y1 =  luaL_checknumber(L,2);
	int x2 =  luaL_checknumber(L,3);
	int y2 =  luaL_checknumber(L,4);
	int dir = GetDirection(x1, y1, x2, y2);
	lua_pushnumber(L, dir);
	return 1;
}

static int GetGroundAttr(lua_State* L)
{
	int x =  luaL_checknumber(L,1);
	int y =  luaL_checknumber(L,2);
	int attrtype = luaL_checknumber(L,3);
	float attr = 0.0f;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	switch(attrtype)
	{
	case 0:
		attr = mapdata->getDefModify(x, y, -1);
		break;
	case 1:
		attr = mapdata->getCovert(x, y, -1);
		break;
	case 2:
		attr = mapdata->getInfApCost(x, y, -1);
		break;
	case 3:
		attr = mapdata->getCavApCost(x, y, -1);
		break;
	}
	lua_pushnumber(L, attr);
	return 1;
}

static int LuaGetDistance(lua_State* L)
{
	int x1 =  luaL_checknumber(L,1);
	int y1 =  luaL_checknumber(L,2);
	int x2 =  luaL_checknumber(L,3);
	int y2 =  luaL_checknumber(L,4);
	int dir = GetDistance(x1, y1, x2, y2);
	lua_pushnumber(L, dir);
	return 1;
}

static const struct luaL_Reg MapLib[] =
{
	{"SetCamera",SetCamera},
	{"MoveCameraTo",MoveCameraTo},
	{"AddMapTrigger",AddMapTrigger},
	{"RemoveMapTrigger",RemoveMapTrigger},
	{"ActiveMapTrigger",ActiveMapTrigger},
	{"DisableMapTrigger",DisableMapTrigger},
	{"AddMapArea", AddMapArea},
	{"RemoveMapArea", RemoveMapArea},
	{"GetDirection",LuaGetDirection},
	{"GetGroundAttr",GetGroundAttr},
	{"GetDistance",LuaGetDistance},
	{NULL,NULL}
};