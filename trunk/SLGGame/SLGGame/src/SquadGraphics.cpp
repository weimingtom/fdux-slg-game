#include "SquadGraphics.h"

#include <stdlib.h>
#include <set>
#include <time.h>
#include <boost/format.hpp>

#include "Core.h"
#include "DataLibrary.h"

#include "UnitGrap.h"
#include "AnimationBlender.h"
#include "BillboardManager.h"
#include "GUISquadBillBoard.h"
#include "GUISquadValueBillBoard.h"
#include "AudioSystem.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"

#include "Terrain.h"

const Ogre::Vector3 LineVector[5]={Ogre::Vector3(0,0,6),Ogre::Vector3(-6,0,6),Ogre::Vector3(6,0,6),Ogre::Vector3(3,0,-3),Ogre::Vector3(-3,0,-3)};
const Ogre::Vector3 CircularVector[5]={Ogre::Vector3(0,0,5),Ogre::Vector3(-5,0,1),Ogre::Vector3(5,0,2),Ogre::Vector3(4,0,-4),Ogre::Vector3(-4,0,-4)};
const Ogre::Vector3 LooseVector[5]={Ogre::Vector3(0,0,0),Ogre::Vector3(-5,0,5),Ogre::Vector3(5,0,5),Ogre::Vector3(5,0,-5),Ogre::Vector3(-5,0,-5)};

#define FORMATION_KEYFRAME_TIME 0.5
#define RELIEF_MOVE_TIME 1
#define COMBAT_POSITION 5

SquadGraphics::SquadGraphics(std::string squadid, std::string datapath, int gridx, int gridy, int direction, int formation, int soldierCount)
:mNextDirection(-1),
mNodeAnimation(NULL),
mNodeAnimationState(NULL),
mSoldierIndex(0),
mFormation(formation),
mDirection(direction)
{
	mSceneMgr=Core::getSingletonPtr()->mSceneMgr;
	mNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(squadid);

	//获取数据

	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string leaderid;
	datalib->getData(datapath + std::string("/LeaderId"),leaderid);
	datalib->getData( std::string("StaticData/LeaderDate/") + leaderid + std::string("/Mesh"), mLeaderMesh);
	datalib->getData( std::string("StaticData/LeaderDate/") + leaderid + std::string("/Mat"), mLeaderMat);

	datalib->getData(datapath + std::string("/UnitMesh"),mSoilderMesh);
	datalib->getData(datapath + std::string("/UnitMat"),mSoilderMat);
	datalib->getData(datapath + std::string("/MoveSound"),mMoveSound);


	std::string tempid;
	mSoilderHaveWeapon=1;
	datalib->getData(datapath + std::string("/PweaponId"),tempid);
	if(tempid != "none")
	{
		mPWeaponID = tempid;
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/Mesh"), mPWeaponMesh);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/Mat"), mPWeaponMat);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/PU"), mPWeaponPU);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/PUVector"), mPWeaponPUVector);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/AniGroup"), mPWeaponAniGroup);
		datalib->getData( std::string("StaticData/PweaponData/") + tempid + std::string("/SoilderHaveWeapon"), mSoilderHaveWeapon);
	}
	else
	{
		mPWeaponID="none";
		mPWeaponMesh = "none";
		mPWeaponMat = "none";
		mPWeaponAniGroup = "1H1";
		mPWeaponPU="none";
	}
	datalib->getData(datapath + std::string("/SweaponId"),tempid);
	if(tempid != "none")
	{
		mSWeaponID = tempid;
		int sweapontype;
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Type"), sweapontype);
		mSWeaponBow = (sweapontype == EQUIP_SWEAPON_BOW);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Mesh"), mSWeaponMesh);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/Mat"), mSWeaponMat);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/PU"), mSWeaponPU);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/PUVector"), mSWeaponPUVector);
		datalib->getData( std::string("StaticData/SweaponData/") + tempid + std::string("/AniGroup"), mSWeaponAniGroup);
	}
	else
	{
		mSWeaponID = "none";
		mSWeaponBow = false;
		mSWeaponMesh = "none";
		mSWeaponMat = "none";
		mSWeaponAniGroup = "bow";
		mSWeaponPU="none";
	}
	datalib->getData(datapath + std::string("/ShieldId"),tempid);
	if(tempid != "none")
	{
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/Mesh"), mShieldMesh);
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/Mat"), mShieldMat);
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/PU"), mShieldPU);
		datalib->getData( std::string("StaticData/ShieldData/") + tempid + std::string("/PUVector"), mShieldVector);
	}
	else
	{
		mShieldMesh = "none";
		mShieldMat = "none";
		mShieldPU="none";
	}

	datalib->getData(datapath + std::string("/HorseId"),tempid);
	if(tempid != "none")
	{
		datalib->getData( std::string("StaticData/HorseData/") + tempid + std::string("/Mesh"), mHorseMesh);
		datalib->getData( std::string("StaticData/HorseData/") + tempid + std::string("/Mat"), mHorseMat);		
	}
	else
	{
		mHorseMesh="none";
		mHorseMat="none";
	}

	int team = 0;
	datalib->getData(datapath + std::string("/Team"),team);
	datalib->getData(str(boost::format("GameData/BattleData/Team/Team%1%/FactionId")%team), tempid);
	datalib->getData(str(boost::format("StaticData/FactionData/%1%/Texture")%tempid), mFactionTexture);
