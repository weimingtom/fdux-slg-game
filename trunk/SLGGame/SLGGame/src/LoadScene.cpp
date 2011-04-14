#include "LoadScene.h"

LoadScene::LoadScene(int width,int height,std::string filename, std::string text):GUIScene("Loadling.layout")
{
	assignWidget(mBackgroundImage,"backgroundImage");
	assignWidget(mLoadProgress,"loadProgress");
	assignWidget(mLoadText,"loadText");

	mBackgroundImage->setSize(width,height);
	mBackgroundImage->setImageTexture(filename);
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

void LoadScene::showScene(std::string arg)
{

}
void LoadScene::hideScene()
{

}

void LoadScene::FrameEvent()
{

}