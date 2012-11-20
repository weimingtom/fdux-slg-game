/*!
	@file
	@author		Albert Semenov
	@date		07/2008
*/
#include "Precompiled.h"
#include "SkillItemBox.h"


SkillItemBox::SkillItemBox(MyGUI::Widget* _parent) :
	wraps::BaseItemBox<SkillCellView>(_parent)
{
}

SkillItemBox::~SkillItemBox()
{
	MyGUI::ItemBox* box = getItemBox();
	size_t count = box->getItemCount();
	for (size_t pos = 0; pos < count; ++pos)
	{
		delete *box->getItemDataAt<SkillItemData*>(pos);
	}
}
