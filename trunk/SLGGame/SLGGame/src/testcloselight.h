#pragma once
#include "cutscenes.h"

class TestCloseLight:public CutScence
{
public:
	TestCloseLight();
	~TestCloseLight();
private:
	virtual bool endCutScence();
	virtual void skipCutScence();
	virtual void updateCutScence(unsigned int deltaTime);
};