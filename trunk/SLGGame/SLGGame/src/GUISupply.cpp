#include "GUISupply.h"

GUISupply::GUISupply(int width,int height):GUIScene("supply.layout",width,height)
{
	setSceneLanguage();

	assignWidget(mSupplyBG,"SupplyBG");
	
}

GUISupply::~GUISupply(void)
{
}

void GUISupply::showScene( std::string arg )
{
}

void GUISupply::hideScene()
{

}

void GUISupply::FrameEvent()
{

}
