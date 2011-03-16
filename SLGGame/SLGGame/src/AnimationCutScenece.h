#pragma once

#include "cutscenes.h"

#include <string>

class SquadGraphics;

class AnimationCutScenece:public CutScence
{
public:
	enum AnimationObject
	{
		Commander,
		Soldier,
		Squad
	};
	
	//isBackToWait:是否回退到待机动画
	AnimationCutScenece(unsigned int id,AnimationObject object,std::string name,bool isLoop=true,bool isBackToWait=false);
	~AnimationCutScenece(void);


protected:
	bool endCutScence();
	void skipCutScence();
	void updateCutScence(unsigned int deltaTime);

	bool mIsBackeToWait;
	SquadGraphics* mSquadGraphics;
	AnimationObject mObject;
};
