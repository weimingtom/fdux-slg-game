#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

class CutScene;

class CutSceneBuilder: public IISingleton<CutSceneBuilder>
{
public:
	CutSceneBuilder();
	~CutSceneBuilder();

	CutScene* getCutScenes();
private:
	
};