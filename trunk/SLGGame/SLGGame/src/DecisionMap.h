#pragma once

#include <vector>

#include "DecisionMapFactor.h"

template <typename T>
class DecisionMap
{
public:
	DecisionMap(std::vector<T>& decisionVec);
	~DecisionMap();

	void addFactor(DecisionMapFactor<T> *factor);
	void calcDecision();

	T getHighest();
	std::vector<T> getHigherThan(float possibility);
	std::vector<T> getSortedDecisions();
private:
	std::vector<DecisionMapFactor<T>*> mFactorVec;

	std::vector<DecisionInfo<T>> mDecisionVec;
};

template <typename T>
DecisionMap<T>::DecisionMap(std::vector<T>& decisionVec)
{
	std::vector<T>::iterator ite = decisionVec.begin();
	for( ; ite != decisionVec.end(); ite++)
	{
		DecisionInfo<T> decisioninfo;
		decisioninfo.decision = (*ite);
		decisioninfo.possibility = 0.0f;
		mDecisionVec.push_back(decisioninfo);
	}
}

template <typename T>
DecisionMap<T>::~DecisionMap()
{
	std::vector<DecisionMapFactor<T>*>::iterator ite = mFactorVec.begin();
	for( ; ite != mFactorVec.end(); ite++)
	{
		delete (*ite);
	}
	mFactorVec.clear();
}

template <typename T>
void DecisionMap<T>::addFactor(DecisionMapFactor<T> *factor)
{
	mFactorVec.push_back(factor);
}

template <typename T>
bool DGreater(DecisionInfo<T> elem1, DecisionInfo<T> elem2)
{
   return elem1.possibility > elem2.possibility;
}

template <typename T>
void DecisionMap<T>::calcDecision()
{
	std::vector<DecisionMapFactor<T>*>::iterator ite = mFactorVec.begin();
	for( ; ite != mFactorVec.end(); ite++)
	{
		(*ite)->calcDecision(mDecisionVec);
	}
	std::sort(mDecisionVec.begin(), mDecisionVec.end(), DGreater<T>);
}

template <typename T>
T DecisionMap<T>::getHighest()
{
	return mDecisionVec.begin()->decision;
}

template <typename T>
std::vector<T> DecisionMap<T>::getHigherThan(float possibility)
{
	std::vector<T> decisionvec;
	std::vector<DecisionInfo<T>>::iterator ite = mDecisionVec.begin();
	for( ; ite != mDecisionVec.end(); ite++)
	{
		if((*ite).possibility >= possibility)
			decisionvec.push_back((*ite).decision);
		else
			break;
	}
	return decisionvec;
}

template <typename T>
std::vector<T> DecisionMap<T>::getSortedDecisions()
{
	std::vector<T> decisionvec;
	std::vector<DecisionInfo<T>>::iterator ite = mDecisionVec.begin();
	for( ; ite != mDecisionVec.end(); ite++)
	{
		decisionvec.push_back((*ite).decision);
	}
	return decisionvec;
}