/*!
	@file
	@author		Albert Semenov
	@date		07/2008
*/
#include "Precompiled.h"
#include "DeployItemBox.h"


DeployItemBox::DeployItemBox(MyGUI::Widget* _parent) :
	wraps::BaseItemBox<DeployCellView>(_parent)
{
}

DeployItemBox::~DeployItemBox()
{
	MyGUI::ItemBox* box = getItemBox();
	size_t count = box->getItemCount();
	for (size_t pos = 0; pos < count; ++pos)
	{
		delete *box->getItemDataAt<DeployItemData*>(pos);
	}
}
