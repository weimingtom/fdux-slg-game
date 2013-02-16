#pragma once

#include <vector>

#include "DecisionMapFactor.h"

template <typename T>
class DecisionMap
{
public:
	DecisionMap(std::vector<T>& decisionVec);
	~DecisionMap();

	void addFactor(DecisionMapFactor<T> *factor, float scale);
	void calcDecision();

	T getHighest();
	std::vector<T> getHigherThan(float possibility);
	std::vector<T> getSortedDecisions();
private:
	struct FactorInfo
	{
		DecisionMapFactor<T>* factor;
		float scale;
	};
	std::vector<FactorInfo> mFactorVec;

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
	std::vector<FactorInfo>::iterator ite = mFactorVec.begin();
	for( ; ite != mFactorVec.end(); ite++)
	{
		delete (*ite).factor;
	}
	mFactorVec.clear();
}

template <typename T>
void DecisionMap<T>::addFactor(DecisionMapFactor<T> *factor, float scale)
{
	FactorInfo factorinfo;
	factorinfo.factor = factor;
	factorinfo.scale = scale;
	mFactorVec.push_back(factorinfo);
}

template <typename T>
bool DGreater(DecisionInfo<T> elem1, DecisionInfo<T> elem2)
{
   return elem1.possibility > elem2.possibility;
}

template <typename T>
void DecisionMap<T>::calcDecision()
{
	std::vector<FactorInfo>::iterator ite = mFactorVec.begin();
	std::vector<DecisionInfo<T>>::iterator ite1 = mDecisionVec.begin();
	for( ; ite != mFactorVec.end(); ite++)
	{
		for(ite1 = mDecisionVec.begin() ; ite1 != mDecisionVec.end(); ite1++)
		{
			(*ite1).possibility += (*ite).factor->calcDecision((*ite1).decision) * (*ite).scale;
		}
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