#include "UnitGrap.h"

#include "Core.h"
#include "AnimationBlender.h"
#include "Terrain.h"
#include "DataLibrary.h"

#include <iostream>

#define ALPHA_DELTA_TIME 100
#define MOVE_KEYFRAME_TIME 1.5

UnitGrap::UnitGrap(std::string unitmesh, std::string unitmat,std::string factiontex,Ogre::SceneNode* node):
mNode(node),
mMainWeapon(NULL),
mSecWeapon(NULL),
mShield(NULL),
mPUSystem(NULL),
mPUSystemEnd(false),
mIsCheckHeight(false),
mAlpha(-1),
mAlphaDeltaTime(0),
mNodeAnimation(NULL),
mNodeAnimationState(NULL),
mFormationPosition(0),
mOffsetX(0),
mOffsetY(0)
{

	mIdleName="Ready1H";
	mLeftHandBoneName = "Bip01 L Hand";
	mRightHandBoneName = "Bip01 R Hand";
	mWalkName = "Run1H";
	mDeathName = "Death";
	mRecoverName ="Recover";
	mRotationName = "JumpLoop";

	mUnitEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(unitmesh);
	if (unitmat!="none")
	{
		mUnitEntity->setMaterialName(unitmat);
	}
	mNode->attachObject(mUnitEntity);

	mAniBlender=new AnimationBlender(mUnitEntity);
	mAniBlender->init(mIdleName);
}

UnitGrap::~UnitGrap(void)
{	
	mUnitEntity->detachAllObjectsFromBone();

	if (mMainWeapon!=NULL)
	{
		delete mMainWeapon;
	}

	if (mSecWeapon!=NULL)
	{
		delete mSecWeapon;
	}

	if (mShield!=NULL)
	{
		delete mShield;
	}
	
	if (mPUSystem!=NULL)
	{
		mNode->detachObject(mPUSystem);
		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
		mPUSystem=NULL;
	}

	mNode->detachAllObjects();
	Core::getSingletonPtr()->mSceneMgr->destroySceneNode(mNode);
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mUnitEntity);
}

