#include "SquadGraphics.h"

#include <stdlib.h>
#include <time.h>

#include "Core.h"
#include "DataLibrary.h"

#include "UnitGrap.h"
#include "AnimationBlender.h"
#include "BillboardManager.h"
#include "GUISquadBillBoard.h"
#include "GUISquadValueBillBoard.h"
#include "AudioSystem.h"

#include "Terrain.h"

const Ogre::Vector3 LineVector[5]={Ogre::Vector3(0,0,6),Ogre::Vector3(-6,0,6),Ogre::Vector3(6,0,6),Ogre::Vector3(3,0,-3),Ogre::Vector3(-3,0,-3)};
const Ogre::Vector3 CircularVector[5]={Ogre::Vector3(0,0,5),Ogre::Vector3(-5,0,1),Ogre::Vector3(5,0,2),Ogre::Vector3(4,0,-4),Ogre::Vector3(-4,0,-4)};
const Ogre::Vector3 LooseVector[5]={Ogre::Vector3(0,0,0),Ogre::Vector3(-5,0,5),Ogre::Vector3(5,0,5),Ogre::Vector3(5,0,-5),Ogre::Vector3(-5,0,-5)};

#define FORMATION_KEYFRAME_TIME 1
#define RELIEF_MOVE_TIME 1
#define COMBAT_POSITION 5

SquadGraphics::SquadGraphics(std::string squadName,std::string datapath,Ogre::Vector2& grid,Direction direction,Formation f,unsigned int index,int soldierCount):
mSquadId(squadName),
mID(index),
// mPUSystem(NULL),
// mPUSystemEnd(false),
mNodeAnimation(NULL),
mNodeAnimationState(NULL),
mDeathUnit(NULL),
mReliefUnit(NULL),
mSoldierIndex(0),
mFormation(f),
mDirection(direction)
{
	mSceneMgr=Core::getSingletonPtr()->mSceneMgr;
	mNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(squadName+Ogre::StringConverter::toString(index));

	//获取数据

	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	datalib->getData(datapath + std::string("/LeaderMesh"),mLeaderMesh);
	datalib->getData(datapath + std::string("/LeaderMat"),mLeaderMat);
	datalib->getData(datapath + std::string("/UnitMesh"),mSoilderMesh);
	datalib->getData(datapath + std::string("/UnitMat"),mSoilderMat);
	datalib->getData(datapath + std::string("/MoveSound"),mMoveSound);


	std::string tempid;
	datalib->getData(datapath + std::string("/PweaponId"),tempid);
	if(tempid != "none")
	{
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/Mesh"), mPWeaponMesh);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/Mat"), mPWeaponMat);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/AniGroup"), mPWeaponAniGroup);
	}
	else
	{
		mPWeaponMesh = "none";
		mPWeaponMat = "none";
		mPWeaponAniGroup = "1H1";
	}
	datalib->getData(datapath + std::string("/SweaponId"),tempid);
	if(tempid != "none")
	{
		int sweapontype;
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Type"), sweapontype);
		mSWeaponBow = (sweapontype == EQUIP_SWEAPON_BOW);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Mesh"), mSWeaponMesh);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Mat"), mSWeaponMat);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/AniGroup"), mSWeaponAniGroup);
	}
	else
	{
		mSWeaponBow = false;
		mSWeaponMesh = "none";
		mSWeaponMat = "none";
		mSWeaponAniGroup = "bow";
	}
	datalib->getData(datapath + std::string("/ShieldId"),tempid);
	if(tempid != "none")
	{
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/Mesh"), mShieldMesh);
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/Mat"), mShieldMat);
	}
	else
	{
		mShieldMesh = "none";
		mShieldMat = "none";
	}
	datalib->getData(datapath + std::string("/TeamId"),tempid);
	datalib->getData( std::string("GameData/BattleData/Team/") + tempid + std::string("/FactionId"), tempid);
	datalib->getData( std::string("StaticData/FactionData/") + tempid + std::string("/Texture"), mFactionTexture);
	

	//组建单位队伍与组建武器
	mCommanderUnit=new UnitGrap(mLeaderMesh,mLeaderMat,mFactionTexture,mSceneMgr->getRootSceneNode()->createChildSceneNode(mNode->getName()+"_Commander"));
	mCommanderUnit->createWeapon(mPWeaponMesh,mPWeaponMat,UnitGrap::MainWepon);
	mCommanderUnit->createWeapon(mSWeaponMesh,mSWeaponMat,UnitGrap::SecWepon);
	mCommanderUnit->createWeapon(mShieldMesh,mShieldMat,UnitGrap::Shield);

	for (int i=0;i<soldierCount;i++)
	{
		createSoldier();
	}
	
	//设置指示器
	mSquadBB=new GUISquadBillBoard(mCommanderUnit->mNode);
	std::string name;
	int type;
	datalib->getData(datapath + std::string("/Name"),name);
	datalib->getData(datapath + std::string("/SquadType"),type);

	datalib->getData(datapath + std::string("/TeamId"),tempid);
	datalib->getData( std::string("GameData/BattleData/Team/") + tempid + std::string("/Relation"), tempid);
	if (tempid=="player")
	{
		mSquadBB->setName(name,MyGUI::Colour::Blue);
		mSquadBB->mHasApColor=MyGUI::Colour::Blue;
		mSquadBB->mNoneApColor=MyGUI::Colour(0,0,0.5);
	}
	else if (tempid=="enemy1" || tempid=="enemy2" ||tempid=="enemy3")
	{
		mSquadBB->setName(name,MyGUI::Colour::Red);
		mSquadBB->mHasApColor=MyGUI::Colour::Red;
		mSquadBB->mNoneApColor=MyGUI::Colour(0.5,0,0);
	}
	else if (tempid=="aliiance")
	{
		mSquadBB->setName(name,MyGUI::Colour::Green);
		mSquadBB->mHasApColor=MyGUI::Colour::Green;
		mSquadBB->mNoneApColor=MyGUI::Colour(0,0.5,0);
	}
	else
	{
		mSquadBB->setName(name,MyGUI::Colour::Black);
	}

	mSquadBB->setIcon(type);
	mSName=name;
	BillboardManager::getSingletonPtr()->addBillBoard(mSquadBB);

	mSquadValueBB=new GUISquadValueBillBoard(mCommanderUnit->mNode);
	BillboardManager::getSingletonPtr()->addBillBoard(mSquadValueBB);

	//设置参数
	setGrid(grid.x,grid.y);
	setFormation(f,false);
	setDirection(direction,false);
	if(mSWeaponMesh == "none")
		setWeaponMode(SquadGraphics::MainWepon);
	else
		setWeaponMode(SquadGraphics::SceWepon);

	//读取现有效果
	std::vector<std::string> particlelist = datalib->getChildList(datapath + std::string("/ParticleList"));
	std::vector<std::string>::iterator ite;
	for(ite = particlelist.begin(); ite != particlelist.end(); ite++)
	{
		UnitType unittype;
		datalib->getData(datapath + std::string("/ParticleList/")+ (*ite) +std::string("/UnitType"),unittype);
		datalib->getData(datapath + std::string("/ParticleList/")+ (*ite) +std::string("/Particle"),tempid);
		addParticle((*ite),tempid,unittype);
		startParticle((*ite));
	}
}

