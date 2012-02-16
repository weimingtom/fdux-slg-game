#pragma once
#include "cutscene.h"
#include "squaddefine.h"

#include <string>

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

	WeapenCutScene(std::string id,WeaponType type);
	virtual ~WeapenCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	WeaponType mType;
};
