/*!
	@file
	@author		Albert Semenov
	@date		01/2009
*/
#ifndef __ITEM_BOX_H__
#define __ITEM_BOX_H__

#include <MyGUI.h>
#include "ItemBox/BaseItemBox.h"
#include "WeaponCellView.h"

class WeaponItemBox :
		public wraps::BaseItemBox<WeaponCellView>
	{
	public:
		WeaponItemBox(MyGUI::Widget* _parent);
		virtual ~WeaponItemBox();
	};

#endif // __ITEM_BOXV_H__
