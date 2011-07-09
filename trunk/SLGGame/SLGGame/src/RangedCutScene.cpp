#include "RangedCutScene.h"

RangedCutScene::RangedCutScene(Ogre::Vector3 startpos, Ogre::Vector3 endpoint, int type, std::string resname)
:mStartpoint(startpos),mEndpoint(endpoint)
{
	mNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->setPosition(startpos);
	mParticle = NULL;
	mEntity= NULL;
	if(resname == "none")
		return;
	switch(type)
	{
	case 0:
		break;
	case 1:
		break;
	}
}
RangedCutScene::~RangedCutScene()
{

}

void RangedCutScene::startCutScence()
{

}

bool RangedCutScene::endCutScene()
{
	if(mNode->getPosition().distance(mEndpoint) < 0.1f)
	{
		clear();
		return true;
	}
	return false;
}

void RangedCutScene::skipCutScene()
{
	clear();
}

void RangedCutScene::updateCutScene(unsigned int deltaTime)
{

}

void RangedCutScene::clear()
{
	mNode->detachAllObjects();
	if(mParticle != NULL )
	{
		mParticle->stop();
		Core::getSingleton().destroyPUSystem(mParticle);
		mParticle = NULL;
	}
	if(mEntity != NULL)
	{
		Core::getSingleton().mSceneMgr->destroyEntity(mEntity);
		mEntity = NULL;
	}
	Core::getSingleton().mSceneMgr->destroySceneNode(mNode);
	mNode =NULL;
}