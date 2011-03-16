#include "EffectCutScenece.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

EffectCutScenece::EffectCutScenece(unsigned int id,EffectObject object,std::string name):CutScence(0)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);

	mSquadGraphics->setEffect(name,(SquadGraphics::Object)object);
	mObject=object;
}

EffectCutScenece::~EffectCutScenece(void)
{
	skipCutScence();
}

bool EffectCutScenece::endCutScence()
{
	return mSquadGraphics->isEffectOver((SquadGraphics::Object)mObject);
}

void EffectCutScenece::skipCutScence()
{
	mSquadGraphics->stopEffect((SquadGraphics::Object)mObject);
}

void EffectCutScenece::updateCutScence( unsigned int deltaTime )
{

}