//	datalib->getData(datapath + std::string("/TeamId"),tempid);
// 	datalib->getData( std::string("GameData/BattleData/Team/") + tempid + std::string("/FactionId"), tempid);
// 	datalib->getData( std::string("StaticData/FactionData/") + tempid + std::string("/Texture"), mFactionTexture);


	//组建单位队伍与组建武器
	mCommanderUnit=new UnitGrap(mLeaderMesh,mLeaderMat,mHorseMesh,mHorseMat,mFactionTexture,mSceneMgr->getRootSceneNode()->createChildSceneNode(mNode->getName()+"_Commander"));
	mCommanderUnit->createWeapon(mPWeaponMesh,mPWeaponMat,mPWeaponPU,mPWeaponPUVector,UnitGrap::MainWepon);
	mCommanderUnit->createWeapon(mSWeaponMesh,mSWeaponMat,mSWeaponPU,mSWeaponPUVector,UnitGrap::SecWepon);
	mCommanderUnit->createWeapon(mShieldMesh,mShieldMat,mShieldPU,mSWeaponPUVector,UnitGrap::Shield);

	for (int i=0;i<soldierCount;i++)
	{
		createSoldier();
	}

	//设置指示器
	mSquadBB=new GUISquadBillBoard(mCommanderUnit->mNode);
	std::string name;
	int type = 0;
	datalib->getData(datapath + std::string("/Name"),name);
	datalib->getData(datapath + std::string("/SquadType"),type);

	datalib->getData(str(boost::format("GameData/BattleData/Team/Team%1%/Relation")%team), tempid);
	if (tempid=="player")
	{
		mSquadBB->setName(name,MyGUI::Colour::Blue,"p1.png","p2.png");
		mSquadBB->mHasApColor=MyGUI::Colour::Blue;
		mSquadBB->mNoneApColor=MyGUI::Colour(0,0,0.5);
	}
	else if (tempid=="enemy1" || tempid=="enemy2" ||tempid=="enemy3")
	{
		mSquadBB->setName(name,MyGUI::Colour::Red,"p1-1.png","p2-2.png");
		mSquadBB->mHasApColor=MyGUI::Colour::Red;
		mSquadBB->mNoneApColor=MyGUI::Colour(0.5,0,0);
	}
	else if (tempid=="alliance")
	{
		mSquadBB->setName(name,MyGUI::Colour(0.0143634,0.614035,0.0307607),"p1.png","p2.png");
		mSquadBB->mHasApColor=MyGUI::Colour(0.0143634,0.614035,0.0307607);
		mSquadBB->mNoneApColor=MyGUI::Colour(0,0.5,0);
	}
	else
	{
		mSquadBB->setName(name,MyGUI::Colour::Black,"p1.png","p2.png");
	}

	mSquadBB->setIcon(type);
	mSName=name;
	BillboardManager::getSingletonPtr()->addBillBoard(mSquadBB);

	mSquadValueBB=new GUISquadValueBillBoard(mNode);
	BillboardManager::getSingletonPtr()->addBillBoard(mSquadValueBB);

	//设置参数
	setGrid(gridx,gridy);
	setFormation(formation,false);
	setDirection(direction,false);
	if(mSWeaponMesh == "none")
		setWeaponMode(SquadGraphics::MainWepon);
	else
		setWeaponMode(SquadGraphics::SceWepon);

	updateBB();

	//读取现有效果
 	std::vector<std::string> particlelist = datalib->getChildList(datapath + std::string("/ParticleList"));
 	std::vector<std::string>::iterator ite;
 	for(ite = particlelist.begin(); ite != particlelist.end(); ite++)
 	{
 		int unittype;
 		datalib->getData(datapath + std::string("/ParticleList/")+ (*ite) +std::string("/AffectUnit"),unittype);
 		datalib->getData(datapath + std::string("/ParticleList/")+ (*ite) +std::string("/ParticleName"),tempid);
 		addParticle((*ite),tempid,unittype);
 		startParticle((*ite));
 	}
}

