#include "SquadParticleCutScence.h"

#include "SquadGrapManager.h"
#include "SquadGraphics.h"

SquadParticleCutScence::SquadParticleCutScence(std::string squadid, std::string particleid, std::string particlename, int affectunit)
:mSquadId(squadid),mParticleId(particleid),mParticleName(particlename),mAffectUnit(affectunit),mRemove(false)
{

}

SquadParticleCutScence::SquadParticleCutScence(std::string squadid, std::string particleid)
:mSquadId(squadid),mParticleId(particleid),mRemove(true)
{
}

SquadParticleCutScence::~SquadParticleCutScence()
{

}

void SquadParticleCutScence::startCutScence()
{
	SquadGraphics* squadgrap = SquadGrapManager::getSingleton().getSquad(mSquadId);
	if(squadgrap)
	{
		if(mRemove)
		{
			squadgrap->stopParticle(mParticleId);
			squadgrap->delParticle(mParticleId);
		}
		else
		{
			if(squadgrap->addParticle(mParticleId, mParticleName, mAffectUnit))
			{
				squadgrap->startParticle(mParticleId);
			}
		}

	}
}

bool SquadParticleCutScence::endCutScene()
{
	return true;
}

void SquadParticleCutScence::skipCutScene()
{
	startCutScence();
}

void SquadParticleCutScence::updateCutScene(unsigned int deltaTime)
{

}