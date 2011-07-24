#include "RangedCutScene.h"

#include "Core.h"

RangedCutScene::RangedCutScene(Ogre::Vector3 startpos, Ogre::Vector3 endpoint, int type, std::string resname)
:mStartpoint(startpos),mEndpoint(endpoint)
{
	mNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->setVisible(false);
	mNode->setDirection(startpos - endpoint);
	mNode->setPosition(startpos);
	mLastTime = (startpos - endpoint).length() * 30;
	mLastPoint = startpos;
	mSpline.addPoint(startpos);
	Ogre::Vector3 midpoint = (startpos + endpoint) / 2;
	midpoint.y += (startpos - endpoint).length() / 4;
	mSpline.addPoint(midpoint);
	mSpline.addPoint(endpoint);

	mParticle = NULL;
	mEntity= NULL;
	rootNode=NULL;
	trail=NULL;
	if(resname == "none")
		return;
	switch(type)
	{
	case 0:
		{

		Ogre::NameValuePairList pairList;

		pairList["numberOfChains"] = "1";

		pairList["maxElements"] = "80";

		trail = static_cast<Ogre::RibbonTrail*>(

		Core::getSingletonPtr()->mSceneMgr->createMovableObject("RibbonTrail", &pairList));

		rootNode=Core::getSingletonPtr()->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		rootNode->attachObject(trail);

		trail->setMaterialName("Examples/LightRibbonTrail");

		trail->setTrailLength(50);

		trail->setInitialColour(0, 1.0, 1.0, 1.0,0.3);
		//trail->set

		trail->setColourChange(0, 0.5, 0.5, 0.5, 0.5);

		trail->setInitialWidth(0, 1);
		trail->setWidthChange(0,0.5);

		trail->addNode(mNode);

		
		if (resname!="NoMesh")
		{
			mEntity = Core::getSingleton().mSceneMgr->createEntity(resname);
			mNode->attachObject(mEntity);
		}

		break;
		}
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
// 	Ogre::Vector3 vec = mEndpoint - mStartpoint;
// 	vec.normalise();
// 	vec = vec * deltaTime / 25.0f;
// 	mNode->translate(vec);
// 	Ogre::Vector3 vec1 = mEndpoint - mNode->getPosition();
// 	float dot = vec1.dotProduct(vec);
// 	if(dot <0.0f)
// 		mNode->setPosition(mEndpoint);
	Ogre::Vector3 newpos = mSpline.interpolate((float)mPassedTime/mLastTime );
	mNode->setPosition(newpos);
	mNode->setDirection(newpos - mLastPoint);
	mLastPoint = newpos;
}

void RangedCutScene::clear()
{
	if(mNode)
	{
		mNode->detachAllObjects();
		if (rootNode)
		{
			Core::getSingletonPtr()->mSceneMgr->destroySceneNode(rootNode);
		}
		
		if (trail)
		{
			Core::getSingletonPtr()->mSceneMgr->destroyRibbonTrail(trail);
		}

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