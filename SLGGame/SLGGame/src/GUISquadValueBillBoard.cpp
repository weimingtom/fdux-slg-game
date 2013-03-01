#include "GUISquadValueBillBoard.h"

#include "Framerate.h"

#define OFFEST_X 70
#define OFFEST_Y 150

GUISquadValueBillBoard::GUISquadValueBillBoard(Ogre::SceneNode* node):GUIBillBoard("SquadValueBill.layout",150,35),mNode(node),mDeltaTime(0)
{
	assignWidget(mBText,"BText");
	mBText->setVisible(false);
	mFramerate=Framerate::getSingletonPtr();
}

GUISquadValueBillBoard::~GUISquadValueBillBoard(void)
{
}

Ogre::Vector3 GUISquadValueBillBoard::getPosition()
{
	if(mNode==NULL)
		return Ogre::Vector3(0,0,0);
	else
		return mNode->getPosition();
}

void GUISquadValueBillBoard::update( Ogre::Vector2 screen,unsigned int deltaTime)
{
	if(mMoveY<OFFEST_Y && mStart)
	{
		mBText->setPosition(screen.x+OFFEST_X/2,screen.y+OFFEST_Y-mMoveY);
		
		//mDeltaTime+=deltaTime;
		//if (mDeltaTime>=10)
		//{
			mMoveY+=1*mFramerate->speedfactor;
		//	mDeltaTime=0;
		//}
		
		if (mMoveY>OFFEST_Y/2)
		{
			float a=(mMoveY-OFFEST_Y/2)/(float)(OFFEST_Y/2);
			mBText->setAlpha(1-a);
		}
	}
	else
	{
		stopShow();
	}
}

void GUISquadValueBillBoard::setMarginalValue( float marginalTop,float marginalBottom,float marginalLeft,float marginalRight )
{

}

void GUISquadValueBillBoard::setValue( std::string value,MyGUI::Colour c)
{
	mBText->setCaption(value);
	mBText->setTextColour(c);
	mBText->setVisible(true);
	mBText->setAlpha(1);
	mMoveY=0;
	mStart=true;
}

void GUISquadValueBillBoard::showScene( std::string arg )
{
	//mBText->setVisible(true);
}

void GUISquadValueBillBoard::hideScene()
{
	mBText->setVisible(false);
	stopShow();
}

void GUISquadValueBillBoard::stopShow()
{
	mMoveY=0;
	mStart=false;
	mBText->setVisible(false);
	mBText->setCaption("");
}
