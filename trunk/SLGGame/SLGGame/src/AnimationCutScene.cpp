#include "AnimationCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

AnimationCutScene::AnimationCutScene(unsigned int id,AnimationObject object,std::string name,bool isLoop,bool isBackToWait):CutScene(0),mIsBackeToWait(isBackToWait)
{
	
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	
	mSquadGraphics->setAnimation(name,(SquadGraphics::Object)object,isLoop);
	mObject=object;
}

AnimationCutScene::~AnimationCutScene(void)
{
	if (mIsBackeToWait)
	{
		mSquadGraphics->setInitAnimation((SquadGraphics::Object)mObject);
	}
}

bool AnimationCutScene::endCutScene()
{
	return mSquadGraphics->isAnimationOver((SquadGraphics::Object)mObject);
}

void AnimationCutScene::skipCutScene()
{
	if (mIsBackeToWait)
	{
		mSquadGraphics->setInitAnimation((SquadGraphics::Object)mObject);
	}
}

void AnimationCutScene::updateCutScene( unsigned int deltaTime )
{

}
