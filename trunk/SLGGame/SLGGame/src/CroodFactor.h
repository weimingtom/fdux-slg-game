#pragma once

#include <set>

#include "DecisionMapFactor.h"

#include "Area.h"

class ClosetoCroodFactor: public DecisionMapFactor<Crood>
{
public:
	ClosetoCroodFactor(Crood tgtcrood, int dist = 0);

	virtual float calcDecision(Crood &crood);
private:
	Crood mTgtCrood;
	int mDist;
};

class ClosetoBorderFactor: public DecisionMapFactor<Crood>
{
public:
	ClosetoBorderFactor(Area &area);

	virtual float calcDecision(Crood &crood);
private:
	std::set<int> mAreaSet;
};