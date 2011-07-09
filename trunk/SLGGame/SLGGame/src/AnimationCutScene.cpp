#include "AnimationCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

AnimationCutScene::AnimationCutScene(unsigned int id,UnitType object,std::string name,std::string sound , std::string particle,bool isLoop,bool isBackToWait)
:CutScene(0),mName(name),mSound(sound),mParticle(particle),mIsBackeToWait(isBackToWait)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mIsLoop = isLoop;
	mObject=object;
}

AnimationCutScene::~AnimationCutScene(void)
{

}

void AnimationCutScene::startCutScence()
{
	mSquadGraphics->setAnimation(mName,mObject,mIsLoop,mIsBackeToWait);
}

bool AnimationCutScene::endCutScene()
{
	if(mSquadGraphics->isAnimationOver(mObject))
	{
		if (mIsBackeToWait)
		{
			mSquadGraphics->setInitAnimation(mObject);
		}
		return true;
	}
	return false;
}

void AnimationCutScene::skipCutScene()
{
	if (mIsBackeToWait)
	{
		mSquadGraphics->setInitAnimation(mObject);
	}
}

void AnimationCutScene::updateCutScene( unsigned int deltaTime )
{

}
