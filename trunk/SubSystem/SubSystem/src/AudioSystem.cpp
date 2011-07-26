#include "AudioSystem.h"

#define BGM_PATH "..\\media\\bgm\\"
#define SE_PATH "..\\media\\sound\\"

#ifndef SCRIPT_EDITOR
#include "Framerate.h"
#endif

AudioSystem::AudioSystem(void):mVol(-1),mStream(0),mSample(0),mStreamName("none")
{

}

AudioSystem::~AudioSystem(void)
{
	BASS_Free();
}

bool AudioSystem::init()
{
	return BASS_Init(-1,44100,0,0,NULL);
}

bool AudioSystem::playStream( std::string name,bool isLoop,int time)
{
	if (mStream!=0)
	{
		BASS_StreamFree(mStream);
	}

	std::string path=BGM_PATH;
	path+=name;
	mStream=BASS_StreamCreateFile(FALSE,path.c_str(),0,0,0);
	if (mStream==0)
	{
		return false;
	}
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM,0);//将音量调为0

	if (BASS_ChannelPlay(mStream,true))//开始播放
	{
		if (isLoop)
		{
			BASS_ChannelFlags(mStream, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
		}
		 
		if (time!=0)
		{
			mVol=0;
			mTickTime=time/1000;//每次增加音量的间隔
		}
		else
		{
			mVol=1001;
			mTickTime=0;
		}
		mInOut=true;
		mTimer.reset();
		mStreamName=name;

		return true;
	}
	else
	{
		return false;
	}
}

bool AudioSystem::stopStream(int time)
{
	if (mStream!=0)
	{
		mVol=1000;
		mInOut=false;
		mTickTime=time/1000;//每次减少音量的间隔
		mTimer.reset();
		mStreamName="none";
		return true;
	}
	else
	{
		return false;
	}
}

bool AudioSystem::playSample( std::string name,bool isLoop)
{
	if (mSample!=0)//如果不等0的话,就要释放掉以前的音效
	{
		BASS_SampleFree(mSample);
	}
		
	std::string path=SE_PATH;
	path+=name;

	if (isLoop)
	{
		mSample=BASS_SampleLoad(FALSE,path.c_str(),0,0,3,BASS_SAMPLE_LOOP);
	}
	else
	{
		mSample=BASS_SampleLoad(FALSE,path.c_str(),0,0,3,BASS_SAMPLE_OVER_POS);
	}
	
	HCHANNEL ch=BASS_SampleGetChannel(mSample,FALSE);
	return BASS_ChannelPlay(ch,FALSE);
}

void AudioSystem::FrameUpdate()
{
	if (mVol!=-1)
	{
		if (mTimer.getMilliseconds()>=mTickTime)
		{
			//复位定时器
			mTimer.reset();

			if (mInOut)
			{
				if (mVol<=1000)
				{
					BASS_SetConfig(BASS_CONFIG_GVOL_STREAM,mVol*5);
					mVol+=10*Framerate::getSingletonPtr()->speedfactor;
				}
				else
				{
					BASS_SetConfig(BASS_CONFIG_GVOL_STREAM,100*50);
					mVol=-1;
				}
			}
			else
			{
				if (mVol>=0)
				{
					BASS_SetConfig(BASS_CONFIG_GVOL_STREAM,mVol*5);
					mVol-=10*Framerate::getSingletonPtr()->speedfactor;
				}
				else
				{
					BASS_SetConfig(BASS_CONFIG_GVOL_STREAM,0);
					mVol=-1;
					BASS_StreamFree(mStream);
					mStream=0;
				}
			}
		}
	}

}

int AudioSystem::getErrorCode()
{
	return BASS_ErrorGetCode();
}

bool AudioSystem::stopSample()
{
	if (mSample!=0)
	{
		BASS_SampleFree(mSample);
	}
	mSample=0;
	return true;
}
