#pragma once

#include <map>

class CutScence;

class CutScenceDirector
{
public:
	CutScenceDirector();
	~CutScenceDirector();

	int addCutScence(CutScence* cutscence);
	void skipCutScence(int id);

	void update(unsigned int deltaTime);
private:
	typedef std::pair<int, CutScence*> CutScencePair;
	typedef std::map<int, CutScence*>::iterator CutScenceIte;
	std::map<int, CutScence*> mCutScence;
	int mId;
};