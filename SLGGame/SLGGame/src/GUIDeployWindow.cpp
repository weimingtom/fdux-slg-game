#include "GUIDeployWindow.h"

#include "StringTable.h"
#include "BattleDeployState.h"

GUIDeployWindows::GUIDeployWindows(MyGUI::Window* window,int Width,int Height)
:GUISubWindows(window,Width,Height),mWindow(window),mState(NULL)
{
	assignWidget(mDeployList,"DeployList");
	assignWidget(mConfirm,"DeployConfirm");
	setAllowConfirm(false);
	mDeployList->setColumnResizingPolicyAt(0,MyGUI::ResizingPolicy::Fixed);
	mDeployList->setColumnResizingPolicyAt(1,MyGUI::ResizingPolicy::Fixed);
	mDeployList->setColumnWidthAt(0,200);
	mDeployList->setColumnWidthAt(1,90);

	mWindow->setCaption(StringTable::getSingleton().getString("DeployWindow"));
	mConfirm->setCaption(StringTable::getSingleton().getString("DeployConfirm"));

	mDeployList->eventListChangePosition  += MyGUI::newDelegate(this, &GUIDeployWindows::onSelect);
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

void GUIDeployWindows::initList(std::vector<std::string> squadlist)
{
	for(int n = 0; n < squadlist.size(); n++)
	{
		mDeployList->addItem(squadlist[n]);
		mDeployList->setSubItemNameAt(1, n ,StringTable::getSingleton().getString("NotDeploy"));
	}
}

void GUIDeployWindows::setAllowConfirm(bool allow)
{
	mConfirm->setEnabled(allow);
}

void GUIDeployWindows::onSelect(MyGUI::MultiListBox* _sender, size_t _index)
{
	if(mState)
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
	mDeployList->setSubItemNameAt(1, index ,info);
}