#pragma once
#include "guiscene.h"

class GUIMenuWindow :
	public GUIScene
{
public:
	GUIMenuWindow(int Width,int Height);
	virtual ~GUIMenuWindow(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return MenuWindowsScene;
	}

	void setAllowSave(bool allow) { mSaveButton->setEnabled(allow);}

	bool getVisible();

	void onOtherSceneNotify(std::string arg);

private:

	void onRestart(MyGUI::Widget* _sender);
	void onSave(MyGUI::Widget* _sender);
	void onLoad(MyGUI::Widget* _sender);
	void onExit(MyGUI::Widget* _sender);
	void onOption( MyGUI::Widget* _sender );

	MyGUI::ImageBox* mWindow;
	MyGUI::Button* mRestartButton;
	MyGUI::Button* mSaveButton;
	MyGUI::Button* mLoadButton;
	MyGUI::Button* mOptionButton;
	MyGUI::Button* mExitButton;

};

class GUIMenuWindowFactory:
	public GUISceneFactory
{
public:
	GUIMenuWindowFactory(){}

	~GUIMenuWindowFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIMenuWindow(Width, Height);
	}
};