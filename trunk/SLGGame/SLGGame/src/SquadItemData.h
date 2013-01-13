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
		  mResourceImage("")
	  {
		  mSquadType=squadType;
		  std::string type;
		  switch(squadType)
		  {
		  case SQUADTYPE_LightInf:
			  {
				 mResourceImage="kind_lightinf";
				 break;
			  }
		  case SQUADTYPE_HeavyInf:
			  {
				  mResourceImage="kind_heavyinf";
				  break;
			  }
		  case SQUADTYPE_Saint:
			  {
				  mResourceImage="kind_mage";
				  break;
			  }
		  case SQUADTYPE_Bowman:
			  {
				  mResourceImage="kind_lightinf";
				  break;
			  }
		  }
	  }

	  void clear()
	  {
		  mResourceInfo = nullptr;
		  mResourceImage = "";
		  mSquadType=0;
		  mSquadName="";
		  mLevel=0;
	  }

	  demo::ResourceItemInfoPtr getInfo() const
	  {
		  return mResourceInfo;
	  }

	  std::string getImage() const
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
	std::string mResourceImage;
};

#endif // __ITEM_DATA_H__
