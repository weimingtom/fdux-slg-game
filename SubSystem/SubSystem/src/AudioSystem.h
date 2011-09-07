#pragma once

#include "iisingleton.hpp"

#include "GUICommon.h"

#include <audiere.h>

#include <MyGUI.h>

using namespace izayoi;

class AudioSystem:public IISingleton<AudioSystem> 
{
public:
	AudioSystem();
	~AudioSystem(void);

	bool init();

	void changeVolume();

	bool playStream(std::string name,bool isLoop,int time);

	bool stopStream(int time);

	bool playSample(std::string name,bool isLoop);

	bool stopSample();

	std::string getError(bool isStreamError);

	void FrameUpdate();

	std::string mStreamName;
private:
	audiere::AudioDevicePtr mDevice;
	audiere::OutputStreamPtr mStream;
	audiere::OutputStreamPtr mSample;
	float mStreamVol;
	float mSampleVol;
	//MyGUI::Timer mTimer;
	//HSTREAM mStream;//音频流
	//HSAMPLE mSample;//音效
	//int mVol;
	//bool mInOut;//渐入还是渐出,true为in,false为out
	//int mTickTime;//定时器单次时间
	//std::string mNextMusic;
	//int mNextTime;
	//bool mNextLoop;
};
