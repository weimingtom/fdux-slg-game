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
		  mPoint(0),
		  mTotalPoint(0),
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
	  }

	  SkillItemData(int type,const std::string& id,int point,std::string name,int totalPoint) :
	  mType(type),
		  mPoint(point),
		  mID(id),
		  mTotalPoint(totalPoint),
		  mName(name),
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
		  MyGUI::ResourceManager& manager = MyGUI::ResourceManager::getInstance();

		  if(manager.getByName(mID,false)!=nullptr)
			 mResourceImage = manager.getByName(mID,false)->castType<MyGUI::ResourceImageSet>();
		  else
			mResourceImage = manager.getByName("NULLICON",false)->castType<MyGUI::ResourceImageSet>();

		  switch(type)
		  {
		  case SKILLTYPE_PASSIVE:
			  mTypeString = "StaticData/EffectData/"+id;
			  break;
		  case SKILLTYPE_ACTIVE:
			  mTypeString = "StaticData/SkillData/"+id;
			  break;
		  case SKILLTYPE_EQUIP:
			  mTypeString = "";
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
		  mResourceImage = nullptr;
		  mID="";
		  mType=0;
		  mTypeString="";
		  mIsCanTrain=false;
		  mPoint=0;
	  }

	  demo::ResourceItemInfoPtr getInfo() const
	  {
		  return mResourceInfo;
	  }

	  MyGUI::ResourceImageSetPtr getImage() const
	  {
		  return mResourceImage;
	  }

	  std::string getPrice()
	  {
		  if(mIsCanTrain)
		  {
			  int point=getPoint();
			  if(mTotalPoint-point<0)
			  {
				  mIsHaveEnoughPoint=false;
				  return "#C0C0C0"+StringTable::getSingleton().getString("point")+Ogre::StringConverter::toString(point)+StringTable::getSingleton().getString("NoEnoughPoint");
			  }
			  else
			  {
				  mIsHaveEnoughPoint=true;
				  return "#FFFF00"+StringTable::getSingleton().getString("point")+Ogre::StringConverter::toString(point);
			  }
		  }
		  else
		  {
			  return "#00FF00"+StringTable::getSingleton().getString("Trained");
		  }
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

	  int getPoint()
	  {
		return mPoint;
	  }

	  bool getHaveEnoughPoint()
	  {
		  return mIsHaveEnoughPoint;
	  }

private:

	std::string mID;
	std::string mName;
	int mType;
	int mPoint;
	int mTotalPoint;
	std::string mTypeString;
	bool mIsCanTrain;
	bool mIsHaveEnoughPoint;
	demo::ResourceItemInfoPtr mResourceInfo;
	MyGUI::ResourceImageSetPtr mResourceImage;
};

#endif // __ITEM_DATA_H__