SquadGraphics::~SquadGraphics(void)
{
	delete mCommanderUnit;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		delete (*it);
	}

// 	if (mPUSystem!=NULL)
// 	{
// 		mNode->detachObject(mPUSystem);
// 		Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
// 		mPUSystem=NULL;
// 	}

	if (mNodeAnimationState!=NULL)
	{
		mSceneMgr->destroyAnimationState(mNode->getName()+"_AniState");
		mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
	}
	
	mNode->removeAndDestroyAllChildren();
	mNode->getParentSceneNode()->removeAndDestroyChild(mNode->getName());

	BillboardManager::getSingletonPtr()->destroyBillBoard(mSquadBB);
	BillboardManager::getSingletonPtr()->destroyBillBoard(mSquadValueBB);
}

void SquadGraphics::setSquadBillBoardState( bool hasAp )
{
	if (hasAp)
	{
		mSquadBB->changeColor(mSquadBB->mHasApColor);
	}
	else
	{
		mSquadBB->changeColor(mSquadBB->mNoneApColor);
	}
}

UnitGrap* SquadGraphics::createSoldier()
{
	mSoldierIndex++;
	UnitGrap* unit=new UnitGrap(mSoilderMesh,mSoilderMat,mFactionTexture,mSceneMgr->getRootSceneNode()->createChildSceneNode(mNode->getName()+"_Soldier"+Ogre::StringConverter::toString(mSoldierIndex)));

	unit->createWeapon(mPWeaponMesh,mPWeaponMat,UnitGrap::MainWepon);
	unit->createWeapon(mSWeaponMesh,mSWeaponMat,UnitGrap::SecWepon);
	unit->createWeapon(mShieldMesh,mShieldMat,UnitGrap::Shield);

	mSoldierUnits.push_back(unit);

	return unit;
}

