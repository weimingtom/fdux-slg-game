#include "AnimationCutScenece.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

AnimationCutScenece::AnimationCutScenece(unsigned int id,AnimationObject object,std::string name,bool isLoop,bool isBackToWait):CutScence(0),mIsBackeToWait(isBackToWait)
{
	
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	
	mSquadGraphics->setAnimation(name,(SquadGraphics::Object)object,isLoop);
	mObject=object;
}

AnimationCutScenece::~AnimationCutScenece(void)
{
	if (mIsBackeToWait)
	{
		mSquadGraphics->setInitAnimation((SquadGraphics::Object)mObject);
	}
}

bool AnimationCutScenece::endCutScence()
{
	return mSquadGraphics->isAnimationOver((SquadGraphics::Object)mObject);
}

void AnimationCutScenece::skipCutScence()
{
	if (mIsBackeToWait)
	{
		mSquadGraphics->setInitAnimation((SquadGraphics::Object)mObject);
	}
}

void AnimationCutScenece::updateCutScence( unsigned int deltaTime )
{

}
