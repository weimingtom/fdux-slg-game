#pragma once
#include "guiscene.h"

class GUIMessageBox :
	public GUIScene
{
public:
	GUIMessageBox(int width,int height);
	virtual ~GUIMessageBox(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	void setNotify(GUIScene* scene){mNotifyScene=scene;}

	GUISceneType getType()
	{
		return MessageBoxScene;
	}
	
	bool mIsReturn;
	bool mYesNo;

private:
	MyGUI::Button* mYesButton;
	MyGUI::Button* mNoButton;
	MyGUI::TextBox* mCaption;
	MyGUI::ImageBox* mBG;
	MyGUI::Window* mWindow;

	GUIScene* mNotifyScene;

	void onYes(MyGUI::Widget* _sender);
	void onNo(MyGUI::Widget* _sender);
};

class GUIMessageBoxFactory:
	public GUISceneFactory
{
public:
	GUIMessageBoxFactory(){}

	~GUIMessageBoxFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIMessageBox(Width, Height);
	}
};