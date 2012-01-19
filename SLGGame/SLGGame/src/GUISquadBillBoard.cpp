#include "GUISquadBillBoard.h"

#define MARGIN_WIDTH 80
#define MARGIN_HEIGHT 50

GUISquadBillBoard::GUISquadBillBoard(Ogre::SceneNode* node):GUIBillBoard("SquadBill.layout",183,36),mNode(node),mIsVisible(true)
{
	assignWidget(mBImage,"BImage");
	assignWidget(mBName,"BName");
	assignWidget(mBIcon,"BIcon");
}

GUISquadBillBoard::~GUISquadBillBoard(void)
{
}

Ogre::Vector3 GUISquadBillBoard::getPosition()
{
	return mNode->getPosition();
}

void GUISquadBillBoard::update( Ogre::Vector2 screen,unsigned int deltaTime)
{
	mBImage->setPosition(screen.x,screen.y);
}

void GUISquadBillBoard::setMarginalValue(float marginalTop,float marginalBottom,float marginalLeft,float marginalRight)
{
	float visibility=1;
	if (marginalTop<=MARGIN_HEIGHT)
	{
		visibility=marginalTop/MARGIN_HEIGHT;
	}
	else if (marginalBottom<=MARGIN_HEIGHT)
	{
		visibility=marginalBottom/MARGIN_HEIGHT;
	}
	else if( marginalLeft<=MARGIN_WIDTH)
	{
		visibility=marginalLeft/MARGIN_WIDTH;
	}
	else if( marginalRight<=MARGIN_WIDTH)
	{
		visibility=marginalRight/MARGIN_WIDTH;
	}

	mBImage->setAlpha(visibility);

}


void GUISquadBillBoard::showScene( std::string arg )
{
	if (mIsVisible)
	{
		mBImage->setVisible(true);
	}
	else
	{
		mBImage->setVisible(false);
	}
}

void GUISquadBillBoard::hideScene()
{
	mBImage->setVisible(false);
}

void GUISquadBillBoard::setVisible( bool v )
{
	mIsVisible=v;
}

void GUISquadBillBoard::setName( std::string name,MyGUI::Colour c)
{
	mBName->setCaption(name);
	mBName->setTextColour(c);
}


void GUISquadBillBoard::setIcon( SquadIconType type )
{
	switch(type)
	{
	case SQUADTYPE_LightInf:
		 {
			mBIcon->setItemResource("LightInfIcon");
			break;
		 }
	case SQUADTYPE_HeavyInf:
		  {
			  mBIcon->setItemResource("HeavyInfIcon");
			  break;
		  }
	case SQUADTYPE_Saint:
		  {
			  mBIcon->setItemResource("SaintIcon");
			  break;
		  }
	case SQUADTYPE_Bowman:
		  {
			  mBIcon->setItemResource("BowmanIcon");
			  break;
		  }
	}

}

void GUISquadBillBoard::changeColor(MyGUI::Colour c)
{
	mBName->setTextColour(c);
}