SquadGraphics::~SquadGraphics(void)
{
	if(mCommanderUnit!=NULL)
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
	UnitGrap* unit=new UnitGrap(mSoilderMesh,mSoilderMat,mHorseMesh,mHorseMat,mFactionTexture,mSceneMgr->getRootSceneNode()->createChildSceneNode(mNode->getName()+"_Soldier"+Ogre::StringConverter::toString(mSoldierIndex)));

	if(mSoilderHaveWeapon)
	{
		unit->createWeapon(mPWeaponMesh,mPWeaponMat,mPWeaponPU,mPWeaponPUVector,UnitGrap::MainWepon);
		unit->createWeapon(mSWeaponMesh,mSWeaponMat,mSWeaponPU,mSWeaponPUVector,UnitGrap::SecWepon);
		unit->createWeapon(mShieldMesh,mShieldMat,mShieldPU,mShieldVector,UnitGrap::Shield);
	}

	mSoldierUnits.push_back(unit);

	return unit;
}

void SquadGraphics::setMovePath(std::map<int,Ogre::Vector3>& vectors,std::map<int,Ogre::Quaternion>& quaternions,std::map<int,Direction>& directions)
{
	
	if (vectors.size()==0)
	{
		return;
	}

	setDirection(directions[0],false);
	mDirection=(directions.end().operator --())->second;

	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(mFormation,mDirection,CommanderVector,SoldierVector);

	std::map<int,Ogre::Vector3>* newVectors=getUnitMovePath(mCommanderUnit,vectors,directions,true);
	mCommanderUnit->setMovePath(*newVectors,quaternions,directions);
	mCommanderUnit->mOffsetX=CommanderVector.x;
	mCommanderUnit->mOffsetY=CommanderVector.z;
	delete newVectors;

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		newVectors=getUnitMovePath((*it),vectors,directions,false);
		(*it)->setMovePath(*newVectors,quaternions,directions);
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
	if (mCommanderUnit==NULL)
	{
		return true;
	}
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
	if (mNodeAnimationState!=NULL)
	{
		mSceneMgr->destroyAnimationState(mNodeAnimationState->getAnimationName());
		mNodeAnimationState=NULL;
		
	}
	
	if (mNodeAnimation!=NULL)
	{
		mSceneMgr->destroyAnimation(mNodeAnimation->getName());
		mNodeAnimation=NULL;
	}

	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->stopTransform();
	}
	if (mCommanderUnit!=NULL)
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
			if (mCommanderUnit!=NULL)
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
			if(mCommanderUnit!=NULL)
			{
				mCommanderUnit->mAniBlender->BackToInit();
				if (mCommanderUnit->mHorseAniBlender!=NULL)
				{
					mCommanderUnit->mHorseAniBlender->BackToInit();
				}
			}
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
				if ((*it)->mHorseAniBlender!=NULL)
				{
					(*it)->mHorseAniBlender->BackToInit();
				}
			}
			break;
		}
	}
}


