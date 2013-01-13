/*!
@file
@author		Albert Semenov
@date		07/2008
*/
#include "Precompiled.h"
#include "WeaponCellView.h"

void WeaponCellView::getCellDimension(MyGUI::Widget* _sender, MyGUI::IntCoord& _coord, bool _drop)
{
	if (_drop)
		_coord.set(0, 0,230, 50);
	else
		_coord.set(0, 0,230, 50);
}

WeaponCellView::WeaponCellView(MyGUI::Widget* _parent) :
wraps::BaseCellView<WeaponItemData*>("CellView.layout", _parent)
{
	assignWidget(mImageBack, "image_Back");
	assignWidget(mImageBorder, "image_Border");
	assignWidget(mImageItem, "image_Item");
	assignWidget(mTextBack, "text_Back");
	assignWidget(mTextFront, "text_Front");
}

void WeaponCellView::update(const MyGUI::IBDrawItemInfo& _info, WeaponItemData* _data)
{
	if (_info.update)
	{
		if (!_data->isEmpty())
		{
			mImageItem->setItemResource("eqp");
			mImageItem->setItemGroup(_data->getImage());
			mImageItem->setVisible(true);
		}
		else
		{
			mImageItem->setVisible(false);
		}
		mTextBack->setCaption(_data->getPrice());
		mTextFront->setCaption(_data->getName());

	/*	static MyGUI::ResourceImageSetPtr resource_back = nullptr;
		static MyGUI::ResourceImageSetPtr resource_select = nullptr;
		if (resource_back == nullptr)
			resource_back = MyGUI::ResourceManager::getInstance().getByName("pic_ItemBackImage")->castType<MyGUI::ResourceImageSet>();
		if (resource_select == nullptr)
			resource_select = MyGUI::ResourceManager::getInstance().getByName("pic_ItemSelectImage")->castType<MyGUI::ResourceImageSet>();*/

		mImageBack->setItemResource("button");
		mImageBack->setItemGroup("item_skin");
		//mImageBorder->setItemResourcePtr(resource_select);
		//mImageBorder->setItemGroup("States");
	}

	/*if (_info.drag)
	{
		mImageBack->setItemName("None");
		mImageBorder->setItemName("None");

		if (!_data->isEmpty())
		{
			if (_info.drop_refuse)
				mImageItem->setItemName("Refuse");
			else if (_info.drop_accept)
				mImageItem->setItemName("Accept");
			else
				mImageItem->setItemName("Normal");
			mImageItem->setVisible(true);
		}
		else
		{
			mImageItem->setVisible(false);
		}
	}
	else
	{
	*/
		if (_info.active)
		{
			if (_info.select)
				mImageBack->setItemName("highlighted");
			else
				mImageBack->setItemName("highlighted");
		}
		else if (_info.select)
			mImageBack->setItemName("highlighted");
		else
			mImageBack->setItemName("normal");
/*
		if (_info.drop_refuse)
		{
			mImageBorder->setItemName("Refuse");
			mTextFront->setTextColour(MyGUI::Colour::Red);
		}
		else if (_info.drop_accept)
		{
			mImageBorder->setItemName("Accept");
			mTextFront->setTextColour(MyGUI::Colour::Green);
		}
		else*/
		{
			//mImageBorder->setItemName("normal");
			mTextFront->setTextColour(MyGUI::Colour::White);
		}

		if (!_data->isEmpty())
		{
			mImageItem->setItemName("normal");
			mImageItem->setVisible(true);
		}
		else
		{
			mImageItem->setVisible(false);
		}
}