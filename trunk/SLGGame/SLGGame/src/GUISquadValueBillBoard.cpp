#include "GUISquadValueBillBoard.h"

#define OFFEST_X 70
#define OFFEST_Y 150

GUISquadValueBillBoard::GUISquadValueBillBoard(Ogre::SceneNode* node):GUIBillBoard("SquadValueBill.layout",150,35),mNode(node)
{
	assignWidget(mBText,"BText");
	mBText->setVisible(false);
}

GUISquadValueBillBoard::~GUISquadValueBillBoard(void)
{
}

Ogre::Vector3 GUISquadValueBillBoard::getPosition()
{
	return mNode->getPosition();
}

void GUISquadValueBillBoard::update( Ogre::Vector2 screen )
{
	if(mMoveY<OFFEST_Y && mStart)
	{
		mBText->setPosition(screen.x+OFFEST_X/2,screen.y+OFFEST_Y-mMoveY);
		mMoveY+=1;
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
	mBText->setVisible(true);
}

void GUISquadValueBillBoard::hideScene()
{
	mBText->setVisible(false);
}

void GUISquadValueBillBoard::stopShow()
{
	mMoveY=0;
	mStart=false;
	mBText->setVisible(false);
	mBText->setCaption("");
}
