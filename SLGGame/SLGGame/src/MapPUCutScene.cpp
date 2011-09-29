#include "MapPUCutScene.h"

#include "AudioSystem.h"

MapPUCutScene::MapPUCutScene(Ogre::Vector3 pos, float estime, std::string name, std::string sound)
:mEsTime(estime),mSound(sound)
{
	mNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mParticle  = Core::getSingleton().createPUSystem(mNode->getName()+ std::string("_PU"), name);
	mNode->attachObject(mParticle);
	mNode->setPosition(pos);
	mParticle->prepare();
}
MapPUCutScene::~MapPUCutScene(void)
{
	mNode->detachObject(mParticle);
	Core::getSingleton().destroyPUSystem(mParticle);
	Core::getSingleton().mSceneMgr->destroySceneNode(mNode);
}

void MapPUCutScene::startCutScence()
{
	mParticle->startAndStopFade(mEsTime);
	AudioSystem::getSingleton().playSample(mSound,false);
}
bool MapPUCutScene::endCutScene()
{
	return mParticle->getState() == ParticleUniverse::ParticleSystem::PSS_STOPPED;
}
void MapPUCutScene::skipCutScene()
{
	mParticle->stop();
	Core::getSingleton().destroyPUSystem(mParticle);
}
void MapPUCutScene::updateCutScene(unsigned int deltaTime)
{

}