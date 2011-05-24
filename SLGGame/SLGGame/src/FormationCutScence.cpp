#include "FormationCutScence.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

FormationCutScene::FormationCutScene(unsigned int id,Formation formation)
{
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	mForm=formation;
	time = 0;
}

FormationCutScene::~FormationCutScene(void)
{
}

void FormationCutScene::startCutScence()
{
	mSquadGraphics->setFormation(mForm,true);
}

bool FormationCutScene::endCutScene()
{
	return time > 150;
}

void FormationCutScene::skipCutScene()
{
	mSquadGraphics->setFormation(mForm,false);
}

void FormationCutScene::updateCutScene( unsigned int deltaTime )
{
	time += 10;
}
