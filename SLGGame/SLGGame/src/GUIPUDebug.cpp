#include "GUIPUDebug.h"

#include "Core.h"

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

	mStart->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onStart);
	mRefresh->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIPUDebug::onRefresh);
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

void GUIPUDebug::showScene( std::string arg )
{

}

void GUIPUDebug::hideScene()
{

}

void GUIPUDebug::FrameEvent()
{

}


