#ifndef __DeployITEM_DATA_H__
#define __DeployITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "squaddefine.h"

class DeployItemData
{
public:
	DeployItemData() :
		  mResourceInfo(nullptr),
		  mResourceImage(nullptr)
	  {
	  }

		  DeployItemData(int squadType,const std::string squadName,std::string deployState) :
		  mSquadType(squadType),
		  mSquadName(squadName),
		  mDeployState(deployState),
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
		  mDeployState="";
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

	  void setDeployState(std::string deployState)
	  {
			mDeployState=deployState;
	  }

	  std::string getDeployState()
	  {
		  return mDeployState;
	  }


private:

	int mSquadType;
	std::string mSquadName;
	int mLevel;
	std::string mDeployState;
	demo::ResourceItemInfoPtr mResourceInfo;
	std::string mResourceImage;
};

#endif // __ITEM_DATA_H__
