#pragma once

#include "cutscene.h"

#include <string>

class SquadGraphics;

class AnimationCutScene:public CutScene
{
public:
	enum AnimationObject
	{
		Commander,
		Soldier,
		Squad
	};
	
	//isBackToWait:是否回退到待机动画
	AnimationCutScene(unsigned int id,AnimationObject object,std::string name,bool isLoop=true,bool isBackToWait=false);
	~AnimationCutScene(void);


protected:
	void startCutScence() {}
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	bool mIsBackeToWait;
	SquadGraphics* mSquadGraphics;
	AnimationObject mObject;
};
