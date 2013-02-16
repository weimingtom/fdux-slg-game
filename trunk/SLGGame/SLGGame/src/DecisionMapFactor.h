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
	virtual float calcDecision(T& decision) = 0;
};