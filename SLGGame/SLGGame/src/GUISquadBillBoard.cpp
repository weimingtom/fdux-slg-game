#include "GUISquadBillBoard.h"

#define MARGIN_WIDTH 80
#define MARGIN_HEIGHT 50

GUISquadBillBoard::GUISquadBillBoard(Ogre::SceneNode* node):GUIBillBoard("SquadBill.layout",183,36),mNode(node),mIsVisible(true)
{
	assignWidget(mBImage,"BImage");
	assignWidget(mBName,"BName");
	assignWidget(mBIcon,"BIcon");
	assignWidget(mBBar,"BProgressBar");
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


void GUISquadBillBoard::setIcon( enumtype type )
{
	mBIcon->setItemResource("kind");
	switch(type)
	{
	case SQUADTYPE_MISSILEINFANTRY:
		{
			mBIcon->setItemGroup("kind_lightinf");
			break;
		}
	case SQUADTYPE_INFANTRY:
		{
			mBIcon->setItemGroup("kind_heavyinf");
			break;
		}
	case SQUADTYPE_CAVALRY:
		{
			mBIcon->setItemGroup("kind_heavyrid");
			break;
		}
	case SQUADTYPE_MISSILECAVALRY:
		{
			mBIcon->setItemGroup("kind_lightrid");
			break;
		}
	case SQUADTYPE_BATTLEMAGE:
		{
			mBIcon->setItemGroup("kind_warlock");
			break;
		}
	case SQUADTYPE_ARCANEMAGE:
		{
			mBIcon->setItemGroup("kind_priest");
			break;
		}
	case SQUADTYPE_SAINT:
		{
			mBIcon->setItemGroup("kind_mage");
			break;
		}
	}

}

void GUISquadBillBoard::setBar(int v)
{
	mBBar->setProgressPosition(v);
}

void GUISquadBillBoard::changeColor(MyGUI::Colour c)
{
	mBName->setTextColour(c);
}