void SquadGraphics::setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,std::map<int,Direction>& directions)
{
	
	if (vectors.size()==0)
	{
		return;
	}

	Ogre::Vector3 v=vectors[0];
	Ogre::Vector3 df=mNode->getPosition();
	
	if(v.z!=df.z)
	{
		if (v.z-df.z<0)
		{
			setDirection(North,false);
		}
		else
		{
			setDirection(South,false);
		}
	}

	if(v.x!=df.x)
	{
		if (v.x-df.x<0)
		{
			setDirection(West,false);
		}
		else
		{
			setDirection(East,false);
		}
	}

	mNode->setPosition((vectors.end().operator --())->second);
	mDirection=(directions.end().operator --())->second;

	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(mFormation,mDirection,CommanderVector,SoldierVector);

	std::map<int,Ogre::Vector3>* newVectors=getUnitMovePath(mCommanderUnit,vectors,directions,true);
	mCommanderUnit->setMovePath(*newVectors,quaternions);
	mCommanderUnit->mOffsetX=CommanderVector.x;
	mCommanderUnit->mOffsetY=CommanderVector.z;
	delete newVectors;

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		newVectors=getUnitMovePath((*it),vectors,directions,false);
		(*it)->setMovePath(*newVectors,quaternions);
		(*it)->mOffsetX=SoldierVector[(*it)->mFormationPosition].x;
		(*it)->mOffsetY=SoldierVector[(*it)->mFormationPosition].z;
		delete newVectors;
	}

	AudioSystem::getSingletonPtr()->playSample(mMoveSound,true);
}

std::map<int,Ogre::Vector3>* SquadGraphics::getUnitMovePath( UnitGrap* unit,std::map<int,Ogre::Vector3>& vectors,std::map<int,Direction>& directions,bool isCommander)
{
	std::map<int,Ogre::Vector3>* newVectors=new std::map<int,Ogre::Vector3>();
	std::map<int,Ogre::Vector3>::iterator itr  =  vectors.begin();

	for(  ;  itr !=  vectors.end();  ++itr )
	{
		std::map<int,Direction>::iterator itr1;
		itr1 = directions.find(itr->first);

		if( itr1 != directions.end() )
		{
			
			Ogre::Vector3 dv;
			Ogre::Vector3 v=vectors[itr->first];
			
			Ogre::Vector3 CommanderVector;
			Ogre::Vector3 SoldierVector[4];

			getFormationPosition(mFormation,itr1->second,CommanderVector,SoldierVector);

			if (isCommander)
			{
				dv=CommanderVector;
			}
			else
			{
				dv=SoldierVector[unit->mFormationPosition];
			}

			v.x=v.x+dv.x;
			v.z=v.z+dv.z;

			(*newVectors)[itr->first]=v;
		}
	}

	return newVectors;
}

bool SquadGraphics::isTransformOver()
{
	if (mCommanderUnit->mNodeAnimationState!=NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void SquadGraphics::stopTransform()
{
	if (mNodeAnimation!=NULL)
	{
		mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
		mNodeAnimationState=NULL;
		
	}
	
	if (mNodeAnimation!=NULL)
	{
		mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
		mNodeAnimation=NULL;
	}

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->stopTransform();
	}
	mCommanderUnit->stopTransform();
	setCheckUnitHeight(false);
	AudioSystem::getSingletonPtr()->stopSample();
}

void SquadGraphics::setAnimation(std::string name,UnitType object,bool isLoop,bool returnInit)
{
	switch(object)
	{
	case UNITTYPE_ALL:
		{

		}
	case UNITTYPE_LEADER:
		{
			mCommanderUnit->setAnimation(name,isLoop,returnInit);
			if (object!=UNITTYPE_ALL)
			{
				break;
			}
		}
	case UNITTYPE_SOLIDER:
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				(*it)->setAnimation(name,isLoop,returnInit);
			}
			break;
		}
	}
}


void SquadGraphics::setInitAnimation( UnitType object )
{
	switch(object)
	{
	case UNITTYPE_ALL:
		{

		}
	case UNITTYPE_LEADER:
		{
			mCommanderUnit->mAniBlender->BackToInit();
			if (object!=UNITTYPE_ALL)
			{
				break;
			}
		}
	case UNITTYPE_SOLIDER:
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				(*it)->mAniBlender->BackToInit();
			}
			break;
		}
	}
}


bool SquadGraphics::isAnimationOver(UnitType object)
{
	bool isCommandEnd=mCommanderUnit->mIsAnimationComplete;
	bool isSoldierEnd=true;
	if (mSoldierUnits.size()!=0)
	{
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			if (!(*it)->mIsAnimationComplete)
			{
				isSoldierEnd=false;
				break;
			}
		}
	}

	if (object==UNITTYPE_LEADER)
	{
		return isCommandEnd;
	}
	else if(object==UNITTYPE_SOLIDER) 
	{
		return isSoldierEnd;
	}
	else
	{
		return isCommandEnd && isSoldierEnd;
	}
}


