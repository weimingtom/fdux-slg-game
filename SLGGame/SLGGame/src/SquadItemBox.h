/*!
	@file
	@author		Albert Semenov
	@date		01/2009
*/
#ifndef __SQUADITEM_BOX_H__
#define __SQUADITEM_BOX_H__

#include <MyGUI.h>
#include "ItemBox/BaseItemBox.h"
#include "SquadCellView.h"

class SquadItemBox :
		public wraps::BaseItemBox<SquadCellView>
	{
	public:
		SquadItemBox(MyGUI::Widget* _parent);
		virtual ~SquadItemBox();
	};

#endif // __ITEM_BOXV_H__
