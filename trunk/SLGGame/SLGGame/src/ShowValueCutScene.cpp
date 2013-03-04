#include "ShowValueCutScene.h"

#include "SquadGraphics.h"
#include "SquadGrapManager.h"

ShowValueCutScene::ShowValueCutScene(std::string id,std::string value,Ogre::ColourValue c):CutScene(2000),mValue(value),mColor(c)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
}

ShowValueCutScene::~ShowValueCutScene(void)
{
}

void ShowValueCutScene::startCutScence()
{
	mSquadGraphics->showValue(mValue,mColor);
}

bool ShowValueCutScene::endCutScene()
{
	return true;
}

void ShowValueCutScene::skipCutScene()
{
	if(!mStarted)
		mSquadGraphics->showValue(mValue,mColor);
}

void ShowValueCutScene::updateCutScene( unsigned int deltaTime )
{

}
