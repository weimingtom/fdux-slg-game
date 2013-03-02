#include "AudioSystem.h"
#ifndef SCRIPT_EDITOR
#include "DataLibrary.h"
#endif

#define BGM_PATH "..\\media\\sound\\bgm\\"
#define SE_PATH "..\\media\\sound\\Effect\\"

#ifndef SCRIPT_EDITOR
#include "Framerate.h"
#endif

//using namespace audiere;

AudioSystem::AudioSystem(void):mStreamName("none"),mStream(NULL),mSample(NULL)
{
	mSampleVol=1.0f;
	mStreamVol=1.0f;
	mIsFadeIn=false;
	mIsFadeOut=false;
}

AudioSystem::~AudioSystem(void)
{
	for (std::map<int,std::map<int,std::vector<std::string>>*>::iterator it=mSEList.begin();it!=mSEList.end();it++)
	{
		delete it->second;
	}

	mEngine->drop();
}

bool AudioSystem::init()
{
	std::vector<std::string> oneList=DataLibrary::getSingletonPtr()->getChildList("StaticData/SEData");
	for (std::vector<std::string>::iterator it=oneList.begin();it!=oneList.end();it++)
	{
		int oneType=0;
		DataLibrary::getSingletonPtr()->getData(std::string("StaticData/SEData/")+(*it),oneType);
		mSEList[oneType]=new std::map<int,std::vector<std::string>>();

		std::vector<std::string> twoList=DataLibrary::getSingletonPtr()->getChildList(std::string("StaticData/SEData/")+(*it));
		for (std::vector<std::string>::iterator itt=twoList.begin();itt!=twoList.end();itt++)
		{
			int twoType=0;
			DataLibrary::getSingletonPtr()->getData(std::string("StaticData/SEData/")+(*it)+"/"+(*itt),twoType);
			
			std::vector<std::string> thrList=DataLibrary::getSingletonPtr()->getChildList(std::string("StaticData/SEData/")+(*it)+"/"+(*itt));
			std::vector<std::string> se;
			for (std::vector<std::string>::iterator ittr=thrList.begin();ittr!=thrList.end();ittr++)
			{
				std::string temp;
				DataLibrary::getSingletonPtr()->getData(std::string("StaticData/SEData/")+(*it)+"/"+(*itt)+"/"+(*ittr),temp);
				se.push_back(temp);
			}
			mSEList[oneType]->operator [](twoType)=se;
		}
	}

	//mDevice=OpenDevice();
	mEngine=irrklang::createIrrKlangDevice();
	changeVolume();
	if (mEngine==NULL) {
		mEngine=irrklang::createIrrKlangDevice(irrklang::ESOD_NULL);
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

	if (mStream!=NULL)
	{
		mStream->stop();
		mStream->drop();
		mStream=NULL;
	}

	//mStream=OpenSound(mDevice, path.c_str(), true);
	//mStream->setRepeat(isLoop);
	mStream=mEngine->play2D(path.c_str(),isLoop,false,true);

	if(time==0)
	{
		mStream->setVolume(mStreamVol);
	}
	else
	{
		mStream->setVolume(0);
		mTimer.reset();
		mIsFadeIn=true;
		mIsFadeOut=false;
		mTickTime=time/(mStreamVol/0.05);
		mCurStreamVol=0;
	}

	return true;
}

bool AudioSystem::stopStream(int time)
{
	if (mStream!=NULL)
	{
		if(time==0)
		{
			mStream->stop();
			mStream->drop();
			mStream=NULL;
		}
		else
		{
			mTimer.reset();
			mIsFadeOut=true;
			mIsFadeIn=false;
			mTickTime=time/(mStreamVol/0.05);
			mCurStreamVol=mStreamVol;
		}
	}


	return true;
}

bool AudioSystem::playSample( std::string name,bool isLoop,bool isList)
{
	if(mSample!=NULL)
	{
		mSample->stop();
		mSample->drop();
		mSample=NULL;
	}

	std::string path=SE_PATH;

	if(isList)
	{
		std::queue<std::string> s;
		DataLibrary::getSingletonPtr()->split(name,"-",s);

		int first=Ogre::StringConverter::parseInt(s.front());
		s.pop();
		int second=Ogre::StringConverter::parseInt(s.front());

		std::vector<std::string> selist=mSEList[first]->operator [](second);
		srand((int)time(NULL));
		int r=rand()%selist.size();
		if(r>=selist.size())
			r=selist.size()-1;
		path+=selist[r];

		Ogre::LogManager::getSingletonPtr()->logMessage(std::string("Audio play:")+path,Ogre::LML_NORMAL);
	}
	else
	{
		path+=name;
	}

	mSample=mEngine->play2D(path.c_str(),isLoop,false,true);
	mSample->setVolume(mSampleVol);

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
		mSample->drop();
		mSample=NULL;
	}
	return true;
}
