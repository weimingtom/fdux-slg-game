#pragma once
#include "guiscene.h"

class GUISLWindow :
	public GUIScene
{
public:
	GUISLWindow(int width,int height);
	~GUISLWindow(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	void setCallScene(GUIScene* scene);

	GUISceneType getType()
	{
		return SLScene;
	}
private:
	void onYes(MyGUI::Widget* _sender);
	void onNo(MyGUI::Widget* _sender);
	void onSaveTextClick(MyGUI::Widget* _sender);
	void buttonLock(bool islock);

	MyGUI::Button* mYesButton;
	MyGUI::Button* mNoButton;
	MyGUI::TextBox* mCaption;
	MyGUI::EditBox* mFileName;
	MyGUI::ImageBox* mBG;
	MyGUI::Window* mWindow;

	bool mStartFade;
	MyGUI::TextBox* mOldText;
	bool isSave;
	bool isOk;

	GUIScene* mCallScene;
};

class GUISLWindowFactory:
	public GUISceneFactory
{
public:
	GUISLWindowFactory(){}

	~GUISLWindowFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUISLWindow(Width, Height);
	}
};
