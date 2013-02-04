#include "GUIDeployWindow.h"

#include "StringTable.h"
#include "BattleDeployState.h"


GUIDeployWindows::GUIDeployWindows(MyGUI::Window* window,int Width,int Height)
:GUISubWindows(window,Width,Height),mWindow(window),mState(NULL)
{
	MyGUI::ItemBox* baseList;
	assignWidget(baseList,"DeployList");
	assignWidget(mConfirm,"DeployConfirm");
	mDeployList=new DeployItemBox(baseList);
	mDeployList->getItemBox()->eventMouseItemActivate+= MyGUI::newDelegate(this, &GUIDeployWindows::onSelect);
	setAllowConfirm(false);

	mWindow->setCaption(StringTable::getSingleton().getString("DeployWindow"));
	mConfirm->setCaption(StringTable::getSingleton().getString("DeployConfirm"));

	//mDeployList->eventListChangePosition  += MyGUI::newDelegate(this, &GUIDeployWindows::onSelect);
	mConfirm->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIDeployWindows::onConfirm);
}

GUIDeployWindows::~GUIDeployWindows(void)
{

}

void GUIDeployWindows::showScene(std::string arg)
{
	mWindow->setVisible(true);
}

void GUIDeployWindows::hideScene()
{
	mWindow->setVisible(false);
}

void GUIDeployWindows::FrameEvent()
{

}

bool GUIDeployWindows::GridInputEvent(int x,int y)
{
	return false;
}

void GUIDeployWindows::initList(std::vector<BattleSquad*>& list)
{
	for(std::vector<BattleSquad*>::iterator it=list.begin();it!=list.end();it++)
	{
		mDeployList->addItem(new DeployItemData((*it)->getSquadType(),(*it)->getName(),StringTable::getSingleton().getString("NotDeploy")));
	}
}

void GUIDeployWindows::setAllowConfirm(bool allow)
{
	mConfirm->setEnabled(allow);
}

void GUIDeployWindows::onSelect(MyGUI::ItemBox* _sender, size_t _index)
{
	if(mState && _index!=-1)
	{
		mState->selectIndex(_index);
	}
}

void GUIDeployWindows::onConfirm(MyGUI::Widget* _sender)
{
	if(mState)
	{
		mState->deployConfirm();
	}
}

void GUIDeployWindows::setDeployState(BattleDeployState* state)
{
	mState = state;
}

void GUIDeployWindows::setDeployInfo(int index, std::string info)
{
	if(index!=-1)
	{
		DeployItemData* item=*(mDeployList->getItemDataAt<DeployItemData*>(index));
		item->setDeployState(info);
		mDeployList->setItemData(index,item);
	}
}