#include "DirectionCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

DirectionCutScene::DirectionCutScene(unsigned int id,Direction direction)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mSquadGraphics->setDirection(direction,true);
	mDirection=direction;
}

DirectionCutScene::~DirectionCutScene(void)
{
}

bool DirectionCutScene::endCutScene()
{
	return mSquadGraphics->isTransformOver();
}

void DirectionCutScene::skipCutScene()
{
	mSquadGraphics->setDirection(mDirection,false);
}

void DirectionCutScene::updateCutScene( unsigned int deltaTime )
{

}