bool SquadGraphics::isAnimationOver(UnitType object)
{
	if (mCommanderUnit==NULL)
	{
		return true;
	}

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

void SquadGraphics::getFormationPosition(int f,int d,Ogre::Vector3& CommanderVector,Ogre::Vector3 SoldierVector[])
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

	float w1,w2;
	switch(d)
	{
	case North:
		{
			w1=-1;
			w2=0;
			break;
		}
	case NorthEast:
		{
			w1=-0.707106;//cos -135
			w2=-0.707106;//sin -135
			break;
		}
	case South:
		{
			w1=1;
			w2=0;
			break;
		}
	case SouthWest:
		{
			w1=0.707106;
			w2=0.707106;
			break;
		}
	case West:
		{
			w1=0;
			w2=1;
			break;
		}
	case WestNorth:
		{
			w1=-0.707106;
			w2=0.707106;
			break;
		}
	case East:
		{
			w1=0;
			w2=-1;
			break;
		}
	case EastSouth:
		{
			w1=0.707106;
			w2=-0.707106;
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

void SquadGraphics::setFormation( int f,bool isAnim )
{
	if (mCommanderUnit==NULL)
	{
		return;
	}

	mFormation=f;
	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(f,mDirection,CommanderVector,SoldierVector);

	if (isAnim)
	{
		if(mSceneMgr->hasAnimation(mNode->getName()+"_Ani"))
		{
			mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
		}

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

		if(mSceneMgr->hasAnimationState(mNode->getName()+"_Ani"))
		{
			mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
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
		setGrid(mX,mY);
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
	mX=x;
	mY=y;
	float wx,wy=0;
	Terrain::getSingletonPtr()->getWorldCoords(x,y,wx,wy);
	
	mNode->setPosition(wx,0,wy);

	if (mCommanderUnit!=NULL)
	{
		mCommanderUnit->setPosition(wx,wy);
	}
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
	if (mCommanderUnit==NULL)
	{
		return;
	}

	if (isAnim)
	{
		if (d==mDirection)
		{
			return;
		}

		switch(d)//计算转180度的情况
		{
		case North:
			{
				if (mDirection==South)
				{
					mNextDirection=West;
				}
				break;
			}
		case South:
			{
				if (mDirection==North)
				{
					mNextDirection=East;
				}
				break;
			}
		case West:
			{
				if (mDirection==East)
				{
					mNextDirection=North;
				}
				break;
			}
		case East:
			{
				if (mDirection==West)
				{
					mNextDirection=South;
				}
				break;
			}
		}
	}

	mDirection=d;

	if (isAnim)
	{
		//设置移动
		if (mNextDirection!=-1)
		{
			changeUnitPosition(mNextDirection,Ogre::Vector3(0,0,0),true);
			mNextDirection=mDirection;
		}
		else
		{
			changeUnitPosition(mDirection,Ogre::Vector3(0,0,0),true);
		}
		

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
	}
	else
	{
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

		setGrid(mX,mY);
		mCommanderUnit->setPositionOffset(CommanderVector.x,CommanderVector.z);
		mCommanderUnit->mNode->setOrientation(q);

		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			(*it)->setPositionOffset(SoldierVector[(*it)->mFormationPosition].x,SoldierVector[(*it)->mFormationPosition].z);
			(*it)->mNode->setOrientation(q);
		}
	}

}

void SquadGraphics::setCheckUnitHeight( bool enable )
{
	if(mCommanderUnit!=NULL)
		mCommanderUnit->mIsCheckHeight=enable;
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->mIsCheckHeight=enable;
	}
}

void SquadGraphics::setWeaponMode( WeaponMode mode )
{
	if (mCommanderUnit==NULL)
	{
		return;
	}

	UnitGrap::WeaponType type;
	UnitGrap::BoneType bonetype;
	std::string anigroup;
	mWeapenMode=mode;
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

int SquadGraphics::getMainWeaponType()
{
	int type=0;
	if (mWeapenMode==MainWepon)
	{
		if(mPWeaponID=="none")
			return -1;
		DataLibrary::getSingletonPtr()->getData(std::string("StaticData/PweaponData/") + mPWeaponID + std::string("/Type"),type);
	}
	else
	{
		if(mSWeaponID=="none")
			return -1;
		DataLibrary::getSingletonPtr()->getData(std::string("StaticData/PweaponData/") + mSWeaponID + std::string("/Type"),type);
	}

	return type;

}

void SquadGraphics::setDeath(int num)
{
	if (mSoldierUnits.size()!=0)//还有士兵?
	{
		//随机选择
		if(num<mSoldierUnits.size())
		{
			std::set<int> s;
			while(1)
			{
				int r = rand()%mSoldierUnits.size();
				s.insert(r);
				if(s.size() == num)
				{
					break;
				}
			}
			
			UnitGrap* reliefUnit=NULL;
			for (std::set<int>::iterator it=s.begin();it!=s.end();it++)
			{
				reliefUnit=NULL;
				if (mSoldierUnits.at((*it))->mFormationPosition<2)//如果是前排?
				{
					int findF;//确定士兵队伍里面还有没有替补?
					if (mSoldierUnits.at((*it))->mFormationPosition==0)
					{
						if (s.find(3)==s.end())
						{
							findF=3;
						}
						else
						{
							findF=-1;
						}
					}
					else
					{						
						if (s.find(2)==s.end())
						{
							findF=2;
						}
						else
						{
							findF=-1;
						}
					}
					
					for (std::vector<UnitGrap*>::iterator itt=mSoldierUnits.begin();itt!=mSoldierUnits.end();itt++)
					{
						if ((*itt)->mFormationPosition==findF)
						{
							reliefUnit=(*itt);
						}
					}

					if (reliefUnit!=NULL)//如果找到了替补队员
					{
						reliefUnit->mFormationPosition=mSoldierUnits.at((*it))->mFormationPosition;
						reliefUnit->mOffsetX=mSoldierUnits.at((*it))->mOffsetX;
						reliefUnit->mOffsetY=mSoldierUnits.at((*it))->mOffsetY;
					}
				}
				
				

				mDeathUnits[mSoldierUnits.at((*it))]=reliefUnit;
			}

		}
		else
		{
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				mDeathUnits[(*it)]=NULL;
			}
		}

	}
	
	if (num>mSoldierUnits.size())
	{
		mSquadBB->setNode(NULL);
		mSquadBB->setVisible(false);
		if(mCommanderUnit!=NULL)
			mDeathUnits[mCommanderUnit]=NULL;
	}

	for (std::map<UnitGrap*,UnitGrap*>::iterator it=mDeathUnits.begin();it!=mDeathUnits.end();it++)
	{
		//执行死亡动画
		it->first->setAnimation(it->first->mDeathName,false,false);

		//移除单位
		for (std::vector<UnitGrap*>::iterator itt=mSoldierUnits.begin();itt!=mSoldierUnits.end();itt++)
		{
			if ((*itt)==it->first)
			{
				mSoldierUnits.erase(itt);
				break;
			}
		}

	}

	if(mDeathUnits.size()!=0)
		mDeathStep=playAni;

}

void SquadGraphics::doDeathStep()
{
	switch(mDeathStep)
	{
	case playAni:
		{
			//等待死亡动画结束

			if(mDeathUnits.begin()->second==NULL)
			{
				if (mDeathUnits.begin()->first->mIsAnimationComplete)
				{
					mDeathStep=moveUnit;
				}
			}
			else
			{
				mDeathStep=moveUnit;
			}

			break;
		}
	case moveUnit:
		{
			int i=0;
			if(mSceneMgr->hasAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i)))
			{
				mSceneMgr->destroyAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
			}

			if (mSceneMgr->hasAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i)))
			{
				mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
			}

			mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i), RELIEF_MOVE_TIME);
			mNodeAnimationState = mSceneMgr->createAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
			bool haveMove=false;
			for (std::map<UnitGrap*,UnitGrap*>::iterator it=mDeathUnits.begin();it!=mDeathUnits.end();it++)
			{
				if (it->second!=NULL)
				{
					haveMove=true;
					//设置节点动画
					mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
					Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(i, it->second->mNode);

					Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
					kf->setTranslate( it->second->mNode->getPosition());
					kf->setRotation( it->second->mNode->getOrientation());
					kf->setScale(it->second->mNode->getScale());

					kf = track->createNodeKeyFrame(RELIEF_MOVE_TIME);
					kf->setTranslate(it->first->mNode->getPosition());
					kf->setRotation(it->second->mNode->getOrientation());
					kf->setScale( it->second->mNode->getScale());

					

					//setCheckUnitHeight(true);


					mReturnInitAni=false;

					//设置跑步动画
					it->second->setAnimation(it->second->mWalkName,true,false);
					i++;
				}

			}

			if(!haveMove)
			{
				mSceneMgr->destroyAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
				mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
				mNodeAnimation=NULL;
				mNodeAnimationState=NULL;
			}
			else
			{
				mNodeAnimationState->setLoop(false);
				mNodeAnimationState->setEnabled(true);
			}

			mDeathStep=resetAni;

			break;
		}
	case resetAni:
		{
			if (mNodeAnimation==NULL)
			{
				int i=0;
				for (std::map<UnitGrap*,UnitGrap*>::iterator it=mDeathUnits.begin();it!=mDeathUnits.end();it++)
				{
					if(it->second!=NULL)
					{
						//回复原来动画
						it->second->mAniBlender->BackToInit();
						if (it->second->mHorseAniBlender!=NULL)
						{
							it->second->mHorseAniBlender->BackToInit();
						}
					}

					if (it->first==mCommanderUnit)
					{
						mCommanderUnit=NULL;
					}

					delete it->first;
				}

				if(mSceneMgr->hasAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i)))
				{
					mSceneMgr->destroyAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
					mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
				}

				mDeathUnits.clear();
				
				
			}
			break;
		}
	}
}

