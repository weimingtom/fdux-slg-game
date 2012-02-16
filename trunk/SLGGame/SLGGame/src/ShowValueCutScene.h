#pragma once
#include "cutscene.h"
#include "squaddefine.h"

#include <Ogre.h>
#include <string>

class SquadGraphics;

class ShowValueCutScene :
	public CutScene
{
public:
	enum WeaponType
	{
		MainWepon,
		SceWepon
	};

	ShowValueCutScene(std::string id,std::string value,Ogre::ColourValue c);
	virtual ~ShowValueCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	SquadGraphics* mSquadGraphics;
	std::string mValue;
	Ogre::ColourValue mColor;
};
