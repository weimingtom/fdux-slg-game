#include "AudioSystem.h"

#define BGM_PATH "..\\media\\bgm\\"
#define SE_PATH "..\\media\\sound\\"

using namespace libZPlay;

#ifndef SCRIPT_EDITOR
#include "Framerate.h"
#endif

AudioSystem::AudioSystem(void):mStreamName("none")//:mVol(-1),mStream(0),mSample(0),mStreamName("none"),mNextMusic("none"),mNextTime(0),mNextLoop(true)
{

}

AudioSystem::~AudioSystem(void)
{
	mStreamPlayer->Release();
	mSamplePlayer->Release();
}

bool AudioSystem::init()
{
	mStreamPlayer = CreateZPlay();
	mSamplePlayer=CreateZPlay();
	return true;
}

bool AudioSystem::playStream( std::string name,bool isLoop,int time)
{
	std::string path=BGM_PATH;
	path+=name;
	mStreamName=name;

	if (mStreamPlayer->OpenFile(path.c_str(),TStreamFormat::sfAutodetect)==0)
	{
		return false;
	}

	if (isLoop)
	{
		TStreamInfo info;
		mStreamPlayer->GetStreamInfo(&info);

		TStreamTime startTime;
		startTime.ms=0;
		TStreamTime endTime;
		endTime=info.Length;
		if (mStreamPlayer->PlayLoop(tfMillisecond, &startTime, tfMillisecond, &endTime ,99999, 1)==0)
		{
			return false;
		}
	}
	else
	{
		if(mStreamPlayer->Play()==0)
		{
			return false;
		}
	}

	if (time!=0)
	{
		TStreamTime start;
		TStreamTime end;
		mStreamPlayer->GetPosition(&start);
		end.ms = start.ms + time;

		mStreamPlayer->SlideVolume(tfMillisecond, &start, 0,0, tfMillisecond, &end, 100,100);
	}

	return true;
}

bool AudioSystem::stopStream(int time)
{
	TStreamTime start;
	TStreamTime end;
	mStreamPlayer->GetPosition(&start);
	end.ms = start.ms + time;

	return mStreamPlayer->SlideVolume(tfMillisecond, &start, 100,100, tfMillisecond, &end, 0,0);
}

bool AudioSystem::playSample( std::string name,bool isLoop)
{
	std::string path=SE_PATH;
	path+=name;

	if (mSamplePlayer->OpenFile(path.c_str(),TStreamFormat::sfAutodetect)==0)
	{
		return false;
	}

	if (isLoop)
	{
		TStreamInfo info;
		mSamplePlayer->GetStreamInfo(&info);

		TStreamTime startTime;
		startTime.ms=0;
		TStreamTime endTime;
		endTime=info.Length;
		if (mSamplePlayer->PlayLoop(tfMillisecond, &startTime, tfMillisecond, &endTime ,99999, 1)==0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if(mSamplePlayer->Play()==0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void AudioSystem::FrameUpdate()
{

}

std::string AudioSystem::getError(bool isStreamError)
{
	if (isStreamError)
	{
		return std::string(mStreamPlayer->GetError());
	}
	else
	{
		return std::string(mSamplePlayer->GetError());
	}
}

bool AudioSystem::stopSample()
{
	return mSamplePlayer->Stop();
}
