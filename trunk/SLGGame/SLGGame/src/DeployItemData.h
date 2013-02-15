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
		  case SQUADTYPE_MISSILEINFANTRY:
			  {
				  mResourceImage="kind_lightinf";
				  break;
			  }
		  case SQUADTYPE_INFANTRY:
			  {
				  mResourceImage="kind_heavyinf";
				  break;
			  }
		  case SQUADTYPE_CAVALRY:
			  {
				  mResourceImage="kind_heavyrid";
				  break;
			  }
		  case SQUADTYPE_MISSILECAVALRY:
			  {
				  mResourceImage="kind_lightrid";
				  break;
			  }
		  case SQUADTYPE_BATTLEMAGE:
			  {
				  mResourceImage="kind_warlock";
				  break;
			  }
		  case SQUADTYPE_ARCANEMAGE:
			  {
				  mResourceImage="kind_priest";
				  break;
			  }
		  case SQUADTYPE_SAINT:
			  {
				  mResourceImage="kind_mage";
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
