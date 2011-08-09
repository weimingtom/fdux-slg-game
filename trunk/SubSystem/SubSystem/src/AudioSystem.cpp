#include "AudioSystem.h"

#define BGM_PATH "..\\media\\bgm\\"
#define SE_PATH "..\\media\\sound\\"

#ifndef SCRIPT_EDITOR
#include "Framerate.h"
#endif

using namespace audiere;

AudioSystem::AudioSystem(void):mStreamName("none")//:mVol(-1),mStream(0),mSample(0),mStreamName("none"),mNextMusic("none"),mNextTime(0),mNextLoop(true)
{

}

AudioSystem::~AudioSystem(void)
{

}

bool AudioSystem::init()
{
	mDevice=OpenDevice();
	if (!mDevice) {
		return false;
	}
	return true;
}

bool AudioSystem::playStream( std::string name,bool isLoop,int time)
{
	std::string path=BGM_PATH;
	path+=name;
	mStreamName=name;

	mStream=OpenSound(mDevice, path.c_str(), true);
	mStream->setRepeat(isLoop);
	mStream->play();

	return true;
}

bool AudioSystem::stopStream(int time)
{
	mStream->stop();
	return true;
}

bool AudioSystem::playSample( std::string name,bool isLoop)
{
	std::string path=SE_PATH;
	path+=name;

	mSample=OpenSound(mDevice, path.c_str(), false);
	mSample->setRepeat(isLoop);
	mSample->play();

	return true;
}

void AudioSystem::FrameUpdate()
{

}

std::string AudioSystem::getError(bool isStreamError)
{
	return "";
}

bool AudioSystem::stopSample()
{
	mSample->stop();
	return true;
}
