/*!
@file
@author		Albert Semenov
@date		07/2008
*/
#include "Precompiled.h"
#include "DeployCellView.h"

void DeployCellView::getCellDimension(MyGUI::Widget* _sender, MyGUI::IntCoord& _coord, bool _drop)
{
	if (_drop)
		_coord.set(0, 0,230, 50);
	else
		_coord.set(0, 0,230, 50);
}

DeployCellView::DeployCellView(MyGUI::Widget* _parent) :
wraps::BaseCellView<DeployItemData*>("DeployCellView.layout", _parent)
{
	assignWidget(mImageBack, "image_Back");
	assignWidget(mImageBorder, "image_Border");
	assignWidget(mImageItem, "image_Item");
	assignWidget(mTextBack, "text_Back");
	assignWidget(mTextFront, "text_Front");
}

void DeployCellView::update(const MyGUI::IBDrawItemInfo& _info, DeployItemData* _data)
{
	if (_info.update)
	{
		if (!_data->isEmpty())
		{
			mImageItem->setItemResource("kind");
			mImageItem->setItemGroup(_data->getImage());
			mImageItem->setVisible(true);
		}
		else
		{
			mImageItem->setVisible(false);
		}
		mTextBack->setCaption(_data->getDeployState());
		mTextFront->setCaption(_data->getSquadName());

	/*	static MyGUI::ResourceImageSetPtr resource_back = nullptr;
		static MyGUI::ResourceImageSetPtr resource_select = nullptr;
		if (resource_back == nullptr)
			resource_back = MyGUI::ResourceManager::getInstance().getByName("pic_ItemBackImage")->castType<MyGUI::ResourceImageSet>();
		if (resource_select == nullptr)
			resource_select = MyGUI::ResourceManager::getInstance().getByName("pic_ItemSelectImage")->castType<MyGUI::ResourceImageSet>();*/

		mImageBack->setItemResource("button");
		mImageBack->setItemGroup("squad_skin");
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
	//}
}