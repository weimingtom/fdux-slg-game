#include "CombineCutScene.h"


CombineCutScene::CombineCutScene()
{

}
CombineCutScene::~CombineCutScene()
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		delete *ite;
	}
}

void CombineCutScene::addCutScene(CutScene* cutscene)
{
	mCutScene.push_back(cutscene);
}

void CombineCutScene::startCutScence()
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		(*ite)->start();
	}
}

bool CombineCutScene::endCutScene()
{
	CutSceneIte ite;
	bool bend = true;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		if(!(*ite)->end())
			bend = false;
	}
	return bend;
}
void CombineCutScene::skipCutScene()
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();ite++)
	{
		(*ite)->skipall();
	}
}
void CombineCutScene::updateCutScene(unsigned int deltaTime)
{
	CutSceneIte ite;
	for(ite = mCutScene.begin(); ite != mCutScene.end();)
	{
		if((*ite)->end())
		{
			delete *ite;
			ite = mCutScene.erase(ite);
		}
		else
		{
			(*ite)->update(deltaTime);
			ite++;
		}
	}
}