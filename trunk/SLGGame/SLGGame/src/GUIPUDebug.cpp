#include "GUIPUDebug.h"

#include "Core.h"

#include "cutscencediretor.h"
#include "MoveCutScenece.h"
#include "DirectionCutScenece.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

#include <ParticleUniverseSystem.h> 

GUIPUDebug::GUIPUDebug(int width,int height):GUIScene(width,height,"PUDebug.layout")
{
	assignWidget(mPUList,"PUList");
	assignWidget(mStart,"Start");
	assignWidget(mRefresh,"Refresh");

	assignWidget(mScaleX,"ScaleX");
	assignWidget(mScaleY,"ScaleY");
	assignWidget(mScaleZ,"ScaleZ");
	assignWidget(mScaleTime,"ScaleTime");

	assignWidget(mSquadID,"SquadID");
	assignWidget(mMove,"Move");

	assignWidget(mDirection,"Direction");
	assignWidget(mDirectionList,"DirectionList");

	assignWidget(mFormation,"Formation");
	assignWidget(mFormationList,"FormationList");

	mStart->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onStart);
	mRefresh->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onRefresh);

	mMove->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onMove);
	mDirection->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onDirection);
	mFormation->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onFormation);
}

GUIPUDebug::~GUIPUDebug(void)
{
}

void GUIPUDebug::onStart( MyGUI::Widget* _sender )
{
	if (mPUList->getIndexSelected()!=MyGUI::ITEM_NONE)
	{
		for (std::vector<ParticleUniverse::ParticleSystem*>::iterator it=Core::getSingletonPtr()->mPUSystems.begin();it!=Core::getSingletonPtr()->mPUSystems.end();it++)
		{
			if ((*it)->getName()==mPUList->getItemNameAt(mPUList->getIndexSelected()).asUTF8())
			{
				(*it)->stop();
				(*it)->setScale(Ogre::Vector3(Ogre::StringConverter::parseReal(mScaleX->getOnlyText()),Ogre::StringConverter::parseReal(mScaleY->getOnlyText()),Ogre::StringConverter::parseReal(mScaleZ->getOnlyText())));
				(*it)->setScaleTime(Ogre::StringConverter::parseReal(mScaleTime->getOnlyText()));
				(*it)->start();
				break;
			}
		}
	}
}

void GUIPUDebug::onRefresh( MyGUI::Widget* _sender )
{
	mPUList->removeAllItems();
	for (std::vector<ParticleUniverse::ParticleSystem*>::iterator it=Core::getSingletonPtr()->mPUSystems.begin();it!=Core::getSingletonPtr()->mPUSystems.end();it++)
	{
		mPUList->addItem((*it)->getName());
	}
}

void GUIPUDebug::onMove( MyGUI::Widget* _sender )
{
	if(Ogre::StringConverter::parseInt(mSquadID->getOnlyText())!=0)
	{
		std::vector<Ogre::Vector2> grids;
		Ogre::Vector2 currentGrid(7,7);

		grids.push_back(Ogre::Vector2(7,8));
		grids.push_back(Ogre::Vector2(7,9));
		grids.push_back(Ogre::Vector2(8,9));
		grids.push_back(Ogre::Vector2(9,9));
		grids.push_back(Ogre::Vector2(9,8));
		grids.push_back(Ogre::Vector2(8,8));

		mDirector->addCutScence(new MoveCutScenece(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()),grids,currentGrid));
	}
}


void GUIPUDebug::onDirection( MyGUI::Widget* _sender )
{
	if(Ogre::StringConverter::parseInt(mSquadID->getOnlyText())!=0)
	{
		DirectionCutScenece::Direction d;
		if (mDirectionList->getIndexSelected()==0)
		{
			d=DirectionCutScenece::North;
		}
		else if (mDirectionList->getIndexSelected()==1)
		{
			d=DirectionCutScenece::South;
		}
		else if (mDirectionList->getIndexSelected()==2)
		{
			d=DirectionCutScenece::West;
		}
		else
		{
			d=DirectionCutScenece::East;
		}
		
		SquadGrapManager::getSingletonPtr()->getSquad(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()))->setAnimation("RunBase",SquadGraphics::Squad,true);

		mDirector->addCutScence(new DirectionCutScenece(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()),d));
	}

}

void GUIPUDebug::onFormation( MyGUI::Widget* _sender )
{
	if(Ogre::StringConverter::parseInt(mSquadID->getOnlyText())!=0)
	{

		SquadGrapManager::getSingletonPtr()->getSquad(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()))->setFormation((SquadGraphics::Formation)mFormationList->getIndexSelected(),true);

		//mDirector->addCutScence(new DirectionCutScenece(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()),d));
	}
}

void GUIPUDebug::showScene( std::string arg )
{

}

void GUIPUDebug::hideScene()
{

}

void GUIPUDebug::FrameEvent()
{

}



