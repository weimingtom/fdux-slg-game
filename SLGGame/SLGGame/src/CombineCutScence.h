#pragma once

#include "cutscenes.h"
#include <list>

class CombineCutScence: public CutScence
{
public:
	CombineCutScence();
	~CombineCutScence();
	
	void addCutScence(CutScence* cutscence);

private:
	virtual bool endCutScence();
	virtual void skipCutScence();
	virtual void updateCutScence(unsigned int deltaTime);

	typedef std::list<CutScence*>::iterator CutScenceIte;
	std::list<CutScence*> mCutScence;
};