#include "UnitGrap.h"

#include "Core.h"
#include "AnimationBlender.h"
#include "Terrain.h"
#include "DataLibrary.h"
#include "AudioSystem.h"

#include <iostream>

#define ALPHA_DELTA_TIME 100
#define MOVE_KEYFRAME_TIME 0.05

UnitGrap::UnitGrap(std::string unitmesh, std::string unitmat,std::string horsemesh,std::string horsemat,std::string factiontex,Ogre::SceneNode* node):
mNode(node),
mMainWeapon(NULL),
mSecWeapon(NULL),
mShield(NULL),
//mPUSystem(NULL),
//mPUNode(NULL),
//mPUSystemEnd(false),
mIsCheckHeight(false),
//mAlpha(-1),
//mAlphaDeltaTime(0),
mNodeAnimation(NULL),
mNodeAnimationState(NULL),
mFormationPosition(0),
mOffsetX(0),
mOffsetY(0),
mIsAnimationComplete(true)
{

	mIdleName="Ready1H";
	mLeftHandBoneName = "Bip01 L Hand";
	mRightHandBoneName = "Bip01 R Hand";
	mWalkName = "Run1H";
	mAttackName = "Attack1H1";
	mDeathName = "Death";
	mRecoverName ="Recover";

	mUnitEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(unitmesh);
	if (unitmat!="none")
	{
		mUnitEntity->setMaterialName(unitmat);
	}

	if(horsemesh!="none")
	{
		mHorseEntity=Core::getSingletonPtr()->mSceneMgr->createEntity(horsemesh);

		if (horsemat!="none")
		{
			mHorseEntity->setMaterialName(horsemat);
		}
	}
	else
	{
		mHorseEntity=NULL;
	}

	mNode->attachObject(mUnitEntity);
	if (mHorseEntity!=NULL)
	{
		mNode->attachObject(mHorseEntity);
	}
	

	mAniBlender=new AnimationBlender(mUnitEntity);
	mAniBlender->init(mIdleName);
	if (mHorseEntity!=NULL)
	{
		mHorseAniBlender=new AnimationBlender(mHorseEntity);
		mHorseAniBlender->init(mIdleName);
	}
	else
	{
		mHorseAniBlender=NULL;
	}

	mParticleVisible = true;
	mParticleNode = mNode->createChildSceneNode();
	mParticleNode->setPosition(0.0f,3.0f,0.0f);

	if(!mUnitEntity->getAllAnimationStates()->hasAnimationState("Recover"))
	{
		mRecoverName="Ready1H";
	}
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
	
	for(PUMapIte ite = mPUMap.begin();ite != mPUMap.end(); ite++)
	{
		ite->second->stop();
		mParticleNode->detachObject(ite->second);
		Core::getSingleton().destroyPUSystem(ite->second);
	}
	Core::getSingletonPtr()->mSceneMgr->destroySceneNode(mParticleNode);
	mNode->detachAllObjects();
	Core::getSingletonPtr()->mSceneMgr->destroySceneNode(mNode);
	Core::getSingletonPtr()->mSceneMgr->destroyEntity(mUnitEntity);
	if(mHorseEntity!=NULL)
	{
		Core::getSingletonPtr()->mSceneMgr->destroyEntity(mHorseEntity);
	}
	
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
				if(mMainWeapon!=NULL)
				{	
					if(mMainWeapon->getAttachBoneName() == mRightHandBoneName)
						mMainWeapon->detachWeapon(mUnitEntity);
				}
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

void UnitGrap::playWeaponParticle( WeaponType type,std::string name )
{
	switch(type)
	{
	case MainWepon:
		{
			if (mMainWeapon!=NULL)
			{
				mMainWeapon->playParticleUniverse(name);
			}
			break;
		}
	case SecWepon:
		{
			if (mSecWeapon!=NULL)
			{
				mSecWeapon->playParticleUniverse(name);
			}
			break;
		}
	case Shield:
		{
			if (mShield!=NULL)
			{
				mShield->playParticleUniverse(name);
			}
			break;
		}
	}
}

void UnitGrap::stopWeaponParticle( WeaponType type)
{
	switch(type)
	{
	case MainWepon:
		{
			if (mMainWeapon!=NULL)
			{
				mMainWeapon->stopParticleUniverse();
			}
			break;
		}
	case SecWepon:
		{
			if (mSecWeapon!=NULL)
			{
				mSecWeapon->stopParticleUniverse();
			}
			break;
		}
	case Shield:
		{
			if (mShield!=NULL)
			{
				mShield->stopParticleUniverse();
			}
			break;
		}
	}
}

void UnitGrap::setAniGroup(std::string anigroup)
{
	if(anigroup == "1H2")
	{
		mWalkName = std::string("Run1H");;
		mAttackName = std::string("Attack1H2");
		mIdleName = std::string("Ready1H");
	}
	else if(anigroup == "1H")
	{
		if(mHorseEntity==NULL)
		{
			mWalkName = std::string("Run1H");;
			mAttackName = std::string("Attack1H2");
			mIdleName = std::string("Ready1H");
		}
		else
		{
			mWalkName = std::string("Run1H");;
			mAttackName = std::string("Attack1H");
			mIdleName = std::string("Ready1H");
		}
	}
	else if(anigroup == "1H3")
	{
		mWalkName = std::string("Run1H");;
		mAttackName = std::string("Attack1H3");
		mIdleName = std::string("Ready1H");
	}
	else if(anigroup == "2HL")
	{
		mWalkName = std::string("Run2HL");;
		mAttackName = std::string("Attack2HL2");
		mIdleName = std::string("Ready2HL");
	}
	else if(anigroup == "2H1")
	{
		mWalkName = std::string("Run2H");;
		mAttackName = std::string("Attack2H1");
		mIdleName = std::string("Ready2H");
	}
	else if(anigroup == "Bow")
	{
		if(mHorseEntity==NULL)
		{
			mWalkName = std::string("Run1H");;
			mAttackName = std::string("AttackBow");
			mIdleName = std::string("Ready1H");
		}
		else
		{
			mWalkName = std::string("RunBow");;
			mAttackName = std::string("AttackBow");
			mIdleName = std::string("ReadyBow");
		}
	}
	else if(anigroup == "Crossbow")
	{
		if(mHorseEntity==NULL)
		{
			mWalkName = std::string("Run1H");
			mAttackName = std::string("AttackCrossbow");
			mIdleName = std::string("Ready1H");
		}
		else
		{
			mWalkName = std::string("RunCrossbow");
			mAttackName = std::string("AttackCrossbow");
			mIdleName = std::string("ReadyCrossbow");
		}
	}
	mAniBlender->init(mIdleName);
	if (mHorseAniBlender!=NULL)
	{
		mAniBlender->init(mIdleName);
	}
}

void UnitGrap::createWeapon( std::string mesh, std::string mat,std::string weaponPU,Ogre::Vector3 PUVector,WeaponType type )
{
	if (mesh!="none")
	{
		switch(type)
		{
		case MainWepon:
			{
				mMainWeapon=new WeaponGrap(mesh,mat,weaponPU,PUVector);
				break;
			}
		case SecWepon:
			{
				mSecWeapon=new WeaponGrap(mesh,mat,weaponPU,PUVector);
				break;
			}
		case Shield:
			{
				mShield=new WeaponGrap(mesh,mat,weaponPU,PUVector);
				break;
			}
		}
	}
}

void UnitGrap::setMovePath( std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,std::map<int,Direction>& directions,float MoveSpeed,bool NotBezier)
{
	std::cout<<mNode->getName()+"_Ani"<<" Created"<<std::endl;
	mNodeAnimation = Core::getSingletonPtr()->mSceneMgr->createAnimation(mNode->getName()+"_Ani", (vectors.size()-1)*MOVE_KEYFRAME_TIME*20*MoveSpeed);
	mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mNode);

	float timePosition=0;
	Ogre::TransformKeyFrame* kf;
	
	std::map<int,Ogre::Vector3>::iterator itrr=vectors.begin();

	for( std::map<int,Ogre::Vector3>::iterator itr  =  vectors.begin();  itr !=  vectors.end();  itr++ )
	{
		itrr++;

		if(itrr==vectors.end())
			break;
		
		if(itr->second.x==itrr->second.x || itr->second.z==itrr->second.z || NotBezier==true)
		{

			timePosition+=MOVE_KEYFRAME_TIME;
			kf = track->createNodeKeyFrame(timePosition);
			kf->setRotation(quaternions[itr->first]);

			kf->setTranslate(Ogre::Vector3(itr->second.x, Terrain::getSingletonPtr()->getHeight(itr->second.x,itr->second.z),itr->second.z));

			timePosition+=MOVE_KEYFRAME_TIME*19;
			kf = track->createNodeKeyFrame(timePosition);
			kf->setRotation(quaternions[itrr->first]);
			kf->setTranslate(Ogre::Vector3(itrr->second.x,Terrain::getSingletonPtr()->getHeight(itrr->second.x,itrr->second.z),itrr->second.z));

		}
		else
		{


			mBezier.P0.x=itr->second.x;
			mBezier.P0.y=itr->second.z;

			switch(directions[itr->first])
			{
			case North:
				{
					mBezier.P1.x=itr->second.x;
					mBezier.P1.y=itrr->second.z;
					break;
				}
			case South:
				{
					mBezier.P1.x=itr->second.x;
					mBezier.P1.y=itrr->second.z;
					break;
				}
			case West:
				{
					mBezier.P1.x=itrr->second.x;
					mBezier.P1.y=itr->second.z;
					break;
				}
			case East:
				{
					mBezier.P1.x=itrr->second.x;
					mBezier.P1.y=itr->second.z;
					break;
				}
			}


			mBezier.P2.x=itrr->second.x;
			mBezier.P2.y=itrr->second.z;

			mBezier.initValue();

			for(int i=0;i<20;i++)
			{
				mBezier.calculate(i,20);

				timePosition+=MOVE_KEYFRAME_TIME;
				kf = track->createNodeKeyFrame(timePosition);
					
				Ogre::Quaternion q;

				Ogre::Vector3 dir(-mBezier.DX,0,mBezier.DY);
		

				kf->setRotation(dir.getRotationTo(Ogre::Vector3(0,0,1)));

				kf->setTranslate(Ogre::Vector3(mBezier.CurX,Terrain::getSingletonPtr()->getHeight(mBezier.CurX,mBezier.CurY),mBezier.CurY));
			}
		}
	}

	mNodeAnimationState = Core::getSingletonPtr()->mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

	//mIsCheckHeight=true;
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

void UnitGrap::setAnimation( std::string name,bool loop,bool returnInit )
{
	if(name == "Idle")
		name = mIdleName;
	else if(name == "Attack")
		name = mAttackName;
	else if(name == "Walk")
		name == mWalkName;
	mAniBlender->blend(name,AnimationBlender::BlendSwitch,0.2,loop);
	if(mHorseAniBlender!=NULL)
		mHorseAniBlender->blend(name,AnimationBlender::BlendSwitch,0.2,loop);
	mReturnInitAni=returnInit;
	mIsAnimationComplete=false;
}

void UnitGrap::stopTransform()
{
	if (mNodeAnimationState!=NULL)
	{

		Core::getSingletonPtr()->mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
		mNodeAnimationState=NULL;
	}
	
	if (mNodeAnimation!=NULL)
	{
		std::cout<<mNode->getName()+"_Ani"<<" Deleted"<<std::endl;

		Core::getSingletonPtr()->mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
		mNodeAnimation=NULL;
	}
	
	mIsCheckHeight=false;
	if (mReturnInitAni)
	{
		mAniBlender->BackToInit();
		if (mHorseAniBlender!=NULL)
		{
			mHorseAniBlender->BackToInit();
		}
		mReturnInitAni=false;
	}
	AudioSystem::getSingletonPtr()->stopSample();
}

void UnitGrap::update( unsigned int deltaTime )
{
	if (mHorseAniBlender!=NULL)
	{
		mAniBlender->addTime(deltaTime/1000.0f*1.5);
		mHorseAniBlender->addTime(deltaTime/1000.0f*1.5);
	}
	else
	{
		mAniBlender->addTime(deltaTime/1000.0f);
	}
	
	if ( !mIsAnimationComplete && mAniBlender->complete)
	{
		mIsAnimationComplete=true;
		if (mReturnInitAni)
		{
			mAniBlender->BackToInit();
			if (mHorseAniBlender!=NULL)
			{
				mHorseAniBlender->BackToInit();
			}
			mReturnInitAni=false;
		}
	}



	if(mNodeAnimationState!=NULL)
	{
		if (mNodeAnimationState->getTimePosition() >= mNodeAnimationState->getLength())
		{
			stopTransform();
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

}

bool UnitGrap::addParticle(std::string id,std::string name)
{
	PUMapIte ite;
	ite = mPUMap.find(id);
	if(ite != mPUMap.end())
		return false;
	ParticleUniverse::ParticleSystem* pu  = Core::getSingleton().createPUSystem(mParticleNode->getName()+ id, name);
	mParticleNode->attachObject(pu);
	pu->prepare();
	pu->setVisible(mParticleVisible);
	mPUMap.insert(PUMap::value_type(id,pu));
	return true;
}
void UnitGrap::startParticle(std::string id,bool isTriggerEvent)
{
	PUMapIte ite;
	ite = mPUMap.find(id);
	if(ite != mPUMap.end())
	{
		if (isTriggerEvent)
		{
			mIsPUEnd=false;
			ite->second->addParticleSystemListener(this);		
		}
		
		ite->second->start();
	}
}
void UnitGrap::stopParticle(std::string id)
{
	PUMapIte ite;
	ite = mPUMap.find(id);
	if(ite != mPUMap.end())
		ite->second->stop();
}
void UnitGrap::delParticle(std::string id)
{
	PUMapIte ite;
	ite = mPUMap.find(id);
	if(ite == mPUMap.end())
		return;
	ite->second->stop();
	mParticleNode->detachObject(ite->second);
	Core::getSingleton().destroyPUSystem(ite->second);
	mPUMap.erase(ite);
}

void UnitGrap::setParticleVisible(bool visible)
{
	mParticleVisible = visible;
	mParticleNode->setVisible(mParticleVisible);
}

void UnitGrap::handleParticleSystemEvent( ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent )
{
	if (particleUniverseEvent.eventType=ParticleUniverse::PU_EVT_SYSTEM_STOPPED)
	{
		mIsPUEnd=true;
	}
}