// void SquadGraphics::setEffect( std::string name,UnitType object)
// {
// 	switch(object)
// 	{
// 	case UNITTYPE_ALL:
// 		{
// 			if (mPUSystem!=NULL)
// 			{
// 				mNode->detachObject(mPUSystem);
// 				Core::getSingletonPtr()->destroyPUSystem(mPUSystem);
// 				mPUSystem=NULL;
// 			}
// 
// 			mPUSystem=Core::getSingletonPtr()->createPUSystem(mNode->getName()+"_PU",name);
// 			mPUSystem->addParticleSystemListener(this);
// 			mPUSystem->prepare();
// 			mNode->attachObject(mPUSystem);
// 			mPUSystem->start();
// 			break;
// 		}
// 	case UNITTYPE_LEADER:
// 		{
// 			mCommanderUnit->setEffect(name);
// 			break;
// 		}
// 	case UNITTYPE_SOLIDER:
// 		{
// 			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
// 			{
// 				(*it)->setEffect(name);
// 			}
// 			break;
// 		}
// 	}
// }

void SquadGraphics::getFormationPosition(Formation f,Direction d,Ogre::Vector3& CommanderVector,Ogre::Vector3 SoldierVector[])
{
	switch(f)//确定各个位置
	{
	case Line:
		{
			CommanderVector=LineVector[0];

			for (int i=1;i<5;i++)
			{
				SoldierVector[i-1]=LineVector[i];
			}
			break;
		}
	case Circular:
		{
			CommanderVector=CircularVector[0];

			for (int i=1;i<5;i++)
			{
				SoldierVector[i-1]=CircularVector[i];
			}
			break;
		}
	case Loose:
		{
			CommanderVector=LooseVector[0];

			for (int i=1;i<5;i++)
			{
				SoldierVector[i-1]=LooseVector[i];
			}
			break;
		}
	}

	int w1,w2;
	switch(d)
	{
	case North:
		{
			w1=-1;
			w2=0;
			break;
		}
	case South:
		{
			w1=1;
			w2=0;
			break;
		}
	case West:
		{
			w1=0;
			w2=1;
			break;
		}
	case East:
		{
			w1=0;
			w2=-1;
			break;
		}
	}

	//x'=xcos-ysin y'=ycos+xsin
	Ogre::Vector3 V;
	V.x=CommanderVector.x*w1-CommanderVector.z*w2;
	V.y=CommanderVector.y;
	V.z=CommanderVector.z*w1+CommanderVector.x*w2;
	CommanderVector=V;

	for (int i=0;i<4;i++)
	{
		V.x=SoldierVector[i].x*w1-SoldierVector[i].z*w2;
		V.y=SoldierVector[i].y;
		V.z=SoldierVector[i].z*w1+SoldierVector[i].x*w2;
		SoldierVector[i]=V;
	}
}

