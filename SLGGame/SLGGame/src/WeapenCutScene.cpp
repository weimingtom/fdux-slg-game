#include "WeapenCutScene.h"

#include "SquadGraphics.h"
#include "SquadGrapManager.h"

WeapenCutScene::WeapenCutScene(unsigned int id,WeaponType type):mType(type)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
}

WeapenCutScene::~WeapenCutScene(void)
{
}

void WeapenCutScene::startCutScence()
{
	mSquadGraphics->setWeaponMode((SquadGraphics::WeaponMode)mType);
}

bool WeapenCutScene::endCutScene()
{
	return true;
}

void WeapenCutScene::skipCutScene()
{

}

void WeapenCutScene::updateCutScene( unsigned int deltaTime )
{

}
