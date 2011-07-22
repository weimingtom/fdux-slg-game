#include "GUIMessageBox.h"

#include "StringTable.h"

GUIMessageBox::GUIMessageBox(int width,int height):GUIScene("MessageBox.layout",width,height)
{
	assignWidget(mYesButton,"Yes");
	assignWidget(mNoButton,"No");
	assignWidget(mCaption,"Caption");
	assignWidget(mBG,"BG");
	assignWidget(mWindow,"Window");

	mYesButton->setCaption(StringTable::getSingletonPtr()->getString("Yes"));
	mNoButton->setCaption(StringTable::getSingletonPtr()->getString("No"));

	mYesButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMessageBox::onYes);
	mNoButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIMessageBox::onNo);
}

GUIMessageBox::~GUIMessageBox(void)
{
}

void GUIMessageBox::showScene( std::string arg )
{
	mCaption->setCaption(arg);
	mBG->setVisible(true);
	mIsReturn=false;
}

void GUIMessageBox::hideScene()
{
	mBG->setVisible(false);
}

void GUIMessageBox::FrameEvent()
{

}

void GUIMessageBox::onYes( MyGUI::Widget* _sender )
{
	mIsReturn=true;
	mYesNo=true;
	hideScene();
}

void GUIMessageBox::onNo( MyGUI::Widget* _sender )
{
	mIsReturn=true;
	mYesNo=false;
	hideScene();
}