#include "SquadStateCutScene.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "BattleSquad.h"
#include "DataLibrary.h"
#include "boost/format.hpp"

SquadStateCutScene::SquadStateCutScene(BattleSquad* battlesquad, SquadStateType type, std::string stateid ,int val)
{
	mSquadGraphics = SquadGrapManager::getSingleton().getSquad(battlesquad->getGrapId());
	mSquad = battlesquad;
	mStateType = type;
	mStateId = stateid;
	mStateValue = val;
}
SquadStateCutScene::~SquadStateCutScene(void)
{

}

void SquadStateCutScene::startCutScence()
{
	if(mSquadGraphics == NULL)
		return;
	switch(mStateType)
	{
	case SQUAD_STATE_VISIBLE:
		{
			if(mStateValue == 0)
				mSquadGraphics->setVisible(false);
			else
				mSquadGraphics->setVisible(true);
		}
		break;
	case SQUAD_STATE_PARTICLE:
		{
			if(mStateValue == 1 || mStateValue == 4 )
			{
				std::string name;
				UnitType object;
				DataLibrary::getSingleton().getData(str(boost::format("%1%/ParticleList/%2%/Particle")%mSquad->getPath()%mStateId),name);
				DataLibrary::getSingleton().getData(str(boost::format("%1%/ParticleList/%2%/UnitType")%mSquad->getPath()%mStateId),object);
				mSquadGraphics->addParticle(mStateId,name,object);
			}
			if(mStateValue == 2 || mStateValue == 4)
			{
				mSquadGraphics->startParticle(mStateId);
			}
		}
		break;
	}
}
bool SquadStateCutScene::endCutScene()
{
	return true;
}
void SquadStateCutScene::skipCutScene()
{
	startCutScence();
}
void SquadStateCutScene::updateCutScene(unsigned int deltaTime)
{

}