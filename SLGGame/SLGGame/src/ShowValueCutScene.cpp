#include "ShowValueCutScene.h"

#include "SquadGraphics.h"
#include "SquadGrapManager.h"

ShowValueCutScene::ShowValueCutScene(unsigned int id,std::string value,Ogre::ColourValue c):CutScene(3000),mValue(value),mColor(c)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
}

ShowValueCutScene::~ShowValueCutScene(void)
{
	mSquadGraphics->stopShowValue();
}

void ShowValueCutScene::startCutScence()
{
	mSquadGraphics->showValue(mValue,mColor);
}

bool ShowValueCutScene::endCutScene()
{
	return false;
}

void ShowValueCutScene::skipCutScene()
{
	mSquadGraphics->stopShowValue();
}

void ShowValueCutScene::updateCutScene( unsigned int deltaTime )
{

}