void UnitGrap::setWeapon( WeaponType type,BoneType bone )
{
	std::string boneName;

	switch(bone)
	{
	case LeftHand:
		{
			boneName=mLeftHandBoneName;
			break;
		}
	case RightHand:
		{
			boneName=mRightHandBoneName;
			break;
		}
	}

	if (mMainWeapon!=NULL)
	{
		if (mMainWeapon->getAttachBoneName()==boneName)
		{
			mMainWeapon->detachWeapon(mUnitEntity);
		}
	}

	if (mSecWeapon!=NULL)
	{
		if (mSecWeapon->getAttachBoneName()==boneName)
		{
			mSecWeapon->detachWeapon(mUnitEntity);
		
		}
	}

	if (mShield!=NULL)
	{
		if (mShield->getAttachBoneName()==boneName)
		{
			mShield->detachWeapon(mUnitEntity);
		}
	}


	switch(type)
	{
	case MainWepon:
		{
			if (mMainWeapon!=NULL)
			{
				mMainWeapon->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	case SecWepon:
		{
			if (mSecWeapon!=NULL)
			{
				mSecWeapon->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	case Shield:
		{
			if (mShield!=NULL)
			{
				mShield->attachWeapon(mUnitEntity,boneName);
			}
			break;
		}
	}
}

void UnitGrap::createWeapon( std::string mesh, std::string mat,WeaponType type )
{
	if (mesh!="none")
	{
		switch(type)
		{
		case MainWepon:
			{
				mMainWeapon=new WeaponGrap(mesh,mat);
				break;
			}
		case SecWepon:
			{
				mSecWeapon=new WeaponGrap(mesh,mat);
				break;
			}
		case Shield:
			{
				mShield=new WeaponGrap(mesh,mat);
				break;
			}
		}
	}
}

void UnitGrap::setEffect( std::string name )
{
	if (mPUSystem!=NULL)
	{
		mNode->detachObject(mPUSystem);
		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
		mPUSystem=NULL;
	}

	mPUSystem=Core::getSingletonPtr()->createPUSystem(mNode->getName()+"_PU",name);
	mPUSystem->addParticleSystemListener(this);
	mNode->attachObject(mPUSystem);
	mPUSystem->prepare();
	mPUSystem->start();
}

bool UnitGrap::isEffectOver()
{
	return mPUSystemEnd;
}

void UnitGrap::handleParticleSystemEvent( ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent )
{
	if (particleUniverseEvent.componentType==ParticleUniverse::CT_SYSTEM && particleUniverseEvent.eventType==ParticleUniverse::PU_EVT_NO_PARTICLES_LEFT)
	{
		mPUSystemEnd=true;
	}
}

void UnitGrap::stopEffect()
{
	mPUSystem->stop();
}

void UnitGrap::setMovePath( std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions)
{
	mNodeAnimation = Core::getSingletonPtr()->mSceneMgr->createAnimation(mNode->getName()+"_Ani", vectors.size()*MOVE_KEYFRAME_TIME);
	mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mNode);

	float timePosition=0;
	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(timePosition);
	kf->setTranslate(mNode->getPosition());
	kf->setRotation(mNode->getOrientation());

	std::map<int,Ogre::Vector3>::iterator itr  =  vectors.begin();
	for(  ;  itr !=  vectors.end();  ++itr )
	{
		timePosition+=MOVE_KEYFRAME_TIME;
		kf = track->createNodeKeyFrame(timePosition);

		kf->setTranslate(itr->second);//+Ogre::Vector3(mOffsetX,0,mOffsetY));

		std::map<int,Ogre::Quaternion>::iterator itr1;
		itr1 = quaternions.find(itr->first);

		if( itr1 != quaternions.end() )
		{
			kf->setRotation(itr1->second);
		}
	}

	mNodeAnimationState = Core::getSingletonPtr()->mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

	mIsCheckHeight=true;
	mNodeAnimationState->setLoop(false);
	mNodeAnimationState->setEnabled(true);
	setAnimation(mWalkName,true,false);

	mReturnInitAni=true;
}

void UnitGrap::setPosition( float x,float z )
{
	mNode->setPosition(x+mOffsetX,0,z+mOffsetY);
	setHeight();
}

void UnitGrap::setHeight()
{
	Ogre::Vector3 v=mNode->getPosition();
	//Ogre::Vector3 v=mNode->convertLocalToWorldPosition(lv);
	v.y=Terrain::getSingletonPtr()->getHeight(v.x,v.z);
	mNode->setPosition(v);
}

void UnitGrap::setPositionOffset( float ox,float oy )
{
	Ogre::Vector3 v=mNode->getPosition();
	v.x-=mOffsetX;
	v.z-=mOffsetY;
	v.x+=ox;
	v.z+=oy;
	mNode->setPosition(v.x,0,v.z);
	setHeight();
	mOffsetX=ox;
	mOffsetY=oy;
}

void UnitGrap::setFadeInOut( bool isIn )
{
	//¿½±´²ÄÖÊ
	Ogre::Pass *pass=NULL;
	for(int i = 0; i < mUnitEntity->getNumSubEntities(); ++i)
	{
		Ogre::MaterialPtr p;
		if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(mUnitEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy"))
		{
			p=Ogre::MaterialManager::getSingletonPtr()->getByName(mUnitEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
		}
		else
		{
			p=mUnitEntity->getSubEntity(i)->getMaterial()->clone(mUnitEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
		}

		pass = p->getTechnique(0)->getPass(0);
		pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA); 
		pass->setDepthCheckEnabled(true); 
		pass->setDepthWriteEnabled(false);
		mUnitEntity->getSubEntity(i)->setMaterial(p);
	}

	if (mMainWeapon!=NULL)
	{
		mMainWeapon->startFade();
	}

	if (mSecWeapon!=NULL)
	{
		mSecWeapon->startFade();
	}
	
	if (mShield!=NULL)
	{
		mShield->startFade();
	}

	if (isIn)
	{
		mAlpha=0;
		mFadeInOut=true;
	}
	else
	{
		mAlpha=1;
		mFadeInOut=false;
	}

	pass->setDiffuse(pass->getDiffuse().r, pass->getDiffuse().g, pass->getDiffuse().b, mAlpha); 
}

void UnitGrap::doFadeInOut(unsigned int deltaTime )
{
	mAlphaDeltaTime+=deltaTime;
	if (mAlphaDeltaTime>=ALPHA_DELTA_TIME)
	{
		mAlphaDeltaTime=0;
		
		if (mFadeInOut)
		{
			mAlpha+=0.1;
		}
		else
		{
			mAlpha-=0.1;
		}
	
		for(int i = 0; i < mUnitEntity->getNumSubEntities(); ++i)
		{
			if (mAlpha>=1 || mAlpha <=0)
			{
				std::string n = mUnitEntity->getSubEntity(i)->getMaterial()->getName();
				n.replace(n.find("_Copy"),5,"");
				mUnitEntity->getSubEntity(i)->setMaterialName(n);
				Ogre::MaterialManager::getSingletonPtr()->remove(mUnitEntity->getSubEntity(i)->getMaterial()->getName()+"_Copy");
				if( mAlpha <=0)
				{
					mUnitEntity->setVisible(false);
				}
			}
			else
			{
				Ogre::Pass *pass = mUnitEntity->getSubEntity(i)->getMaterial()->getTechnique(0)->getPass(0);
				pass->setDiffuse(pass->getDiffuse().r, pass->getDiffuse().g, pass->getDiffuse().b, mAlpha); 
			}
		}

		if (mAlpha>=1 || mAlpha <=0)
		{
			mAlpha=-1;
			if (mMainWeapon!=NULL)
			{
				if( mAlpha <=0)
				{
					mMainWeapon->overFade(false);
				}
				else
				{
					mMainWeapon->overFade(true);
				}
			}

			if (mSecWeapon!=NULL)
			{
				if( mAlpha <=0)
				{
					mSecWeapon->overFade(false);
				}
				else
				{
					mSecWeapon->overFade(true);
				}
			}

			if (mShield!=NULL)
			{
				if( mAlpha <=0)
				{
					mSecWeapon->overFade(false);
				}
				else
				{
					mSecWeapon->overFade(true);
				}
			}
		}
		else
		{
			if (mMainWeapon!=NULL)
			{
				mMainWeapon->doFade(mAlpha);
			}

			if (mSecWeapon!=NULL)
			{
				mSecWeapon->doFade(mAlpha);
			}

			if (mShield!=NULL)
			{
				mShield->doFade(mAlpha);
			}
		}
	}
}

void UnitGrap::setAnimation( std::string name,bool loop,bool returnInit )
{
	mAniBlender->blend(name,AnimationBlender::BlendWhileAnimating,0.2,loop);
	mReturnInitAni=returnInit;
}

void UnitGrap::stopTransform()
{
	Core::getSingletonPtr()->mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
	Core::getSingletonPtr()->mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
	mNodeAnimation=NULL;
	mNodeAnimationState=NULL;
	mIsCheckHeight=false;
}

void UnitGrap::update( unsigned int deltaTime )
{
	mAniBlender->addTime(deltaTime/1000.0f);
	
	if (mReturnInitAni && mAniBlender->complete)
	{
		mAniBlender->BackToInit();
		mReturnInitAni=false;
	}

	if(mNodeAnimationState!=NULL)
	{
		if (mNodeAnimationState->getTimePosition() >= mNodeAnimationState->getLength())
		{
			stopTransform();
			if (mReturnInitAni)
			{
				mAniBlender->BackToInit();
			}
		}
		else
		{
			mNodeAnimationState->addTime(deltaTime/1000.0f);
		}
	}

	if (mIsCheckHeight)
	{
		setHeight();
	}

	if(mAlpha!=-1)
	{
		doFadeInOut(deltaTime);
	}
}
