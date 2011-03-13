#pragma once
#include "cutscenes.h"

class DelayCutScence:public CutScence
{
public:
	DelayCutScence(unsigned int lasttime, CutScence* next);
	~DelayCutScence();
private:
	virtual bool endCutScence();
	virtual void skipCutScence();
	virtual void updateCutScence(unsigned int deltaTime);
};