#include "EffectCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

EffectCutScene::EffectCutScene(unsigned int id,UnitType object,std::string name):CutScene(0)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);

	mSquadGraphics->setEffect(name,object);
	mObject=object;
}

EffectCutScene::~EffectCutScene(void)
{
	skipCutScene();
}

bool EffectCutScene::endCutScene()
{
	return mSquadGraphics->isEffectOver(mObject);
}

void EffectCutScene::skipCutScene()
{
	mSquadGraphics->stopEffect(mObject);
}

void EffectCutScene::updateCutScene( unsigned int deltaTime )
{

}