void SquadGraphics::setFormation( Formation f,bool isAnim )
{
	mFormation=f;
	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(f,mDirection,CommanderVector,SoldierVector);

	if (isAnim)
	{
		mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani",FORMATION_KEYFRAME_TIME);
		mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
		Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(0,mCommanderUnit->mNode);

		Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
		kf->setTranslate(mCommanderUnit->mNode->getPosition());
		kf->setRotation(mCommanderUnit->mNode->getOrientation());
		kf->setScale(mCommanderUnit->mNode->getScale());
		Ogre::Quaternion q=mCommanderUnit->mNode->getOrientation();

		kf=track->createNodeKeyFrame(FORMATION_KEYFRAME_TIME);
		Ogre::Vector3 v=CommanderVector;
		mCommanderUnit->mOffsetX=v.x;
		mCommanderUnit->mOffsetY=v.z;
		Ogre::Vector3 np=mNode->getPosition();
		v+=np;
		v.y=Terrain::getSingletonPtr()->getHeight(v.x,v.z);
		kf->setTranslate(v);
		//Ogre::Quaternion destQ;
		//Ogre::Vector3 lv=mCommanderUnit->mNode->getPosition();
		//destQ.FromAngleAxis(lv.angleBetween(v),Ogre::Vector3(0,1,0));
		kf->setRotation(mCommanderUnit->mNode->getOrientation());
		kf->setScale(mCommanderUnit->mNode->getScale());

	/*	kf=track->createNodeKeyFrame(2);
		kf->setTranslate(v);
		kf->setRotation(mCommanderUnit->mNode->getOrientation());
		kf->setScale(mCommanderUnit->mNode->getScale());*/

		int i=0;
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			track = mNodeAnimation->createNodeTrack(i+1,(*it)->mNode);

			Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
			kf->setTranslate((*it)->mNode->getPosition());
			kf->setRotation((*it)->mNode->getOrientation());
			kf->setScale((*it)->mNode->getScale());
			//Ogre::Quaternion q=(*it)->mNode->getOrientation();

			//kf=track->createNodeKeyFrame(1.5);
			v=SoldierVector[i];
			(*it)->mOffsetX=v.x;
			(*it)->mOffsetY=v.z;
			v+=mNode->getPosition();
			v.y=Terrain::getSingletonPtr()->getHeight(v.x,v.z);
			//kf->setTranslate(v);
			//kf->setRotation((*it)->mNode->getPosition().getRotationTo(v));
			//kf->setScale((*it)->mNode->getScale());

			kf=track->createNodeKeyFrame(FORMATION_KEYFRAME_TIME);
			kf->setTranslate(v);
			kf->setRotation((*it)->mNode->getOrientation());
			kf->setScale((*it)->mNode->getScale());
			(*it)->mFormationPosition=i;
			i++;
		}

		mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

		setCheckUnitHeight(true);
		mNodeAnimationState->setLoop(false);
		mNodeAnimationState->setEnabled(true);

		mCommanderUnit->setAnimation(mCommanderUnit->mWalkName,true,false);
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			(*it)->setAnimation((*it)->mWalkName,true,false);
		}
		mReturnInitAni=true;

	}
	else
	{
		mCommanderUnit->setPositionOffset(CommanderVector.x,CommanderVector.z);
		
		int i=0;
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			(*it)->setPositionOffset(SoldierVector[i].x,SoldierVector[i].z);
			(*it)->mFormationPosition=i;
			i++;
		}
	}
}

bool SquadGraphics::isFormationOrDirectionOver()
{
	if (mNodeAnimationState!=NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// void SquadGraphics::handleParticleSystemEvent( ParticleUniverse::ParticleSystem *particleSystem, ParticleUniverse::ParticleUniverseEvent &particleUniverseEvent )
// {
// 	if (particleUniverseEvent.componentType==ParticleUniverse::CT_SYSTEM && particleUniverseEvent.eventType==ParticleUniverse::PU_EVT_NO_PARTICLES_LEFT)
// 	{
// 		mPUSystemEnd=true;
// 	}
// }
// 
// bool SquadGraphics::isEffectOver( UnitType object )
// {
// 	switch(object)
// 	{
// 	case UNITTYPE_ALL:
// 		{
// 			return mPUSystemEnd;
// 			break;
// 		}
// 	case UNITTYPE_LEADER:
// 		{
// 			mCommanderUnit->isEffectOver();
// 			break;
// 		}
// 	case UNITTYPE_SOLIDER:
// 		{
// 			if (mSoldierUnits.size()!=0)
// 			{
// 				return mSoldierUnits.at(0)->isEffectOver();
// 			}
// 			else
// 			{
// 				return true;
// 			}
// 			break;
// 		}
// 	}
// 
// 	return true;
// }
// 
// void SquadGraphics::stopEffect( UnitType object )
// {
// 	if (mPUSystem!=NULL)
// 	{
// 		switch(object)
// 		{
// 		case UNITTYPE_ALL:
// 			{
// 				mPUSystem->stop();
// 				break;
// 			}
// 		case UNITTYPE_LEADER:
// 			{
// 				mCommanderUnit->stopEffect();
// 				break;
// 			}
// 		case UNITTYPE_SOLIDER:
// 			{
// 				for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
// 				{
// 					(*it)->stopEffect();
// 				}
// 				break;
// 			}
// 		}
// 	}
// }

void SquadGraphics::setGrid(int x,int y)
{
	float wx,wy=0;
	Terrain::getSingletonPtr()->getWorldCoords(x,y,wx,wy);
	
	mNode->setPosition(wx,0,wy);

	mCommanderUnit->setPosition(wx,wy);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setPosition(wx,wy);
	}
}

void SquadGraphics::setScale( Ogre::Vector3 scale,bool isAnim )
{

}

void SquadGraphics::setDirection( Direction d,bool isAnim )
{
	mDirection=d;

	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(mFormation,d,CommanderVector,SoldierVector);

	Ogre::Quaternion q;

	switch(d)
	{
	case North:
		{
			q.FromAngleAxis(Ogre::Degree(180),Ogre::Vector3(0,1,0));
			break;
		}
	case South:
		{
			q.FromAngleAxis(Ogre::Degree(360),Ogre::Vector3(0,1,0));
			break;
		}
	case West:
		{
			q.FromAngleAxis(Ogre::Degree(270),Ogre::Vector3(0,1,0));
			break;
		}
	case East:
		{
			q.FromAngleAxis(Ogre::Degree(90),Ogre::Vector3(0,1,0));
			break;
		}
	}
	//x'=xcos-ysin y'=ycos+xsin
	mCommanderUnit->setPositionOffset(CommanderVector.x,CommanderVector.z);
	mCommanderUnit->mNode->setOrientation(q);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setPositionOffset(SoldierVector[(*it)->mFormationPosition].x,SoldierVector[(*it)->mFormationPosition].z);
		(*it)->mNode->setOrientation(q);
	}

	//if (isAnim)
	//{
	//	mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani", 2);
	//	mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	//	Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mNode);

	//	Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
	//	kf->setTranslate(mNode->getPosition());
	//	kf->setRotation(mNode->getOrientation());

	//	kf = track->createNodeKeyFrame(2);
	//	kf->setTranslate(mNode->getPosition());
	//	kf->setRotation(q);

	//	mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani");
	//	
	//	setCheckUnitHeight(true);
	//	mNodeAnimationState->setLoop(false);
	//	mNodeAnimationState->setEnabled(true);

	//	mCommanderUnit->setAnimation(mCommanderUnit->mRotationName,true,false);
	//	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	//	{
	//		(*it)->setAnimation((*it)->mRotationName,true,false);
	//	}
	//	mReturnInitAni=true;
	//}
	//else
	//{
	//	mNode->setOrientation(q);
	//}
}

