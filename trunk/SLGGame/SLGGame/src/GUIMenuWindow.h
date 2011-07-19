#pragma once
#include "guisubwindows.h"

class GUIMenuWindow :
	public GUISubWindows
{
public:
	GUIMenuWindow(MyGUI::Window* window,int Width,int Height);
	virtual ~GUIMenuWindow(void);

	void showScene(std::string arg);
	void hideScene();

	void FrameEvent();

	GUISceneType getType()
	{
		return BattleScene;
	}

	bool GridInputEvent(int x,int y);

	bool KeyInputEvent(const OIS::KeyEvent &arg);

	std::string getName()
	{
		return "Menu";
	}

	void setAllowSave(bool allow) { mSaveButton->setEnabled(allow);}

	bool getVisible();

private:

	void onRestart(MyGUI::Widget* _sender);
	void onExit(MyGUI::Widget* _sender);

	MyGUI::Window* mWindow;
	MyGUI::Button* mRestartButton;
	MyGUI::Button* mSaveButton;
	MyGUI::Button* mLoadButton;
	MyGUI::Button* mOptionButton;
	MyGUI::Button* mExitButton;
};
