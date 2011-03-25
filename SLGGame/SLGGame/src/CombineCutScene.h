#pragma once

#include "cutscene.h"
#include <list>

class CombineCutScene: public CutScene
{
public:
	CombineCutScene();
	~CombineCutScene();
	
	void addCutScene(CutScene* cutscene);

private:
	virtual void startCutScence();
	virtual bool endCutScene();
	virtual void skipCutScene();
	virtual void updateCutScene(unsigned int deltaTime);

	typedef std::list<CutScene*>::iterator CutSceneIte;
	std::list<CutScene*> mCutScene;
};