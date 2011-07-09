#include "EffectCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

EffectCutScene::EffectCutScene(unsigned int id,UnitType object,std::string name):CutScene(0)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);

	mName=name;
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

void EffectCutScene::startCutScence()
{
	mSquadGraphics->setEffect(mName,mObject);
}
