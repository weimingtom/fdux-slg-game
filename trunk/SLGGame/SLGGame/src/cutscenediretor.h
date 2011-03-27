#pragma once

#include "SubBattleState.h"

#include <map>


class CutScene;

class CutSceneDirector:public SubBattleState
{
public:
	CutSceneDirector(BattleState* mainState);
	~CutSceneDirector();

	int addCutScene(CutScene* cutscene);
	void skipCutScene(int id);

	virtual void update(unsigned int deltaTime);
private:
	typedef std::pair<int, CutScene*> CutScenePair;
	typedef std::map<int, CutScene*>::iterator CutSceneIte;
	std::map<int, CutScene*> mCutScene;
	int mId;
};