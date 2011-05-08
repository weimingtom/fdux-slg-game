#include "DirectionCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

DirectionCutScene::DirectionCutScene(unsigned int id,Direction direction)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mDirection=direction;
}

DirectionCutScene::~DirectionCutScene(void)
{
}

void DirectionCutScene::startCutScence()
{	
	mSquadGraphics->setDirection(mDirection,true);
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
