#include "AnimationCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AudioSystem.h"
#include "Core.h"

AnimationCutScene::AnimationCutScene(unsigned int id,UnitType object,std::string name,std::string sound , std::string particle,bool isLoop,bool isBackToWait)
:CutScene(0),mName(name),mSound(sound),mParticle(particle),mIsBackToWait(isBackToWait)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mIsLoop = isLoop;
	mObject=object;
	if(mParticle != "none")
	{
		static int n = 0;
		mParticleId = std::string("Anim_PU") + Ogre::StringConverter::toString(n++);
		mSquadGraphics->addParticle(mParticleId,mParticle,mObject);
	}
}

AnimationCutScene::~AnimationCutScene(void)
{
	if(mParticle != "none")
	{
		mSquadGraphics->delParticle(mParticleId);
	}
}

void AnimationCutScene::startCutScence()
{
	mSquadGraphics->setAnimation(mName,mObject,mIsLoop,mIsBackToWait);
	if(mParticle != "none")
	{
		mSquadGraphics->startParticle(mParticleId);
	}
	if(mSound != "none")
	{
		AudioSystem::getSingleton().playSample(mSound,false);
	}
}

bool AnimationCutScene::endCutScene()
{
	if(mSquadGraphics->isAnimationOver(mObject))
	{
		if(mParticle != "none")
		{
			mSquadGraphics->stopParticle(mParticleId);
		}
		if (mIsBackToWait)
		{
			mSquadGraphics->setInitAnimation(mObject);
		}
		return true;
	}
	return false;
}

void AnimationCutScene::skipCutScene()
{
	if(mParticle != "none")
	{
		mSquadGraphics->stopParticle(mParticleId);
	}
	if (mIsBackToWait)
	{
		mSquadGraphics->setInitAnimation(mObject);
	}
}

void AnimationCutScene::updateCutScene( unsigned int deltaTime )
{

}

