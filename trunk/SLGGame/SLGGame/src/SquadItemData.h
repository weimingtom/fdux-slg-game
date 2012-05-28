#ifndef __SQUADITEM_DATA_H__
#define __SQUADITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "squaddefine.h"

class SquadItemData
{
public:
	SquadItemData() :
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
	  }

	  SquadItemData(int squadType,const std::string squadName,int level) :
		  mSquadType(squadType),
		  mSquadName(squadName),
		  mLevel(level),
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
		  mSquadType=squadType;
		  std::string type;
		  switch(squadType)
		  {
		  case SQUADTYPE_LightInf:
			  {
				 type="LightInfIcon_Supply";
				 break;
			  }
		  case SQUADTYPE_HeavyInf:
			  {
				  type="HeavyInfIcon_Supply";
				  break;
			  }
		  case SQUADTYPE_Saint:
			  {
				  type="SaintIcon_Supply";
				  break;
			  }
		  case SQUADTYPE_Bowman:
			  {
				  type="BowmanIcon_Supply";
				  break;
			  }
		  }

		  MyGUI::ResourceManager& manager = MyGUI::ResourceManager::getInstance();
		  mResourceImage = manager.getByName(type)->castType<MyGUI::ResourceImageSet>();
	  }

	  void clear()
	  {
		  mResourceInfo = nullptr;
		  mResourceImage = nullptr;
		  mSquadType=0;
		  mSquadName="";
		  mLevel=0;
	  }

	  demo::ResourceItemInfoPtr getInfo() const
	  {
		  return mResourceInfo;
	  }

	  MyGUI::ResourceImageSetPtr getImage() const
	  {
		  return mResourceImage;
	  }
		
	  bool isEmpty() const
	  {
		  return false;
	  }

	  std::string getSquadName()
	  {
		 return mSquadName;
	  }

	  std::string getLevel()
	  {
		  return "Lv."+Ogre::StringConverter::toString(mLevel);
	  }

private:

	int mSquadType;
	std::string mSquadName;
	int mLevel;
	demo::ResourceItemInfoPtr mResourceInfo;
	MyGUI::ResourceImageSetPtr mResourceImage;
};

#endif // __ITEM_DATA_H__
