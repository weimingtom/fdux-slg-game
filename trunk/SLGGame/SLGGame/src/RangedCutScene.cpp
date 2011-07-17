#include "RangedCutScene.h"

RangedCutScene::RangedCutScene(Ogre::Vector3 startpos, Ogre::Vector3 endpoint, int type, std::string resname)
:mStartpoint(startpos),mEndpoint(endpoint)
{
	mNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->setVisible(false);
	mNode->setDirection(startpos - endpoint);
	mNode->setPosition(startpos);
	mParticle = NULL;
	mEntity= NULL;
	if(resname == "none")
		return;
	switch(type)
	{
	case 0:
		mEntity = Core::getSingleton().mSceneMgr->createEntity(resname);
		mNode->attachObject(mEntity);
		break;
	case 1:
		static int n = 0;
		mParticleId = std::string("Ranged_PU") + Ogre::StringConverter::toString(n++);
		mParticle = Core::getSingleton().createPUSystem(mParticleId,resname);
		mParticle->prepare();
		mNode->attachObject(mParticle);
		break;
	}
}
RangedCutScene::~RangedCutScene()
{
	clear();
}

void RangedCutScene::startCutScence()
{
	if(mNode)
	{
		mNode->setVisible(true);
		if(mParticle)
			mParticle->start();
	}
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
	Ogre::Vector3 vec = mEndpoint - mStartpoint;
	vec.normalise();
	vec = vec * deltaTime / 25.0f;
	mNode->translate(vec);
	Ogre::Vector3 vec1 = mEndpoint - mNode->getPosition();
	float dot = vec1.dotProduct(vec);
	if(dot <0.0f)
		mNode->setPosition(mEndpoint);
}

void RangedCutScene::clear()
{
	if(mNode)
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
}