#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include "squaddefine.h"

namespace demo
{

	class ItemData
	{
	public:
		ItemData() :
			mID(""),
			mResourceInfo(nullptr),
			mResourceImage(nullptr)
		{
		}

		ItemData(int type,const std::string& id) :
			mType(type),
			mID(id),
			mResourceInfo(nullptr),
			mResourceImage(nullptr)
		{
			MyGUI::ResourceManager& manager = MyGUI::ResourceManager::getInstance();
			//mResourceInfo = manager.getByName(_resource)->castType<demo::ResourceItemInfo>();
			mResourceImage = manager.getByName(mID)->castType<MyGUI::ResourceImageSet>();
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
			if(!mIsEquip)
			{
				int price=getPriceValue();
				int money=0;
				DataLibrary::getSingletonPtr()->getData("GameData/StoryData/Money",money);
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

		std::string getID()
		{
			return mID;
		}

		void setEquip(bool isEquip)
		{
			mIsEquip=isEquip;
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
			return price;
		}

	private:

		std::string mID;
		std::string mTypeString;
		int mType;
		bool mIsEquip;
		bool mIsCanBuy;
		demo::ResourceItemInfoPtr mResourceInfo;
		MyGUI::ResourceImageSetPtr mResourceImage;
	};

} // namespace demo

#endif // __ITEM_DATA_H__
