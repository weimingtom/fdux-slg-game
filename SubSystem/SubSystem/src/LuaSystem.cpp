#include "LuaSystem.h"

#include <Ogre.h>

#include "LuaFun.cpp"

#ifndef SCRIPT_EDITOR
#include "DataLibrary.h"
#endif

extern "C"
{

	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>

}

LuaSystem::LuaSystem(void)
{
	L=lua_open();
	luaL_openlibs(L);
	LuaBreakupFun=NULL;
	mListener=NULL;
	mContextStack.push_back("\0");
	luaL_register(L, "GUI",GUILib);
}

LuaSystem::~LuaSystem(void)
{
	lua_close(L);
}

std::string LuaSystem::luaCallString(const std::string Szcode)
{
	luaL_loadstring(L,Szcode.c_str());
	int error=lua_pcall(L, 0 , 0, 0);
	if (error)
	{
		const char* error = lua_tostring(L, -1);//打印错误结果
		lua_pop(L, 1);
		return std::string(error);
	}
	return std::string();
}


void LuaSystem::runScript( const std::string script )
{
	mScriptBuffer.clear();
	LuaBreakupFun=NULL;

	std::stringstream ss(script);
	std::string sub_str;

	while(std::getline(ss,sub_str,';'))//以分号切分语句
	{
		mScriptBuffer.push_back(sub_str);
	}
}

void LuaSystem::onFrameUpdate()
{
	if (!mScriptBuffer.empty())
	{

		if (LuaBreakupFun==NULL)
		{
			std::string lua=(*mScriptBuffer.begin());
			mScriptBuffer.erase(mScriptBuffer.begin());
			
			std::string ret=luaCallString(lua);
			if (ret!="")//如果发生错误
			{
				if (mListener!=NULL)
				{
					mScriptBuffer.clear();
					LuaBreakupFun=NULL;
					mListener->onError(ret);
				}

				return;
			}

			if (mScriptBuffer.empty())//如果是最后一条语句
			{
				if (mListener!=NULL)
				{
					LuaBreakupFun=NULL;
					mListener->onComplete();
				}
			}
			else
			{
				mScriptLine++;
			}
		}
		else//当被阻塞时
		{
			LuaBreakupFun();
		}
	}
}

void LuaSystem::registerListener( LuaSystemListener* listener )
{
	mListener=listener;
}

void LuaSystem::registerCLib( const std::string libName,const luaL_Reg* lib )
{
	luaL_register(L, libName.c_str(),lib);
}

void LuaSystem::runScriptFromFile( const std::string& filename,int lineNum)
{
	mScriptBuffer.clear();
	mScriptName=filename;
	mScriptLine=lineNum;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename, "Script", true);

	runScript(stream->getAsString());

	//跳过指定数量的行
	
	if (lineNum!=0)
	{
		for (int i=0;i<lineNum;i++ )
		{
			mScriptBuffer.erase(mScriptBuffer.begin());
		}
	}
}


std::string LuaSystem::getContext()
{
	return mContextStack.back();
}

std::string LuaSystem::getFileName()
{
	return mFileNameStack.back();
}

LuaTempContext*	LuaSystem::getTempContext()
{
	return mTempContextStack.back();
}

bool LuaSystem::executeFunction(std::string filename, std::string funcname, std::string context, LuaTempContext *tempcontext)
{
	if(context == "\0")
		return false;

	Ogre::String logstr("filename:");
	logstr.append(filename);
	logstr.append(" funcname:");
	logstr.append(funcname);
	logstr.append(" context:");
	logstr.append(context);
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String("LUASYSLOG START ") + logstr);

	mContextStack.push_back(context);
	mFileNameStack.push_back(filename);
	mTempContextStack.push_back(tempcontext);
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename, "Script", true);
	int result;
	result = luaL_loadstring(L,stream->getAsString().c_str());
	if(!result)
	{
		result = lua_pcall(L,0 ,0, 0);
		if(!result)
		{
			lua_getglobal(L, funcname.c_str());
			result = lua_pcall(L,0 ,0, 0);
			if(result)
			{
				const char* erro;
				erro = lua_tostring(L,-1);
				Ogre::LogManager::getSingletonPtr()->logMessage(erro,Ogre::LML_CRITICAL);
			}
		}
		else
		{
			const char* erro;
			erro = lua_tostring(L,-1);
			Ogre::LogManager::getSingletonPtr()->logMessage(erro,Ogre::LML_CRITICAL);
		}
	}
	else
	{
		const char* erro;
		erro = lua_tostring(L,-1);
		Ogre::LogManager::getSingletonPtr()->logMessage(erro,Ogre::LML_CRITICAL);
	}
	mTempContextStack.pop_back();
	mFileNameStack.pop_back();
	mContextStack.pop_back();

	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::String("LUASYSLOG END ") + logstr);

	return !result;
}

void LuaSystem::saveScriptRuntime()
{
#ifndef SCRIPT_EDITOR
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/ScriptName",mScriptName);
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/ScriptLine",mScriptLine);
	
#endif
}

void LuaSystem::loadScripRuntime()
{
#ifndef SCRIPT_EDITOR
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/ScriptName",mScriptName);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/ScriptLine",mScriptLine);
	runScriptFromFile(mScriptName,mScriptLine);
	LuaBreakupFun=NULL;
	
#endif
}

void LuaSystem::clearLuaSystem()
{
	LuaBreakupFun=NULL;
	mContextStack.clear();
	mFileNameStack.clear();
	mScriptBuffer.clear();
}

void LuaSystem::clearAvgState()
{
	LuaBreakupFun=NULL;
	mScriptBuffer.clear();
}