void SquadGraphics::setCheckUnitHeight( bool enable )
{
	mCommanderUnit->mIsCheckHeight=enable;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->mIsCheckHeight=enable;
	}
}

void SquadGraphics::setWeaponMode( WeaponMode mode )
{
	UnitGrap::WeaponType type;
	UnitGrap::BoneType bonetype;
	std::string anigroup;
	if (mode==MainWepon)
	{
		type=UnitGrap::MainWepon;
		anigroup = mPWeaponAniGroup;
		bonetype = UnitGrap::RightHand;
	}
	else
	{
		type=UnitGrap::SecWepon;
		anigroup = mSWeaponAniGroup;
		if(mSWeaponBow)
			bonetype = UnitGrap::LeftHand;
		else
			bonetype = UnitGrap::RightHand;
	}

	mCommanderUnit->setWeapon(UnitGrap::Shield,UnitGrap::LeftHand);
	mCommanderUnit->setWeapon(type,bonetype);
	mCommanderUnit->setAniGroup(anigroup);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setWeapon(UnitGrap::Shield,UnitGrap::LeftHand);
		(*it)->setWeapon(type,bonetype);
		(*it)->setAniGroup(anigroup);
	}
}

void SquadGraphics::setDeath()
{
	if (mSoldierUnits.size()!=0)//还有士兵?
	{
		//随机选择
		int i;
		if (mSoldierUnits.size()!=1)
		{
			i=rand()%(mSoldierUnits.size()-1);
		}
		else
		{
			i=0;
		}

		mDeathUnit=mSoldierUnits.at(i);

		mReliefUnit=NULL;

		if (mDeathUnit->mFormationPosition<2)//如果是前排?
		{
			int findF;//确定士兵队伍里面还有没有替补?
			if (i==0)
			{
				findF=3;
			}
			else
			{
				findF=2;
			}
			
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				if ((*it)->mFormationPosition==findF)
				{
					mReliefUnit=(*it);
				}
			}

			if (mReliefUnit!=NULL)//如果找到了替补队员
			{
				mReliefUnit->mFormationPosition=mDeathUnit->mFormationPosition;
				mReliefUnit->mOffsetX=mDeathUnit->mOffsetX;
				mReliefUnit->mOffsetY=mDeathUnit->mOffsetY;
			}

		}

	}
	else
	{
		mDeathUnit=mCommanderUnit;
		mReliefUnit=NULL;
	}

	//执行死亡动画
	mDeathUnit->setAnimation(mDeathUnit->mDeathName,false,false);
	mDeathStep=playAni;

}

