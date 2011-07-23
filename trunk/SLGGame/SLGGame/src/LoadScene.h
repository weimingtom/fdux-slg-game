#pragma once
#include "GUIScene.h"

class LoadScene :public GUIScene
{
public:
	LoadScene(int width,int height,std::string filename, std::string text);
	~LoadScene();
	void setProgress(unsigned int progress);
	void setBackGround(std::string filename);
	void setText(std::string text);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return LoadingScene;
	}
	void setMapName(std::string text);
	void setMapInfo(std::string info);

	bool isStartCheck;
	bool isClick;
private:
	void eventMouseButtonClick(MyGUI::Widget* _sender);

	MyGUI::ImageBox* mBackgroundImage;
	MyGUI::ProgressBar* mLoadProgress;
	MyGUI::TextBox* mLoadText;
	MyGUI::TextBox* mMapName;
	MyGUI::EditBox* mMapInfo;
};

class LoadSceneFactory:
	public GUISceneFactory
{
public:
	LoadSceneFactory(){}

	~LoadSceneFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new LoadScene(Width, Height, "menubg.jpg", "Loading");
	}
};