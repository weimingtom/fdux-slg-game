#pragma once

#include <vector>

template <typename T>
struct DecisionInfo
{
	T decision;
	float possibility;
};

template <typename T>
class DecisionMapFactor
{
public:
	DecisionMapFactor(float scale)
	:mScale(scale)
	{
	}

	virtual void calcDecision(std::vector<DecisionInfo<T>> &decisionVec) = 0;
protected:
	float mScale;
};