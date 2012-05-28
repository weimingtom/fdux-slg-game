/*!
	@file
	@author		Albert Semenov
	@date		07/2008
*/
#include "Precompiled.h"
#include "SquadItemBox.h"


SquadItemBox::SquadItemBox(MyGUI::Widget* _parent) :
	wraps::BaseItemBox<SquadCellView>(_parent)
{
}

SquadItemBox::~SquadItemBox()
{
	MyGUI::ItemBox* box = getItemBox();
	size_t count = box->getItemCount();
	for (size_t pos = 0; pos < count; ++pos)
	{
		delete *box->getItemDataAt<SquadItemData*>(pos);
	}
}
