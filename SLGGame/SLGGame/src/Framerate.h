#pragma once

#include "iisingleton.hpp"

#include "windows.h"

using namespace izayoi;

class Framerate:public IISingleton<Framerate>
{
public:
	Framerate(void);
	~Framerate(void);
	float targetfps;
	float fps;
	LARGE_INTEGER tickspersecond;
	LARGE_INTEGER currentticks;
	LARGE_INTEGER framedelay;
	float speedfactor;   
	void Init(float tfps);
	void SetSpeedFactor();
};
