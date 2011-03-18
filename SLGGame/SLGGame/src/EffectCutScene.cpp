#include "EffectCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

EffectCutScene::EffectCutScene(unsigned int id,EffectObject object,std::string name):CutScene(0)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);

	mSquadGraphics->setEffect(name,(SquadGraphics::Object)object);
	mObject=object;
}

EffectCutScene::~EffectCutScene(void)
{
	skipCutScene();
}

bool EffectCutScene::endCutScene()
{
	return mSquadGraphics->isEffectOver((SquadGraphics::Object)mObject);
}

void EffectCutScene::skipCutScene()
{
	mSquadGraphics->stopEffect((SquadGraphics::Object)mObject);
}

void EffectCutScene::updateCutScene( unsigned int deltaTime )
{

}
