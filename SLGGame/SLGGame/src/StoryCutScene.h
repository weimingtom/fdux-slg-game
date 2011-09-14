#pragma once
#include "cutscene.h"

#include <string>

class StoryCutScene :
	public CutScene
{
public:
	StoryCutScene(std::string scriptName);
	virtual ~StoryCutScene(void);

	void startCutScence();
	bool endCutScene();
	void skipCutScene();
	void updateCutScene(unsigned int deltaTime);

	std::string mScriptName;

};