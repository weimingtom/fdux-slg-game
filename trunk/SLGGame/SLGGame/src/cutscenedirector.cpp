#include "cutscenediretor.h"
#include "cutscene.h"

CutSceneDirector::CutSceneDirector()
{
	mId = 0;
}
CutSceneDirector::~CutSceneDirector()
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		delete ite->second;
	}
}

int CutSceneDirector::addCutScene(CutScene* cutscene)
{
	if(cutscene!= NULL)
	{
		int id = mId++;
		mCutScene.insert(CutScenePair(id, cutscene));
		return id;
	}
	return -1;
}

void CutSceneDirector::skipCutScene(int id)
{
	CutSceneIte ite;
	ite = mCutScene.find(id);
	if(ite != mCutScene.end())
	{
		ite->second->skipall();
	}
}

void CutSceneDirector::update(unsigned int deltaTime)
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();)
	{
		if(ite->second->end())
		{
			delete ite->second;
			ite = mCutScene.erase(ite);
		}
		else
		{
			ite->second->update(deltaTime);
			ite++;
		}
	}
}