#include "GUIPUDebug.h"

#include "Core.h"

#include "cutscencediretor.h"
#include "MoveCutScenece.h"

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

	mStart->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onStart);
	mRefresh->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onRefresh);

	mMove->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onMove);
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
	std::vector<Ogre::Vector2> grids;
	Ogre::Vector2 currentGrid(7,7);

	grids.push_back(Ogre::Vector2(7,6));
	grids.push_back(Ogre::Vector2(7,5));
	grids.push_back(Ogre::Vector2(7,4));
	grids.push_back(Ogre::Vector2(7,3));
	grids.push_back(Ogre::Vector2(8,3));
	grids.push_back(Ogre::Vector2(9,3));

	mDirector->addCutScence(new MoveCutScenece(Ogre::StringConverter::parseInt(mSquadID->getOnlyText()),grids,currentGrid));
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


