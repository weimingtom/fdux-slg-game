#include "SkillManager.h"

SkillManager::SkillManager(void)
{
}

SkillManager::~SkillManager(void)
{
	for (std::vector<Skill*>::iterator it=mSkillList.begin();it!=mSkillList.end();it++)
	{
		delete (*it);
	}
}

void SkillManager::update( unsigned int time )
{
	for (std::vector<Skill*>::iterator it=mSkillList.begin();it!=mSkillList.end();it++)
	{
		(*it)->update(time);
	}
}

void SkillManager::createSkill( std::string name )
{
	Skill* skill=new Skill(name);
	mSkillList.push_back(skill);
}	
