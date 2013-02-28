#ifndef _SKILL_ITEM_DATA_H__
#define _SKILL_ITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "squaddefine.h"

class SkillItemData
{
public:
	SkillItemData() :
	  mType(0),
	  mID(""),
	  mName(""),
		  mLevel(0),
		  mNowLevel(0),
		  mTotalPoint(0),
		  mResourceInfo(nullptr),
		  mGroup("")
	  {
	  }

	  SkillItemData(int type,const std::string& id,int level,int NowLevel,std::string name,int totalPoint) :
	  mType(type),
		  mLevel(level),
		  mNowLevel(NowLevel),
		  mID(id),
		  mTotalPoint(totalPoint),
		  mName(name),
		  mResourceInfo(nullptr),
		  mGroup("")
	  {

		  switch(type)
		  {
		  case SKILLTYPE_PASSIVE:
			  mTypeString = "StaticData/EffectData/"+id;
			  DataLibrary::getSingletonPtr()->getData(mTypeString+"/Icon",mGroup);
			  mResoure="skillpass";
			  DataLibrary::getSingletonPtr()->getData(mTypeString+"/Name",mName);
			  break;
		  case SKILLTYPE_ACTIVE:
			  mTypeString = "StaticData/SkillData/"+id;
			  DataLibrary::getSingletonPtr()->getData(mTypeString+"/Icon",mGroup);
			  DataLibrary::getSingletonPtr()->getData(mTypeString+"/Name",mName);
			  mResoure="skill";
			  break;
		  case SKILLTYPE_EQUIP:
			  mTypeString = "";
			  mGroup=id;
			  if(id=="OneHandBlunt")
				  mGroup="eqp_oneaxe";
			  else if(id=="OneHandSword")
				  mGroup="OneHandSword";
			  else if(id=="TwoHandSword")
				  mGroup="eqp_twosword";
			  else if(id=="TwoHandBlunt")
				  mGroup="eqp_twoaxe";
			  else if(id=="ShortSpear")
				  mGroup="ShortSpear";
			  else if(id=="Long")
				  mGroup="eqp_halberd";
			  else if(id=="Shield")
				  mGroup="Shield";
			  else if(id=="LightArmor")
				  mGroup="eqp_lightarmor";
			  else if(id=="MiddleArmor")
				  mGroup="eqp_midarmor";
			  else if(id=="HeavyArmor")
				  mGroup="eqp_heavyarmor";
			  else if(id=="Bow")
				  mGroup="Bow";
			  else if(id=="XBow")
				  mGroup="LXBox";
			  else if(id=="LightHorse")
				  mGroup="eqp_lighthorse";
			  else if(id=="HeavyHorse")
				  mGroup="eqp_heavyhorse";

			  mResoure="eqp";
			  mName=StringTable::getSingletonPtr()->getString(mName);
			  break;
		  }
	  }

	  bool isEmpty() const
	  {
		  return false;
	  }

	  void clear()
	  {
		  mResourceInfo = nullptr;
		  mGroup = "";
		  mID="";
		  mType=0;
		  mTypeString="";
		  mIsCanTrain=false;
		  mLevel=0;
		  mNowLevel=0;
	  }

	  demo::ResourceItemInfoPtr getInfo() const
	  {
		  return mResourceInfo;
	  }

	  std::string getResoure() const
	  {
		  return mResoure;
	  }

	  std::string getImage() const
	  {
		  return mGroup;
	  }

	  std::string getPrice()
	  {
		  if(mIsCanTrain)
		  {
			  if(mNowLevel>=mLevel)
			  {
				  if(mTotalPoint-1<0)
				  {
					  mIsHaveEnoughPoint=false;
					  return "#C0C0C0"+StringTable::getSingleton().getString("NoEnoughPoint");
				  }
				  else
				  {
					  mIsHaveEnoughPoint=true;
					  return "#FFFF00"+StringTable::getSingleton().getString("CanTraine");
				  }
			  }
			  else
			  {
					mIsHaveEnoughPoint=false;
					return "#C0C0C0"+StringTable::getSingleton().getString("NoEnoughLevel")+Ogre::StringConverter::toString(mLevel);
			  }

		  }
		  else
		  {
			  return "#00FF00"+StringTable::getSingleton().getString("Trained");
		  }
	  }

	  std::string getDescribe()
	  {
		  std::string des;
		  DataLibrary::getSingletonPtr()->getData(mTypeString+"/Describe",des);
		  return des;
	  }

	  std::string getName()
	  {
		  return mName;
	  }

	  std::string getID()
	  {
		  return mID;
	  }

	  bool getCanTrain()
	  {
		  return mIsCanTrain;
	  }

	  void setCanTrain(bool train)
	  {
		  mIsCanTrain=train;
	  }

	  int getType()
	  {
		  return mType;
	  }

	  int getLevel()
	  {
		return mLevel;
	  }

	  bool getHaveEnoughPoint()
	  {
		  return mIsHaveEnoughPoint;
	  }

private:

	std::string mID;
	std::string mName;
	int mType;
	int mLevel;
	int mNowLevel;
	int mTotalPoint;
	std::string mTypeString;
	bool mIsCanTrain;
	bool mIsHaveEnoughPoint;
	demo::ResourceItemInfoPtr mResourceInfo;
	std::string mResoure;
	std::string mGroup;
};

#endif // __ITEM_DATA_H__
