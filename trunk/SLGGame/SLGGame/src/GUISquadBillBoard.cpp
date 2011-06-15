#include "GUISquadBillBoard.h"

GUISquadBillBoard::GUISquadBillBoard(Ogre::SceneNode* node):GUIBillBoard("SquadBill.layout",189,44),mNode(node)
{
	assignWidget(mBImage,"BImage");
	assignWidget(mBName,"BName");
}

GUISquadBillBoard::~GUISquadBillBoard(void)
{
}

Ogre::Vector3 GUISquadBillBoard::getPosition()
{
	return mNode->getPosition();
}

void GUISquadBillBoard::update( Ogre::Vector2 screen )
{
	mBImage->setPosition(screen.x,screen.y);
}

void GUISquadBillBoard::showScene( std::string arg )
{
	mBImage->setVisible(true);
}

void GUISquadBillBoard::hideScene()
{
	mBImage->setVisible(false);
}
