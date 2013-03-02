#pragma once
#include "guiscene.h"

class GUIOptionWindow :
	public GUIScene
{
public:
	GUIOptionWindow(int width,int height);
	virtual ~GUIOptionWindow(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return OptionWindowScene;
	}

private:
	MyGUI::Button* mYesButton;
	MyGUI::Button* mNoButton;
	MyGUI::TextBox* mCaption;
	MyGUI::TextBox* mMusicVolumeCaption;
	MyGUI::TextBox* mSEVolumeCaption;
	MyGUI::TextBox* mTextSpeedCaption;
	MyGUI::ScrollBar* mMusicScrollBar;
	MyGUI::ScrollBar* mSeScrollBar;
	MyGUI::ScrollBar* mTextSpeedScrollBar;
	MyGUI::ImageBox* mBG;
	MyGUI::Window* mWindow;

	void onYes(MyGUI::Widget* _sender);
	void onNo(MyGUI::Widget* _sender);

	void SaveData();
	void onOtherSceneNotify(std::string arg);
	bool returnToMainMenu;
};

class GUIOptionWindowFactory:
	public GUISceneFactory
{
public:
	GUIOptionWindowFactory(){}

	~GUIOptionWindowFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIOptionWindow(Width, Height);
	}
};