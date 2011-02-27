#pragma once

#define TIXML_USE_TICPP
#include <ticpp.h>
#include <queue>

#include "iisingleton.hpp"

using namespace izayoi;

class DataLibrary:public IISingleton<DataLibrary>
{
public:
	DataLibrary(void);
	~DataLibrary(void);
	
	enum DataBlock
	{
		SystemConfig,
		GameData
	};

	enum DataType
	{
		NoneType,
		IntType,
		UIntType,
		FloatType,
		DubleType,
		StringType
	};

	void loadXmlData(DataBlock type,std::string fileName);
	void saveXmlData(DataBlock type,std::string fileName);

	void setData(std::string path,int value);
	void setData(std::string path,unsigned int value);
	void setData(std::string path,float value);
	void setData(std::string path,double value);
	void setData(std::string path,std::string value);

	int getDataI(std::string path);
	unsigned int getDataUI(std::string path);
	float getDataF(std::string path);
	double getDataD(std::string path);
	std::string getDataS(std::string path);

	DataType getDataType(std::string path);
private:
	ticpp::Document mSystemConfig;
	ticpp::Document mGameData;

	ticpp::Element* getNode(std::string path);
	ticpp::Element* findNode(ticpp::Element* parent,std::queue<std::string>* path);
	void split(const std::string& s, char c,std::queue<std::string>& v);
};

extern "C"
{

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

	static int SetData(lua_State* L)
	{
		std::string path(luaL_checkstring(L, 1));
		std::string type(luaL_checkstring(L, 2));
		
		if (type=="I")
		{
			DataLibrary::getSingletonPtr()->setData(path,luaL_checkint(L, 3));
		}
		else if(type=="UI")
		{
			DataLibrary::getSingletonPtr()->setData(path,(unsigned int)luaL_checkint(L, 3));
		}
		else if(type=="F")
		{
			DataLibrary::getSingletonPtr()->setData(path,(float)luaL_checknumber(L, 3));
		}
		else if(type=="D")
		{
			DataLibrary::getSingletonPtr()->setData(path,(double)luaL_checknumber(L, 3));
		}
		else if(type=="S")
		{
			DataLibrary::getSingletonPtr()->setData(path,std::string(luaL_checkstring(L, 3)));
		}

		return 1;
	}

	static int GetData(lua_State* L)
	{
		std::string path(luaL_checkstring(L, 1));
		std::string type(luaL_checkstring(L, 2));

		if (type=="I")
		{
			lua_pushnumber(L, DataLibrary::getSingletonPtr()->getDataI(path));
		}
		else if(type=="UI")
		{
			lua_pushnumber(L, DataLibrary::getSingletonPtr()->getDataUI(path));
		}
		else if(type=="F")
		{
			lua_pushnumber(L, DataLibrary::getSingletonPtr()->getDataF(path));
		}
		else if(type=="D")
		{
			lua_pushnumber(L, DataLibrary::getSingletonPtr()->getDataD(path));
		}
		else if(type=="S")
		{
			lua_pushstring(L, DataLibrary::getSingletonPtr()->getDataS(path).c_str());
		}

		return 1;
	}

	static const struct luaL_Reg DataLib[] =
	{
		{"SetData",SetData},
		{"GetData",GetData},

		{NULL,NULL}
	};
}