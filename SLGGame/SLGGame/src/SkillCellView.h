/*!
@file
@author		Albert Semenov
@date		07/2008
*/
#ifndef _SKILL_CELL_VIEW_H__
#define _SKILL_CELL_VIEW_H__

#include <MyGUI.h>
#include "ItemBox/BaseCellView.h"
#include "SkillItemData.h"

class SkillCellView :
	public wraps::BaseCellView<SkillItemData*>
{
public:
	SkillCellView(MyGUI::Widget* _parent);

	void update(const MyGUI::IBDrawItemInfo& _info, SkillItemData* _data);
	static void getCellDimension(MyGUI::Widget* _sender, MyGUI::IntCoord& _coord, bool _drop);

private:
	MyGUI::ImageBox* mImageBack;
	MyGUI::ImageBox* mImageBorder;
	MyGUI::ImageBox* mImageItem;
	MyGUI::TextBox* mTextBack;
	MyGUI::TextBox* mTextFront;
};

#endif // __CELL_VIEW_H__
