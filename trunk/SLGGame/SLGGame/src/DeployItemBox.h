/*!
	@file
	@author		Albert Semenov
	@date		01/2009
*/
#ifndef __DeployITEM_BOX_H__
#define __DeployITEM_BOX_H__

#include <MyGUI.h>
#include "ItemBox/BaseItemBox.h"
#include "DeployCellView.h"

class DeployItemBox :
		public wraps::BaseItemBox<DeployCellView>
	{
	public:
		DeployItemBox(MyGUI::Widget* _parent);
		virtual ~DeployItemBox();
	};

#endif // __ITEM_BOXV_H__
