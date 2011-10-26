#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include "Skill.h"

#include <vector>

class SkillManager
{
public:
	SkillManager();
	~SkillManager();

	void update( unsigned int time );
	void createSkill( std::string name );

private:
	std::vector<Skill*> mSkillList;
};

#endif