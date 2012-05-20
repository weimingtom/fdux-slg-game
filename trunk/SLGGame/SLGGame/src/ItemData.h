#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include "ResourceItemInfo.h"
#include "MyGUI_ResourceManager.h"

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

		ItemData(const std::string& id) :
			mID(id),
			mResourceInfo(nullptr),
			mResourceImage(nullptr)
		{
			//MyGUI::ResourceManager& manager = MyGUI::ResourceManager::getInstance();
			//mResourceInfo = manager.getByName(_resource)->castType<demo::ResourceItemInfo>();
			//mResourceImage = manager.getByName(mResourceInfo->getItemResourceImage())->castType<MyGUI::ResourceImageSet>();
		}

		bool isEmpty() const
		{
			return mResourceInfo == 0;
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

		}

		std::string getName()
		{

		}

	private:

		std::string mID;
		demo::ResourceItemInfoPtr mResourceInfo;
		MyGUI::ResourceImageSetPtr mResourceImage;
	};

} // namespace demo

#endif // __ITEM_DATA_H__
