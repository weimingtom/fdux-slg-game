#pragma once
#include "cutscene.h"

class DelayCutScene:public CutScene
{
public:
	DelayCutScene(unsigned int lasttime, CutScene* next);
	~DelayCutScene();
private:
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);
};