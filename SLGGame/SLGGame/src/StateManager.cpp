#include "StateManager.h"

#include "AVGState.h"
#include "MenuState.h"

#include "LuaSystem.h"
#include "LuaStateFun.h"

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

void StateManager::StateUpdate()
{
	if(mAffixationState!=NULL)
	{
		mAffixationState->update();
	}
	else
	{
		mBaseState->update();
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
	}

	return state;
}
