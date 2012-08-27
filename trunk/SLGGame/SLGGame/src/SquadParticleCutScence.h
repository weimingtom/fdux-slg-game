#pragma once
#include "cutscene.h"

#include <string>

#include "squaddefine.h"

class SquadParticleCutScence : public CutScene
{
public:
	SquadParticleCutScence(std::string squadid, std::string particleid, std::string particlename, enumtype affectunit);
	SquadParticleCutScence(std::string squadid, std::string particleid);
	virtual ~SquadParticleCutScence();

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);
private:
	std::string mSquadId;
	std::string mParticleId;
	std::string mParticleName;
	enumtype mAffectUnit;
	bool mRemove;
};