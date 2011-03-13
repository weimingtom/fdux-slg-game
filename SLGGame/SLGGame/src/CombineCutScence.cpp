#include "CombineCutScence.h"


CombineCutScence::CombineCutScence()
{

}
CombineCutScence::~CombineCutScence()
{

}

void CombineCutScence::addCutScence(CutScence* cutscence)
{
	mCutScence.push_back(cutscence);
}

bool CombineCutScence::endCutScence()
{
	CutScenceIte ite;
	bool bend = true;
	for(ite = mCutScence.begin(); ite != mCutScence.end();ite++)
	{
		if(!(*ite)->end())
			bend = false;
	}
	return bend;
}
void CombineCutScence::skipCutScence()
{
	CutScenceIte ite;
	for(ite = mCutScence.begin(); ite != mCutScence.end();ite++)
	{
		(*ite)->skipall();
	}
}
void CombineCutScence::updateCutScence(unsigned int deltaTime)
{
	CutScenceIte ite;
	for(ite = mCutScence.begin(); ite != mCutScence.end();)
	{
		if((*ite)->end())
		{
			delete *ite;
			ite = mCutScence.erase(ite);
		}
		else
		{
			(*ite)->update(deltaTime);
			ite++;
		}
	}
}