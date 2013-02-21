#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "squaddefine.h"

class WeaponItemData
{
public:
	WeaponItemData() :
	  mID(""),
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
	  }

	  WeaponItemData(int type,const std::string& id,int peopleNum) :
	  mType(type),
		  mID(id),
		  mPeopleNum(peopleNum),
		  mResourceInfo(nullptr),
		  mResourceImage(""),
		  mSubType(0)
	  {
		  mIsEquip=false;

		  switch(type)
		  {
		  case EQUIP_ARMOR:
			  mTypeString = "StaticData/ArmorData/";
			  break;
		  case EQUIP_HORSE:
			  mTypeString = "StaticData/HorseData/";
			  break;
		  case EQUIP_SOILDER:
			  mTypeString = "StaticData/SoilderData/";
			  break;
		  case EQUIP_SHIELD:
			  mTypeString = "StaticData/ShieldData/";
			  break;
		  case EQUIP_PWEAPON:
			  mTypeString = "StaticData/PweaponData/";
			  break;
		  case EQUIP_SWEAPON:
			  mTypeString = "StaticData/SweaponData/";
			  break;
		  case EQUIP_RETAINER:
			  mTypeString = "StaticData/RetainerData/";
			  break;
		  }
		
		  DataLibrary::getSingletonPtr()->getData(mTypeString+id+"/Icon",mResourceImage);
	  }

	  bool isEmpty() const
	  {
		  return false;
	  }

	  void clear()
	  {
		  mResourceInfo = nullptr;
		  mResourceImage = "";
		  mID="";
	  }

	  demo::ResourceItemInfoPtr getInfo() const
	  {
		  return mResourceInfo;
	  }

	  std::string getImage() const
	  {
		  return mResourceImage;
	  }

	  std::string getPrice()
	  {
		  if(!mIsHaveSkill)
		  {
			return "#C0C0C0"+StringTable::getSingleton().getString("NoSkillEquip");
		  }
		  else if(!mIsEquip)
		  {
			  int price=getPriceValue();
			  int money=0;
			  DataLibrary::getSingletonPtr()->getData("GameData/StoryData/Gold",money);
			  if(money-price<0)
			  {
				  mIsCanBuy=false;
				  return "#C0C0C0"+StringTable::getSingleton().getString("Price")+Ogre::StringConverter::toString(price)+StringTable::getSingleton().getString("NoEnoughMoney");
			  }
			  else
			  {
				  mIsCanBuy=true;
				  return "#FFFF00"+StringTable::getSingleton().getString("Price")+Ogre::StringConverter::toString(price);
			  }
		  }
		  else
		  {
			  return "#00FF00"+StringTable::getSingleton().getString("Equiped");
		  }
	  }

	  std::string getName()
	  {
		  std::string name;
		  DataLibrary::getSingletonPtr()->getData(mTypeString+mID+"/Name",name);
		  return name;
	  }

	  std::string getDescribe()
	  {
		  std::string des;
		  DataLibrary::getSingletonPtr()->getData(mTypeString+mID+"/Describe",des);
		  return des;
	  }

	  std::string getID()
	  {
		  return mID;
	  }

	  void setEquip(bool isEquip)
	  {
		  mIsEquip=isEquip;
	  }

	  bool getIsHaveSkill()
	  {
		  return mIsHaveSkill;
	  }

	  void setIsHaveSkill(bool skill)
	  {
		  mIsHaveSkill=skill;
	  }

	  bool getEquip()
	  {
		  return mIsEquip;
	  }

	  bool getCanBuy()
	  {
		  return mIsCanBuy;
	  }

	  int getType()
	  {
		  return mType;
	  }

	  int getPriceValue()
	  {
		  int price;
		  DataLibrary::getSingletonPtr()->getData(mTypeString+mID+"/Value",price);
		  return price*50;
	  }

	  int getOnePrice()
	  {
		  int price;
		  DataLibrary::getSingletonPtr()->getData(mTypeString+mID+"/Value",price);
		  return price;
	  }

	  void setSubType(int subType)
	  {
		  mSubType=subType;
	  }

	  int getSubType()
	  {
		  return mSubType;
	  }

private:

	std::string mID;
	std::string mTypeString;
	int mPeopleNum;
	int mType;
	int mSubType;
	bool mIsEquip;
	bool mIsHaveSkill;
	bool mIsCanBuy;
	demo::ResourceItemInfoPtr mResourceInfo;
	std::string mResourceImage;
};

#endif // __ITEM_DATA_H__
