#include "GUIEffectWindow.h"

#include "boost/format.hpp"
#include "DataLibrary.h"
#include "GUITipsWindow.h"

GUIEffectWindow::GUIEffectWindow( MyGUI::Window* window,int Width,int Height,int index):GUISubWindows(window,Width,Height),mWindow(window),mIndex(index)
{
	for(int i=0;i<10;i++)
	{
		assignWidget(mEffect[i],str(boost::format("effect%1%")%(i+1)));
	}
}

GUIEffectWindow::~GUIEffectWindow()
{

}

bool GUIEffectWindow::GridInputEvent( int x,int y )
{
	return false;
}

void GUIEffectWindow::showScene( std::string arg )
{
	mWindow->setVisible(true);
}

void GUIEffectWindow::hideScene()
{
	mWindow->setVisible(false);
}

void GUIEffectWindow::FrameEvent()
{

}

void GUIEffectWindow::setEffectList(std::vector<std::string> list,std::vector<int> level)
{
	int i=0;
	std::string effectPath="StaticData/EffectData/";
	std::string data;
	std::string skillTips;
	int skilllvindex = 0;
	for (std::vector<std::string>::iterator it=list.begin();it!=list.end();it++,skilllvindex++)
	{
		DataLibrary::getSingletonPtr()->getData(effectPath+(*it)+std::string("/Icon"),data);
		DataLibrary::getSingletonPtr()->getData(effectPath+(*it)+std::string("/Describe"),skillTips);
		int showonbattlesquad = 0;
		DataLibrary::getSingletonPtr()->getData(effectPath+(*it)+std::string("/ShowOnBattleSquad"),showonbattlesquad);
		if(showonbattlesquad == 1)
		{
			mEffect[i]->setImageResource("skillpass");
			mEffect[i]->setImageGroup(data);
			mEffect[i]->setUserString("Tips",skillTips);
			mEffect[i]->setNeedToolTip(true);
			GUITipsWindow::getSingletonPtr()->addToolTipEvent(mEffect[i]);
			if(level[skilllvindex]!=0)
				mEffect[i]->setCaption(Ogre::StringConverter::toString(level[skilllvindex]));
			i++;
		}
	}

	for (;i<10;i++)
	{
		mEffect[i]->setImageResource("");
		mEffect[i]->setImageGroup("");
		mEffect[i]->setNeedToolTip(false);
		mEffect[i]->setCaption("");
	}


}