#include "AnimationCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AudioSystem.h"
#include "Core.h"

AnimationCutScene::AnimationCutScene(std::string id,UnitType object,std::string name,std::string sound , std::string particle,bool isLoop,bool isBackToWait)
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
		int t=mSquadGraphics->getMainWeaponType();

		if(t!=-1)
		{
			if(mSound == "0")
			{
				AudioSystem::getSingleton().playSample(std::string("0-")+Ogre::StringConverter::toString(t),false,true);
			}
			else if(mSound == "1")
			{
				AudioSystem::getSingleton().playSample(std::string("1-")+Ogre::StringConverter::toString(t),false,true);
			}
			else
			{
				AudioSystem::getSingleton().playSample(mSound,false);
			}
		}
	}
}

bool AnimationCutScene::endCutScene()
{
	//std::cout<<mSquadGraphics->mSName<<":"<<mSquadGraphics->isAnimationOver(mObject)<<std::endl;
	if(mSquadGraphics->isAnimationOver(mObject))
	{
		if(mParticle != "none")
		{
			mSquadGraphics->stopParticle(mParticleId);
		}
		//if (mIsBackToWait)
		//{
		//	mSquadGraphics->setInitAnimation(mObject);
		//}
		return true;
	}
	return false;
}

void AnimationCutScene::skipCutScene()
{
	mSquadGraphics->stopTransform();

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

