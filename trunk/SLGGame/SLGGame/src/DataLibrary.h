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

	bool setData(std::string path,const int& value,bool createpath=true);
	bool setData(std::string path,const unsigned int& value,bool createpath=true);
	bool setData(std::string path,const float& value,bool createpath=true);
	bool setData(std::string path,const double& value,bool createpath=true);
	bool setData(std::string path,const std::string& value,bool createpath=true);

	bool getData(std::string path,int& value);
	bool getData(std::string path,unsigned int& value);
	bool getData(std::string path,float& value);
	bool getData(std::string path,double& value);
	bool getData(std::string path,std::string& value);

	DataType getDataType(std::string path);
private:
	ticpp::Document mSystemConfig;
	ticpp::Document mGameData;

	ticpp::Element* getNode(std::string path,bool createpath);
	ticpp::Element* findNode(ticpp::Element* parent,std::queue<std::string>* path,bool createpath);
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

		bool ret;
		
		if (type=="I")
		{
			ret=DataLibrary::getSingletonPtr()->setData(path,luaL_checkint(L, 3),(bool)luaL_optint(L,4,1));
		}
		else if(type=="UI")
		{
			ret=DataLibrary::getSingletonPtr()->setData(path,(unsigned int)luaL_checkint(L, 3),(bool)luaL_optint(L,4,1));
		}
		else if(type=="F")
		{
			ret=DataLibrary::getSingletonPtr()->setData(path,(float)luaL_checknumber(L, 3),(bool)luaL_optint(L,4,1));
		}
		else if(type=="D")
		{
			ret=DataLibrary::getSingletonPtr()->setData(path,(double)luaL_checknumber(L, 3),(bool)luaL_optint(L,4,1));
		}
		else if(type=="S")
		{
			ret=DataLibrary::getSingletonPtr()->setData(path,std::string(luaL_checkstring(L, 3)),(bool)luaL_optint(L,4,1));
		}
		
		lua_pushboolean(L,ret);

		return 1;
	}

	static int GetData(lua_State* L)
	{
		std::string path(luaL_checkstring(L, 1));
		std::string type(luaL_checkstring(L, 2));
		
		if (type=="I")
		{
			int value=0;
			DataLibrary::getSingletonPtr()->getData(path,value);
			lua_pushnumber(L,value);
		}
		else if(type=="UI")
		{
			unsigned int value=0;
			DataLibrary::getSingletonPtr()->getData(path,value);
			lua_pushnumber(L,value);
		}
		else if(type=="F")
		{
			float value=0;
			DataLibrary::getSingletonPtr()->getData(path,value);
			lua_pushnumber(L,value);
		}
		else if(type=="D")
		{
			double value=0;
			DataLibrary::getSingletonPtr()->getData(path,value);
			lua_pushnumber(L,value);
		}
		else if(type=="S")
		{
			std::string value="";
			DataLibrary::getSingletonPtr()->getData(path,value);
			lua_pushstring(L,value.c_str());
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