void SquadGraphics::stopDeath()
{
	stopTransform();

	int i=0;

	for (std::map<UnitGrap*,UnitGrap*>::iterator it=mDeathUnits.begin();it!=mDeathUnits.end();it++)
	{
		if (it->second!=NULL)
		{
			it->second->mNode->setPosition(it->first->mNode->getPosition());
		}

		//移除单位
		for (std::vector<UnitGrap*>::iterator itt=mSoldierUnits.begin();itt!=mSoldierUnits.end();itt++)
		{
			if ((*itt)==it->first)
			{
				mSoldierUnits.erase(itt);
				break;
			}
		}

		if (it->first==mCommanderUnit)
		{
			mCommanderUnit=NULL;
		}

		delete it->first;
		if(mSceneMgr->hasAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i)))
		{
			mSceneMgr->destroyAnimation(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
			mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani"+Ogre::StringConverter::toString(i));
		}
		i++;
	}

	mDeathUnits.clear();
}

bool SquadGraphics::isDeathOver()
{
	if (mDeathUnits.size()!=0)
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
	for (std::vector<UnitGrap*>::iterator it=mRecoverUnits.begin();it!=mRecoverUnits.end();it++)
	{
		if(!(*it)->mIsAnimationComplete)
		{
			over=false;
			break;
		}
	}
	if(over)
	{
		setWeaponMode(mWeapenMode);
		mRecoverUnits.clear();
	}

	return over;
}

