#include "StateManager.h"

#include "AVGState.h"
#include "MenuState.h"
#include "BattleState.h"

#include "LuaSystem.h"
#include "LuaStateFun.h"
#include "DataLibrary.h"

StateManager::StateManager(void):mBaseState(NULL),mAffixationState(NULL)
{
	//注册lua函数
	LuaSystem::getSingletonPtr()->registerCLib("StateLib",StateLib);
}

StateManager::~StateManager(void)
{
}

void StateManager::changeState( std::string arg,StateType type )
{
	if (mAffixationState!=NULL)
	{
		removeAffixationState();
	}

	if (mBaseState!=NULL)
	{
		mBaseState->uninitialize();
		delete mBaseState;
	}

	mBaseState=CreateState(type);

	mBaseState->initialize(arg);
}

void StateManager::addAffixationState( std::string arg,StateType type )
{
	if (mBaseState!=NULL)//必须有主状态
	{
		if (mAffixationState!=NULL)
		{
			removeAffixationState();
		}

		mAffixationState=CreateState(type);

		mAffixationState->initialize(arg);
	}
}

void StateManager::removeAffixationState()
{
	if (mAffixationState!=NULL)
	{
		mAffixationState->uninitialize();
		delete mAffixationState;
		mAffixationState=NULL;
	}
}

bool StateManager::hasAffixationState()
{
	return mAffixationState!=NULL;
}

void StateManager::StateUpdate(unsigned int deltaTime)
{
	if(mAffixationState!=NULL)
	{
		mAffixationState->update(deltaTime);
	}
	else
	{
		mBaseState->update(deltaTime);
	}
}

GameState* StateManager::CreateState( StateType type )
{
	GameState* state=NULL;

	switch(type)
	{
	case Menu:
		{	
			state=new MenuState();
			break;
		}
	case AVG:
		{
			state=new AVGState();
			break;
		}
	case Battle:
		{
			state = new BattleState();
			break;
		}
	}

	return state;
}

void StateManager::saveState( std::string file )
{
	DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::GameData,file);
}

void StateManager::loadState( std::string file )
{
	DataLibrary::getSingleton().delNode(std::string("GameData/StoryData"));
	if(mBaseState)
	{
		mBaseState->uninitialize();
		delete mBaseState;
		mBaseState = NULL;
	}
	DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,file,false);
	std::string state;
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/GameState",state);
	if (state=="AVG")
	{
		LuaSystem::getSingletonPtr()->clearLuaSystem();
		changeState("save.xml",AVG);
	}
	else if (state=="Battle")
	{
		LuaSystem::getSingletonPtr()->clearLuaSystem();
		changeState("save.xml",Battle);
	}
}
