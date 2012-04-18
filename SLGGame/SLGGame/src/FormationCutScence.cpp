#include "FormationCutScence.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

FormationCutScene::FormationCutScene(std::string id,enumtype formation)
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
	return mSquadGraphics->isFormationOrDirectionOver();
}

void FormationCutScene::skipCutScene()
{
	mSquadGraphics->stopTransform();

	mSquadGraphics->setFormation(mForm,false);
}

void FormationCutScene::updateCutScene( unsigned int deltaTime )
{
	time += 10;
}