void SquadGraphics::setRecover(int num)
{
	updateBB();
	int size=mSoldierUnits.size();
	if (mSoldierUnits.size()+num<5)
	{
		for (int i=0;i<num;i++)
		{
			int findIndex=0;
			
			for (int j=0;j<mSoldierUnits.size()+1;j++)
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

			unit->setAnimation(unit->mRecoverName,false,true);
			mRecoverUnits.push_back(unit);

		}
	}
	setGrid(mX,mY);
	setDirection(mDirection,false);
}

bool SquadGraphics::isDirectionOver()
{
	return mNextDirection==-1 && mNodeAnimationState==NULL;
}

void SquadGraphics::update( unsigned int deltaTime )
{
	if (mDeathUnits.size()!=0)
	{
		doDeathStep();
	}
	
	if (mNextDirection!=-1 && isFormationOrDirectionOver())
	{
		stopTransform();
		changeUnitPosition(mNextDirection,Ogre::Vector3(0,0,0),true);
		mNextDirection=-1;
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

	for (std::map<UnitGrap*,UnitGrap*>::iterator itt=mDeathUnits.begin();itt!=mDeathUnits.end();itt++)
	{
		itt->first->update(deltaTime);
	}
}

void SquadGraphics::setVisible(bool visible)
{
	if(mCommanderUnit!=NULL)
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
	if (mCommanderUnit!=NULL)
	{
		mCommanderUnit->setParticleVisible(visible);
	}
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->setParticleVisible(visible);
	}
}