void SquadGraphics::doDeathStep()
{
	switch(mDeathStep)
	{
	case playAni:
		{
			//等待死亡动画结束
			if (mDeathUnit->mAniBlender->complete)
			{
				mDeathStep=changeMat;
				mDeathUnit->setFadeInOut(false);
			}

			break;
		}
	case changeMat:
		{
			if (mReliefUnit!=NULL)//需要替补?
			{
				mDeathStep=moveUnit;
			}
			else
			{
				mDeathStep=resetAni;//终止
			}
			break;
		}
	case moveUnit:
		{
			mReliefAniName=mReliefUnit->mAniBlender->getSource()->getAnimationName();
			mReliefAniLoop=mReliefUnit->mAniBlender->getSource()->getLoop();
			
			//设置节点动画
			mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani", RELIEF_MOVE_TIME);
			mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
			Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(1, mReliefUnit->mNode);

			Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
			kf->setTranslate( mReliefUnit->mNode->getPosition());
			kf->setRotation( mReliefUnit->mNode->getOrientation());
			kf->setScale(mReliefUnit->mNode->getScale());

			kf = track->createNodeKeyFrame(RELIEF_MOVE_TIME);
			kf->setTranslate(mDeathUnit->mNode->getPosition());
			kf->setRotation(mReliefUnit->mNode->getOrientation());
			kf->setScale( mReliefUnit->mNode->getScale());

			mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani");

			//setCheckUnitHeight(true);
			mNodeAnimationState->setLoop(false);
			mNodeAnimationState->setEnabled(true);

			mReturnInitAni=false;

			//设置跑步动画
			mReliefUnit->setAnimation(mReliefUnit->mWalkName,true,false);
			
			mDeathStep=resetAni;

			break;
		}
	case resetAni:
		{
			if (mNodeAnimation==NULL)
			{
				if(mReliefUnit!=NULL)
				{
					//回复原来动画
					mReliefUnit->setAnimation(mReliefAniName,mReliefAniLoop,false);
					mReliefUnit=NULL;
				}
				
				if (mDeathUnit->mAlpha==-1)
				{
					//移除单位
					for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
					{
						if ((*it)==mDeathUnit)
						{
							mSoldierUnits.erase(it);
							break;
						}
					}

					if (mDeathUnit==mCommanderUnit)
					{
						mCommanderUnit=NULL;
					}

					delete mDeathUnit;
					mDeathUnit=NULL;
				}
			}
			break;
		}
	}
}

void SquadGraphics::stopDeath()
{
	if (mReliefUnit!=NULL)
	{
		if (mNodeAnimation!=NULL)
		{
			stopTransform();
		}

		mReliefUnit->mNode->setPosition(mDeathUnit->mNode->getPosition());
	}

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		if ((*it)==mDeathUnit)
		{
			mSoldierUnits.erase(it);
			break;
		}
	}

	delete mDeathUnit;
	mDeathUnit=NULL;
}

bool SquadGraphics::isDeathOver()
{
	if (mDeathUnit!=NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool SquadGraphics::isRecoverOver()
{
	bool over=true;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		if((*it)->mAniBlender->getSource()->getAnimationName()==(*it)->mRecoverName)
		{
			over=false;
			break;
		}
	}
	return over;
}

void SquadGraphics::setRecover(int num)
{
	int size=mSoldierUnits.size();
	if (mSoldierUnits.size()+num<5)
	{
		for (int i=0;i<num;i++)
		{
			int findIndex=-1;
			
			for (int j=0;j<mSoldierUnits.size();j++)
			{
				bool flag=false;
				for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
				{
					if((*it)->mFormationPosition==j)
					{
						flag=true;
						break;
					}
				}

				if (!flag)//没有找到?
				{
					findIndex=j;
					break;
				}
			}

			UnitGrap* unit=createSoldier();
			unit->mFormationPosition=findIndex;
				
			Ogre::Vector3 CommanderVector;
			Ogre::Vector3 SoldierVector[4];

			getFormationPosition(mFormation,mDirection,CommanderVector,SoldierVector);
			unit->setPositionOffset(SoldierVector[unit->mFormationPosition].x,SoldierVector[unit->mFormationPosition].z);

			unit->setFadeInOut(true);
			unit->setAnimation(unit->mRecoverName,false,true);

		}
	}
}


void SquadGraphics::update( unsigned int deltaTime )
{
	if (mDeathUnit!=NULL)
	{
		doDeathStep();
	}
	
	if (mNodeAnimationState!=NULL)
	{
		if (mNodeAnimationState->getTimePosition() >= mNodeAnimationState->getLength())
		{
			stopTransform();
			if (mReturnInitAni)
			{
				setInitAnimation(UNITTYPE_ALL);
			}
		}
		else
		{
			mNodeAnimationState->addTime(deltaTime/1000.0f);
		}
	}

	if (mCommanderUnit!=NULL)
	{
		mCommanderUnit->update(deltaTime);
	}
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->update(deltaTime);
	}
}

