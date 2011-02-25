#include "StateManager.h"

#include "MenuState.h"

StateManager::StateManager(void):mBaseState(NULL),mAffixationState(NULL)
{
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
	if (mBaseState!=NULL)//±ØÐëÓÐÖ÷×´Ì¬
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
			break;
		}
	}

	return state;
}
