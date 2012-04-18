#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

class CutScene;

class CutSceneBuilder: public IISingleton<CutSceneBuilder>
{
public:
	CutSceneBuilder();
	~CutSceneBuilder();

	void addCutScene(CutScene* cutscene);

	bool hasCutScenes();
	CutScene* getCutScenes();
private:
	CutScene* mLastCutScene;
	CutScene* mFirstCutScene;
};