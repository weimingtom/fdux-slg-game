#include "Framerate.h"

Framerate::Framerate(void)
{
}

Framerate::~Framerate(void)
{
}

void Framerate::Init(float tfps)

{

	targetfps = tfps;

	QueryPerformanceCounter(&framedelay);

	QueryPerformanceFrequency(&tickspersecond);

}

void Framerate::SetSpeedFactor()

{

	QueryPerformanceCounter(&currentticks);

	//This frame's length out of desired length

	speedfactor=(float)(currentticks.QuadPart-framedelay.QuadPart)/((float)tickspersecond.QuadPart/targetfps);

	fps = targetfps/speedfactor;

	if (speedfactor <= 0)

		speedfactor = 1;



	framedelay = currentticks;

}