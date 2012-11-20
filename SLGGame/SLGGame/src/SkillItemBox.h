/*!
	@file
	@author		Albert Semenov
	@date		01/2009
*/
#ifndef _SKILL_ITEM_BOX_H__
#define _SKILL_ITEM_BOX_H__

#include <MyGUI.h>
#include "ItemBox/BaseItemBox.h"
#include "SkillCellView.h"

class SkillItemBox :
		public wraps::BaseItemBox<SkillCellView>
	{
	public:
		SkillItemBox(MyGUI::Widget* _parent);
		virtual ~SkillItemBox();
	};

#endif // __ITEM_BOXV_H__
