#include "StateManager.h"

StateManager::StateManager(void):mBaseState(nullptr),mAffixationState(nullptr)
{
}

StateManager::~StateManager(void)
{
}

void StateManager::changeState( std::string arg,StateType type )
{
	if (mAffixationState==NULL)//必须没有附加状态
	{
		if (mBaseState!=NULL)
		{
			mBaseState->uninitialize();
			delete mBaseState;
		}
		
		mBaseState=CreateState(type);

		mBaseState->initialize(arg);
	}
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
			break;
		}
	case AVG:
		{
			break;
		}
	}

	return state;
}