bool SquadGraphics::addParticle(std::string id,std::string name,int object)
{
	bool re = false;
	switch(object)
	{
	case UNITTYPE_ALL:
		if (mCommanderUnit!=NULL)
		{
			re |= mCommanderUnit->addParticle(id,name);
		}
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			re |= (*it)->addParticle(id,name);
		}
		break;
	case UNITTYPE_LEADER:
		if (mCommanderUnit!=NULL)
		{
			re |= mCommanderUnit->addParticle(id,name);
		}
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
	updateBB();
	if(mCommanderUnit!=NULL)
		mCommanderUnit->startParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->startParticle(id);
	}
}
void SquadGraphics::stopParticle(std::string id)
{
	if(mCommanderUnit!=NULL)
		mCommanderUnit->stopParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->stopParticle(id);
	}
}
void SquadGraphics::delParticle(std::string id)
{
	if(mCommanderUnit!=NULL)
		mCommanderUnit->delParticle(id);
	for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
	{
		(*it)->delParticle(id);
	}
}
void SquadGraphics::combatPosition(Direction d,bool isAnim)
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

	changeUnitPosition(d,offestVector,isAnim);

}

void SquadGraphics::idlePosition(bool isAnim)
{
	mIdleDirection=mDirection;

	changeUnitPosition(mIdleDirection,Ogre::Vector3(0,0,0),isAnim);
}

