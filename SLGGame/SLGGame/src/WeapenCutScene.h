#pragma once
#include "cutscene.h"
#include "squaddefine.h"

class SquadGraphics;

class WeapenCutScene :
	public CutScene
{
public:
	enum WeaponType
	{
		MainWepon,
		SceWepon
	};

	WeapenCutScene(unsigned int id,WeaponType type);
	virtual ~WeapenCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	WeaponType mType;
};
