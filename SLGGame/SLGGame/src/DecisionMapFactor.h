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

template <typename T>
class RandomFactor:public DecisionMapFactor<T>
{
public:
	RandomFactor(float min, float max);

	virtual float calcDecision(T& decision);
private:
	float mMin;
	float mMax;
};

template <typename T>
RandomFactor<T>::RandomFactor(float min, float max)
:mMin(min),mMax(max)
{

}

template <typename T>
float RandomFactor<T>::calcDecision(T& decision)
{
	return mMin + (rand()%101/100.0f)*(mMax - mMin);
}