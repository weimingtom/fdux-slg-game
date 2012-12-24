#include "AudioSystem.h"
#ifndef SCRIPT_EDITOR
#include "DataLibrary.h"
#endif

#define BGM_PATH "..\\media\\sound\\bgm\\"
#define SE_PATH "..\\media\\sound\\Effect\\"

#ifndef SCRIPT_EDITOR
#include "Framerate.h"
#endif

using namespace audiere;

AudioSystem::AudioSystem(void):mStreamName("none"),mStream(NULL),mSample(NULL)
{
	mSampleVol=1.0f;
	mStreamVol=1.0f;
	mIsFadeIn=false;
	mIsFadeOut=false;
}

AudioSystem::~AudioSystem(void)
{

}

bool AudioSystem::init()
{
	mDevice=OpenDevice();
	changeVolume();
	if (!mDevice) {
		return false;
	}
	return true;
}

void AudioSystem::changeVolume()
{
#ifndef SCRIPT_EDITOR
	int MusicVolume,SEVolume;
	DataLibrary::getSingletonPtr()->getData("SystemConfig/MusicVolume",MusicVolume);
	DataLibrary::getSingletonPtr()->getData("SystemConfig/SEVolume",SEVolume);
	
	mStreamVol=MusicVolume/100.0;
	mSampleVol=SEVolume/100.0;

	if (mStream!=NULL)
	{
		mStream->setVolume(mStreamVol);
	}
	if (mSample!=NULL)
	{
		mSample->setVolume(mSampleVol);
	}

#endif
}

bool AudioSystem::playStream( std::string name,bool isLoop,int time)
{
	std::string path=BGM_PATH;
	path+=name;
	mStreamName=name;

	mStream=OpenSound(mDevice, path.c_str(), true);
	mStream->setRepeat(isLoop);
	if(time==0)
	{
		mStream->setVolume(mStreamVol);
	}
	else
	{
		mStream->setVolume(0);
		mTimer.reset();
		mIsFadeIn=true;
		mTickTime=time/(mStreamVol/0.05);
		mCurStreamVol=0;
	}
	mStream->play();

	return true;
}

bool AudioSystem::stopStream(int time)
{
	if (mStream!=NULL)
	{
		if(time==0)
		{
			mStream->stop();
		}
		else
		{
			mTimer.reset();
			mIsFadeOut=true;
			mTickTime=time/(mStreamVol/0.05);
			mCurStreamVol=mStreamVol;
		}
	}


	return true;
}

bool AudioSystem::playSample( std::string name,bool isLoop)
{
	std::string path=SE_PATH;
	path+=name;

	mSample=OpenSound(mDevice, path.c_str(), false);
	mSample->setRepeat(isLoop);
	mSample->setVolume(mSampleVol);
	mSample->play();

	return true;
}

void AudioSystem::FrameUpdate()
{
	if(mIsFadeIn || mIsFadeOut)
	{
		if(mIsFadeIn)
		{
			if(mTimer.getMilliseconds()>=mTickTime)
			{
				mCurStreamVol+=0.05;
				mTimer.reset();
				if(mCurStreamVol>=mStreamVol)
				{
					mIsFadeIn=false;
				}
			}
		}
		else if(mIsFadeOut)
		{
			if(mTimer.getMilliseconds()>=mTickTime)
			{
				mCurStreamVol-=0.05;
				mTimer.reset();
				if(mCurStreamVol<=0)
				{
					mStream->stop();
					mIsFadeOut=false;
				}
			}
		}

		mStream->setVolume(mCurStreamVol);
	}
}

std::string AudioSystem::getError(bool isStreamError)
{
	return "";
}

bool AudioSystem::stopSample()
{
	if (mSample!=NULL)
	{
		mSample->stop();
	}
	return true;
}
