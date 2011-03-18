#include "DirectionCutScenece.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

DirectionCutScenece::DirectionCutScenece(unsigned int id,Direction direction)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mSquadGraphics->setDirection((SquadGraphics::Direction)direction,true);
	mDirection=direction;
}

DirectionCutScenece::~DirectionCutScenece(void)
{
}

bool DirectionCutScenece::endCutScence()
{
	return mSquadGraphics->isTransformOver();
}

void DirectionCutScenece::skipCutScence()
{
	mSquadGraphics->setDirection((SquadGraphics::Direction)mDirection,false);
}

void DirectionCutScenece::updateCutScence( unsigned int deltaTime )
{

}
