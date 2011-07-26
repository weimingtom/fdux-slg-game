#include "LoadScene.h"

#include "StringTable.h"

LoadScene::LoadScene(int width,int height,std::string filename, std::string text):GUIScene("Loadling.layout",width,height),isStartCheck(false),isClick(false)
{
	assignWidget(mBackgroundImage,"backgroundImage");
	assignWidget(mLoadProgress,"loadProgress");
	assignWidget(mLoadText,"loadText");
	assignWidget(mMapName,"MapName");
	assignWidget(mMapInfo,"MapInfo");

	mBackgroundImage->setSize(width,height);
	mBackgroundImage->setImageTexture(filename);
	mBackgroundImage->eventMouseButtonClick+=MyGUI::newDelegate(this, &LoadScene::eventMouseButtonClick);
	mLoadText->setCaption(text);
}
LoadScene::~LoadScene()
{

}

void LoadScene::setProgress(unsigned int progress)
{
	mLoadProgress->setProgressPosition(progress);
}
void LoadScene::setBackGround(std::string filename)
{
	mBackgroundImage->setImageTexture(filename);
}
void LoadScene::setText(std::string text)
{
	mLoadText->setCaption(text);
}

void LoadScene::setMapName(std::string text)
{
	mMapName->setCaption(text);
}

void LoadScene::setMapInfo( std::string info )
{
	std::string c=StringTable::getSingletonPtr()->getAnsiString(info);
	DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, c.c_str(), -1, NULL, 0);
	wchar_t *pwText;
	pwText = new wchar_t[dwNum];

	MultiByteToWideChar (CP_ACP, 0, c.c_str(), -1, pwText, dwNum);
	
	mMapInfo->setCaption("");

	std::wstring text=pwText;
	while(!text.empty())
	{
		mMapInfo->addText(text.substr(0,1));
		if (mMapInfo->getHScrollPosition()!=0)//×Ô¶¯»»ÐÐ
		{
			int length=mMapInfo->getTextLength();
			mMapInfo->eraseText(length-1);
			mMapInfo->addText("\n");
			mMapInfo->addText(text.substr(0,1));
		}
		text.erase(text.begin());
	}
	

}

void LoadScene::showScene(std::string arg)
{

}
void LoadScene::hideScene()
{

}

void LoadScene::FrameEvent()
{

}

void LoadScene::eventMouseButtonClick( MyGUI::Widget* _sender )
{
	if (isStartCheck)
	{
		isClick=true;
	}
}
