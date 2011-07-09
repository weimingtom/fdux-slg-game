#pragma once

#include "cutscene.h"
#include "squaddefine.h"
#include <string>

class SquadGraphics;

class AnimationCutScene:public CutScene
{
public:
	//isBackToWait:是否回退到待机动画
	AnimationCutScene(unsigned int id,UnitType object,std::string name,std::string sound , std::string particle,bool isLoop=true,bool isBackToWait=false);
	~AnimationCutScene(void);


protected:
	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	bool mIsBackeToWait;
	SquadGraphics* mSquadGraphics;
	UnitType mObject;
	std::string mName;
	std::string mSound;
	std::string mParticle;
	bool mIsLoop;
};
