#include "CutSceneBuilder.h"

#include "cutscene.h"

CutSceneBuilder::CutSceneBuilder()
{
	mLastCutScene = NULL;
	mFirstCutScene = NULL;
}
CutSceneBuilder::~CutSceneBuilder()
{
	if(mLastCutScene)
		delete mLastCutScene;
	if(mFirstCutScene)
		delete mFirstCutScene;
}

bool CutSceneBuilder::hasCutScenes()
{
	return mFirstCutScene != NULL;
}

void CutSceneBuilder::addCutScene(CutScene* cutscene)
{
	if(cutscene == NULL)
		return;
	if(mLastCutScene == NULL)
	{
		mLastCutScene = cutscene;
		mFirstCutScene = cutscene;
		return;
	}
	mLastCutScene->setNextScene(cutscene);
	mLastCutScene = cutscene;
}

CutScene* CutSceneBuilder::getCutScenes()
{
	CutScene* cutscene = mFirstCutScene;
	mLastCutScene = NULL;
	mFirstCutScene = NULL;
	return cutscene;
}