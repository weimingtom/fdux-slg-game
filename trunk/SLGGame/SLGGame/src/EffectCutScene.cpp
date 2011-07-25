#include "EffectCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "AudioSystem.h"

EffectCutScene::EffectCutScene(unsigned int id,UnitType object,std::string name,std::string sound,unsigned int lasttime):CutScene(lasttime)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	static int n = 0;
	mParticleId = std::string("EFFECT_PU") + Ogre::StringConverter::toString(n++);
	mSquadGraphics->addParticle(mParticleId,name,object);
	mSound = sound;
}

EffectCutScene::~EffectCutScene(void)
{
	mSquadGraphics->stopParticle(mParticleId);
	mSquadGraphics->delParticle(mParticleId);
}

bool EffectCutScene::endCutScene()
{
	return false;
}

void EffectCutScene::skipCutScene()
{
	mSquadGraphics->stopParticle(mParticleId);
}

void EffectCutScene::updateCutScene( unsigned int deltaTime )
{

}

void EffectCutScene::startCutScence()
{
	mSquadGraphics->startParticle(mParticleId);
	if(mSound != "none")
	{
		AudioSystem::getSingleton().playSample(mSound,false);
	}
}