void SquadGraphics::setVisible(bool visible)
{
	mCommanderUnit->mNode->setVisible(visible);

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->mNode->setVisible(visible);
	}

	mSquadBB->setVisible(visible);

	mVisibale = visible;
}

Direction SquadGraphics::getDirection()
{
	return mDirection;
}

void SquadGraphics::setParticleVisible(bool visible)
{
	mCommanderUnit->setParticleVisible(visible);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setParticleVisible(visible);
	}
}

bool SquadGraphics::addParticle(std::string id,std::string name,UnitType object)
{
	bool re = false;
	switch(object)
	{
	case UNITTYPE_ALL:
		re |= mCommanderUnit->addParticle(id,name);
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			re |= (*it)->addParticle(id,name);
		}
		break;
	case UNITTYPE_LEADER:
		re |= mCommanderUnit->addParticle(id,name);
		break;
	case UNITTYPE_SOLIDER:
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			re |= (*it)->addParticle(id,name);
		}
		break;
	}
	return re;
}
void SquadGraphics::startParticle(std::string id)
{
	mCommanderUnit->startParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->startParticle(id);
	}
}
void SquadGraphics::stopParticle(std::string id)
{
	mCommanderUnit->stopParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->stopParticle(id);
	}
}
void SquadGraphics::delParticle(std::string id)
{
	mCommanderUnit->delParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->delParticle(id);
	}
}
void SquadGraphics::combatPosition(Direction d)
{
	mIdleDirection=mDirection;

	Ogre::Vector3 offestVector;

	switch(d)
	{
	case North:
		{
			offestVector=Ogre::Vector3(0,0,-COMBAT_POSITION);
			break;
		}
	case South:
		{
			offestVector=Ogre::Vector3(0,0,COMBAT_POSITION);
			break;
		}
	case West:
		{
			offestVector=Ogre::Vector3(-COMBAT_POSITION,0,0);
			break;
		}
	case East:
		{
			offestVector=Ogre::Vector3(COMBAT_POSITION,0,0);
			break;
		}
	}

	changeUnitPosition(d,offestVector);

}

void SquadGraphics::idlePosition()
{
	mIdleDirection=mDirection;

	changeUnitPosition(mIdleDirection,Ogre::Vector3(0,0,0));
}

void SquadGraphics::changeUnitPosition( Direction d,Ogre::Vector3 offsetVector )
{
	//取得位置
	Ogre::Quaternion q;

	switch(d)
	{
	case North:
		{
			q.FromAngleAxis(Ogre::Degree(180),Ogre::Vector3(0,1,0));
			break;
		}
	case South:
		{
			q.FromAngleAxis(Ogre::Degree(360),Ogre::Vector3(0,1,0));
			break;
		}
	case West:
		{
			q.FromAngleAxis(Ogre::Degree(270),Ogre::Vector3(0,1,0));
			break;
		}
	case East:
		{
			q.FromAngleAxis(Ogre::Degree(90),Ogre::Vector3(0,1,0));
			break;
		}
	}

	Ogre::Vector3 commandVector;
	Ogre::Vector3 soldierVector[4];
	getFormationPosition(mFormation,d,commandVector,soldierVector);

	std::map<int,Ogre::Vector3> commandVectors;
	std::map<int,Ogre::Quaternion> quaternions;
	commandVectors[0]=mNode->getPosition()+commandVector+offsetVector;
	quaternions[0]=q;
	mCommanderUnit->mOffsetX=commandVector.x;
	mCommanderUnit->mOffsetY=commandVector.z;

	//设置移动
	mCommanderUnit->setMovePath(commandVectors,quaternions,0.5);

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		std::map<int,Ogre::Vector3> vectors;
		(*it)->mOffsetX=soldierVector[(*it)->mFormationPosition].x;
		(*it)->mOffsetY=soldierVector[(*it)->mFormationPosition].z;
		vectors[0]=mNode->getPosition()+soldierVector[(*it)->mFormationPosition]+offsetVector;
		(*it)->setMovePath(vectors,quaternions,0.5);
	}
}

Ogre::Vector3 SquadGraphics::getLeaderPosition()
{
	return mCommanderUnit->mNode->getPosition();
}

std::vector<Ogre::Vector3> SquadGraphics::getSoiderPosition()
{
	std::vector<Ogre::Vector3> posvec;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		posvec.push_back((*it)->mNode->getPosition());
	}
	return posvec;
}

void SquadGraphics::showValue( std::string value,Ogre::ColourValue c )
{
	mSquadValueBB->setValue(value,MyGUI::Colour(c.r,c.g,c.b));
}

void SquadGraphics::stopShowValue()
{
	mSquadValueBB->stopShow();
}	
