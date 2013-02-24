#pragma once
#include "cutscene.h"

#include <string>

#include "squaddefine.h"

#include "GUIBattle.h"
#include "GUIGameOver.h"

class WinLostCutScene : public CutScene
{
public:
	WinLostCutScene(bool isWin);
	virtual ~WinLostCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	bool mIsWin;

};