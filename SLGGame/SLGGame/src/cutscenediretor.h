#pragma once

#include <map>

class CutScene;

class CutSceneDirector
{
public:
	CutSceneDirector();
	~CutSceneDirector();

	int addCutScene(CutScene* cutscene);
	void skipCutScene(int id);

	void update(unsigned int deltaTime);
private:
	typedef std::pair<int, CutScene*> CutScenePair;
	typedef std::map<int, CutScene*>::iterator CutSceneIte;
	std::map<int, CutScene*> mCutScene;
	int mId;
};