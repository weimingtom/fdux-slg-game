#pragma once

#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_print.hpp"
#include <queue>
#include <vector>
#include <string>
#include <Ogre.h>

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
		GameData,
		StaticData
	};

	enum DataType
	{
		NoneType,
		IntType,
		UIntType,
		FloatType,
		DubleType,
		StringType,
		Vector3Type
	};

	void loadXmlData(DataBlock type,std::string fileName,bool append, std::string resGroup);
	void saveXmlData(DataBlock type,std::string fileName);

	bool setData(std::string path,const int& value,bool createpath=true);
	bool setData(std::string path,const unsigned int& value,bool createpath=true);
	bool setData(std::string path,const float& value,bool createpath=true);
	bool setData(std::string path,const double& value,bool createpath=true);
	bool setData(std::string path,const std::string& value,bool createpath=true);
	bool setData(std::string path,const Ogre::Vector3& value,bool createpath=true);

	bool getData(std::string path,int& value,bool testExist=false);
	bool getData(std::string path,unsigned int& value,bool testExist=false);
	bool getData(std::string path,float& value,bool testExist=false);
	bool getData(std::string path,double& value,bool testExist=false);
	bool getData(std::string path,std::string& value,bool testExist=false);
	bool getData(std::string path,Ogre::Vector3& value,bool testExist=false);

	bool delNode(std::string path);
	void createPath(std::string path);
	bool copyNode(std::string srcpath, std::string distpath, bool createpath=true);

	std::vector<std::string> getChildList(std::string path);

	DataType getDataType(std::string path);
private:
	rapidxml::xml_document<> mSystemConfig;
	rapidxml::xml_document<> mGameData;
	rapidxml::xml_document<> mStaticData;

	typedef int CreateState;
	static const int	CreateState_None = 0;
	static const int	CreateState_NoCreate = 1;
	static const int	CreateState_Create = 2;

	CreateState mCreateState;

	void copyElement(rapidxml::xml_node<>* srcElement,rapidxml::xml_node<>* destElement);
	void appendXmlDate( rapidxml::xml_document<>* currentDoc,std::string fileName, std::string resGroup);
	rapidxml::xml_node<>* getNode(std::string path,bool createpath);
	rapidxml::xml_node<>* findNode(rapidxml::xml_node<>* parent,std::queue<std::string>* path,bool createpath);
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