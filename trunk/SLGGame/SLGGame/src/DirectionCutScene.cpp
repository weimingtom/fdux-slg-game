#include "DirectionCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

DirectionCutScene::DirectionCutScene(std::string id,Direction direction)
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
	return mSquadGraphics->isDirectionOver();
}

void DirectionCutScene::skipCutScene()
{
	mSquadGraphics->stopTransform();
	mSquadGraphics->setInitAnimation(UNITTYPE_ALL);
	mSquadGraphics->setDirection(mDirection,false);
}

void DirectionCutScene::updateCutScene( unsigned int deltaTime )
{

}