void SquadGraphics::changeUnitPosition( Direction d,Ogre::Vector3 offsetVector,bool isAnim)
{
	if (mCommanderUnit==NULL)
	{
		return;
	}

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

	Ogre::Vector3 CommanderVector;
	Ogre::Vector3 SoldierVector[4];

	getFormationPosition(mFormation,d,CommanderVector,SoldierVector);

	if (isAnim)
	{
		if (mSceneMgr->hasAnimation(mNode->getName()+"_Ani"))
		{
			mSceneMgr->destroyAnimation(mNode->getName()+"_Ani");
		}
		mNodeAnimation = mSceneMgr->createAnimation(mNode->getName()+"_Ani",FORMATION_KEYFRAME_TIME);
		mNodeAnimation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
		Ogre::NodeAnimationTrack* track = mNodeAnimation->createNodeTrack(0,mCommanderUnit->mNode);

		Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
		kf->setTranslate(mCommanderUnit->mNode->getPosition());
		kf->setRotation(mCommanderUnit->mNode->getOrientation());
		kf->setScale(mCommanderUnit->mNode->getScale());

		kf=track->createNodeKeyFrame(FORMATION_KEYFRAME_TIME);
		Ogre::Vector3 v=CommanderVector;
		mCommanderUnit->mOffsetX=v.x;
		mCommanderUnit->mOffsetY=v.z;
		Ogre::Vector3 np=mNode->getPosition();
		v+=np;
		v.y=Terrain::getSingletonPtr()->getHeight(v.x,v.z);
		kf->setTranslate(v);
		kf->setRotation(q);
		kf->setScale(mCommanderUnit->mNode->getScale());

		int i=0;
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			track = mNodeAnimation->createNodeTrack(i+1,(*it)->mNode);

			Ogre::TransformKeyFrame* kf = track->createNodeKeyFrame(0);
			kf->setTranslate((*it)->mNode->getPosition());
			kf->setRotation((*it)->mNode->getOrientation());
			kf->setScale((*it)->mNode->getScale());
			v=SoldierVector[i];
			(*it)->mOffsetX=v.x;
			(*it)->mOffsetY=v.z;
			v+=mNode->getPosition();
			v.y=Terrain::getSingletonPtr()->getHeight(v.x,v.z);

			kf=track->createNodeKeyFrame(FORMATION_KEYFRAME_TIME);
			kf->setTranslate(v);
			kf->setRotation(q);
			kf->setScale((*it)->mNode->getScale());
			(*it)->mFormationPosition=i;
			i++;
		}

		if (mSceneMgr->hasAnimationState(mNode->getName()+"_Ani"))
		{
			mSceneMgr->destroyAnimationState(mNode->getName()+"_Ani");
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

}

Ogre::Vector3 SquadGraphics::getLeaderPosition()
{
	if(mCommanderUnit->mNode!=NULL)
		return mCommanderUnit->mNode->getPosition();
	else
		return Ogre::Vector3(0,0,0);
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
	updateBB();
	mSquadValueBB->setValue(value,MyGUI::Colour(c.r,c.g,c.b));
}

void SquadGraphics::stopShowValue()
{
	mSquadValueBB->stopShow();
}	

void SquadGraphics::defenseAction( SquadGraphics* enemy,bool isMove )
{
	//检查进攻方人数,选出防御方合适的人数进行动作

	std::vector<UnitGrap*> defenseUnit;

	if (mCommanderUnit!=NULL)
	{
		defenseUnit.push_back(mCommanderUnit);
	}

	if (enemy->mSoldierUnits.size()+1<mSoldierUnits.size()+1)//如果进攻方数量小于防御方,则需要选择,否则不用
	{

		if (enemy->mSoldierUnits.size()+1<=3)//从前排选出
		{
			if(enemy->mSoldierUnits.size()!=0)//只剩指挥官?
			{
				int i=0;
				for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
				{
					if (i!=enemy->mSoldierUnits.size())
					{
						if ((*it)->mFormationPosition<2)
						{
							defenseUnit.push_back((*it));
							i++;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			int i=0;
			for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
			{
				if (i!=enemy->mSoldierUnits.size())
				{
					defenseUnit.push_back((*it));
					i++;
				}
				else
				{
					break;
				}
			}
		}
	}
	else
	{
		for (std::vector<UnitGrap*>::iterator it=mSoldierUnits.begin();it!=mSoldierUnits.end();it++)
		{
			defenseUnit.push_back((*it));
		}
	}

	//执行动作

	for (std::vector<UnitGrap*>::iterator it=defenseUnit.begin();it!=defenseUnit.end();it++)
	{
		//设置火花粒子

		(*it)->playWeaponParticle(UnitGrap::Shield,"mp_metal_hit");
		
		//设置自身粒子

		(*it)->addParticle("9999","Hit/mp_hit_01");
		(*it)->startParticle("9999",true);
	}
}

bool SquadGraphics::isDefenseActionOver()
{
	if (mCommanderUnit==NULL)
	{
		return false;
	}

	if (mCommanderUnit->mIsPUEnd)
	{
		mCommanderUnit->mIsPUEnd=false;
		return true;
	}
	else
	{
		return false;
	}
}

void SquadGraphics::updateBB()
{
	BattleSquad* squad=BattleSquadManager::getSingletonPtr()->getBattleSquad(mNode->getName());
	float v;
	float v1;
	if(squad->getType()==0)
	{
		v=((float)squad->getUnitNum())/50.0f;
		v1=((float)squad->getUnitMaxNum())/50.f;
	}
	else
	{
		v=((float)squad->getUnitNum())/20.0f;
		v1=v;
	}
	mSquadBB->setBar(v,v1);
}


